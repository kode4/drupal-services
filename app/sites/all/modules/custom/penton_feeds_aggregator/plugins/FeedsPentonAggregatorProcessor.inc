<?php
/**
 * @file
 * Class definition of FeedsPentonAggregatorProcessor.
 */

// Create or delete FEEDS_NODE_BATCH_SIZE at a time.
if (!defined('FEEDS_NODE_BATCH_SIZE')) {
  define('FEEDS_NODE_BATCH_SIZE', 50);
}

if (!defined('FILTER_FORMAT_DEFAULT')) {
  define('FILTER_FORMAT_DEFAULT', 'filtered_html');
}

define('FEEDS_EXPIRE_ACTION_DELETE', 3);
define('FEEDS_EXPIRE_ACTION_UNPUBLISH', 4);

define('FEEDS_DEFAULT_CONTENT_TYPE', 'article');
require_once drupal_get_path('module', 'penton_feeds_aggregator') . '/penton_feeds_aggregator.mapping.inc';
require_once drupal_get_path('module', 'penton_feeds_aggregator') . '/plugins/FeedsPentonSyndicationParser.inc';

/**
 * Creates nodes from feed items.
 */
class FeedsPentonAggregatorProcessor extends FeedsProcessor {
  private $cckMap = array();

  /**
   * Implementation of FeedsProcessor::entityType().
   */
  public function entityType() {
    return 'node';
  }

  /**
   * Implementation of FeedsProcessor::newEntity().
   */
  public function newEntity(FeedsSource $source) {
    $node = new stdClass();
    $node->type = $this->bundle();
    $node->changed = REQUEST_TIME;
    $node->created = REQUEST_TIME;
    $node->language = LANGUAGE_NONE;
    $node->is_new = TRUE;
    node_object_prepare($node);
    // Populate properties that are set by node_object_prepare().
    $node->log = 'Created by FeedsNodeProcessor';
    return $node;
  }

  /**
   * Implementation of FeedsProcessor::entitySaveAccess().
   */
  public function entitySaveAccess($entity) {
    if ($this->source_config['feed_authorize']) {
      if (empty($entity->nid)) {
        $op = 'create';
        $entity->nid = 'new';
      }
      else {
        $op = 'update';
      }
      $account = user_load($entity->uid);
      if (!node_access($op, $entity, $account) && !user_access('administer feeds')) {
        throw new Exception('User ' . $account->name . ' not authorized to ' . $op . ' content type ' . $entity->type);
      }
    }
  }

  /**
   * Implementation of FeedsProcessor::entitySave().
   */
  public function entitySave($entity) {
    $entity->feeds_item->feed_nid = $entity->field_feed_source[0]['value'];
    $entity->feeds_item->entity_type = 'node';
    $entity->body[LANGUAGE_NONE][0]['format'] = $this->source_config['feed_input_format'];
    node_object_prepare($entity);
    node_save($entity);
  }

  /**
   * Implementation of FeedsProcessor::entityDeleteMultiple().
   */
  public function entityDeleteMultiple($entity_ids) {
    entity_delete_multiple('node', $entity_ids);
  }

  /**
   * Implementation of FeedsPlugin::pluginType().
   */
  public function pluginType() {
  }

  /**
   * Implementation of FeedsProcessor::process().
   */
  public function process(FeedsSource $source, FeedsParserResult $parser_result) {
    $this->source_config = $source->config['FeedsPentonAggregatorProcessor'];

    // Per-feed mappings.
    $aggregated_mappings = json_decode($this->source_config['feed_mapping'], TRUE);
    $targets = penton_get_mapping_targets(FEEDS_DEFAULT_CONTENT_TYPE);
    $base_map = array();
    foreach ($aggregated_mappings as $map) {
      if (isset($targets[$map['target']]['type'])) {
        $this->cckMap[] = $map;
      }
      else {
        $base_map[] = $map;
      }
    }
    foreach ($parser_result->items as &$raw_item) {
      penton_feeds_aggregator_parse_description($raw_item);
    }
    $this->config['mappings'] = $base_map;

    $state = $source->state(FEEDS_PROCESS);

    while ($item = $parser_result->shiftItem()) {
      // Check if this item already exists.
      $entity_id = $this->existingEntityId($source, $parser_result);
      $skip_existing = $this->source_config['update_existing'] == FEEDS_SKIP_EXISTING;

      // If it exists, and we are not updating, pass onto the next item.
      if ($entity_id && $skip_existing) {
        continue;
      }

      $hash = $this->hash($item);
      $changed = ($hash !== $this->getHash($entity_id));
      $force_update = FALSE;

      // Do not proceed if the item exists, has not changed, and we're not
      // forcing the update.
      if ($entity_id && !$changed && !$force_update) {
        continue;
      }

      // Map and save node. If errors occur don't stop but report them.
      try {
        $populate = FALSE;
        // Load an existing entity.
        if ($entity_id) {
          $entity = $this->entityLoad($source, $entity_id);

          // The feeds_item table is always updated with the info for the most
          // recently processed entity. The only carryover is the entity_id.
          $this->newItemInfo($entity, $source->feed_nid, $hash);
          $entity->feeds_item->entity_id = $entity_id;
          $entity->feeds_item->is_new = FALSE;

          if ($this->source_config['update_existing'] != FEEDS_UPDATE_EXISTING) {
            $populate = TRUE;
          }
        }

        // Build a new entity.
        else {
          $entity = $this->newEntity($source);
          $this->newItemInfo($entity, $source->feed_nid, $hash);
          $populate = TRUE;
        }

        $entity->feeds_item->hash = $hash;
        if ($populate) {
          $this->populate($entity);
        }

        $this->map($source, $parser_result, $entity);
        if (!empty($this->cckMap)) {
          foreach ($this->cckMap as $map) {
            if ($map['target'] == 'field_penton_published_datetime') {
              if (is_int($item[$map['source']])) {
                $entity->{$map['target']}[LANGUAGE_NONE][0]['value']['date'] = date('Y-m-d\TH:i:s', $item[$map['source']]);
              }
            }
            else {
              $entity->{$map['target']}[LANGUAGE_NONE][0]['value'] = $item[$map['source']];
            }
          }
        }

        $entity->field_feed_source[0]['value'] = $source->feed_nid;

        if (!empty($entity->feeds_item->url) && strpos($entity->feeds_item->url, 'guid-') === FALSE) {
          $entity->entitywords['canonical']['value'] = $entity->feeds_item->url;
        }
        $this->entitySaveAccess($entity);
        $this->entitySave($entity);

        // Set metatags.
        $metatags = array();
        if ($this->source_config['feed_bloomberg']) {
          $metatags[LANGUAGE_NONE]['robots']['value'] = array(
            'noindex' => 'noindex',
            'nofollow' => 'nofollow',
          );
        }
        $striped_body = strip_tags($item['description']);
        $striped_body = preg_replace('/\s+/i', ' ', $striped_body);
        $striped_body = trim($striped_body, ' ');
        $metatags[LANGUAGE_NONE]['description']['value'] = !empty($item['summary']) ? $item['summary'] :
          (!empty($striped_body) && strlen($striped_body) > 160 ? truncate_utf8($striped_body, 160, FALSE, TRUE) : $striped_body);
        if (!empty($entity->feeds_item->url) && strpos($entity->feeds_item->url, 'guid-') === FALSE) {
          $metatags[LANGUAGE_NONE]['canonical']['value'] = $entity->feeds_item->url;
        }
        if ($this->source_config['feed_noindex']) {
          $metatags[LANGUAGE_NONE]['robots']['value']['noindex'] = 'noindex';
        }
        metatag_metatags_save('node', $entity->nid, $entity->vid, $metatags, LANGUAGE_NONE);

        // Track progress.
        if (empty($entity_id)) {
          $state->created++;
        }
        else {
          $state->updated++;
        }
      }
      catch (Exception $e) {
        $state->failed++;
        drupal_set_message($e->getMessage(), 'warning');
        watchdog('feeds', $e->getMessage(), array(), WATCHDOG_WARNING);
      }
    }

    // Set messages if we're done.
    if ($source->progressImporting() != FEEDS_BATCH_COMPLETE) {
      return;
    }
    $info = $this->entityInfo();

    $tokens = array(
      '@entity' => 'node',
      '@entities' => 'nodes',
    );
    $messages = array();
    if ($state->created) {
      $messages[] = array(
        'message' => format_plural(
          $state->created,
          'Created @number @entity.',
          'Created @number @entities.',
          array('@number' => $state->created) + $tokens
        ),
      );
    }
    if ($state->updated) {
      $messages[] = array(
        'message' => format_plural(
          $state->updated,
          'Updated @number @entity.',
          'Updated @number @entities.',
          array('@number' => $state->updated) + $tokens
        ),
      );
    }
    if ($state->failed) {
      $messages[] = array(
        'message' => format_plural(
          $state->failed,
          'Failed importing @number @entity.',
          'Failed importing @number @entities.',
          array('@number' => $state->failed) + $tokens
        ),
        'level' => WATCHDOG_ERROR,
      );
    }
    if (empty($messages)) {
      $messages[] = array(
        'message' => t('There are no new @entities.', array('@entities' => strtolower($info['label plural']))),
      );
    }
    foreach ($messages as $message) {
      drupal_set_message($message['message']);
      $source->log('import', $message['message'], array(), isset($message['level']) ? $message['level'] : WATCHDOG_INFO);
    }
    db_query(
      'INSERT INTO {penton_feeds_aggregator_last_import} VALUES (:feed_nid, :feeds_request_time)
      ON DUPLICATE KEY UPDATE last_import = :feeds_request_time',
      array(
        ':feed_nid' => $source->feed_nid,
        ':feeds_request_time' => FEEDS_REQUEST_TIME,
      ));
  }

  /**
   * Populates node with mappings.
   */
  protected function populate($node) {
    $node->type = FEEDS_DEFAULT_CONTENT_TYPE;
    $node->changed = FEEDS_REQUEST_TIME;
    $node->body[LANGUAGE_NONE][0]['format'] = $this->source_config['feed_input_format'];
    $node->feeds_item = new stdClass();
    $node->feeds_item->id = $this->id;
    $node->feeds_item->imported = FEEDS_REQUEST_TIME;

    // Fill taxonomy.
    $taxonomy_fields = array(
      'feed_primary_category' => 'categories',
      'feed_secondary_category' => 'categories',
      'feed_program' => 'program',
    );
    foreach ($taxonomy_fields as $conf_name => $vocabulary_name) {
      if (!empty($this->source_config[$conf_name])) {
        $taxs = explode(',', $this->source_config[$conf_name]);
        foreach ($taxs as $t) {
          $tid = key(taxonomy_get_term_by_name($t, $vocabulary_name));
          $field_name = str_replace('feed_', 'field_penton_', $conf_name);
          $node->{$field_name}[LANGUAGE_NONE][]['tid'] = $tid;
        }
      }
    }

    // Fill authors.
    $contributors = explode(',', $this->source_config['feed_contributors']);
    foreach ($contributors as $contributor) {
      $contributor_id = trim(preg_replace('/.*\((\d*)\)/', '$1', $contributor));
      if (!empty($contributor_id)) {
        $node->field_penton_author[LANGUAGE_NONE][]['target_id'] = $contributor_id;
      }
    }

    $node->field_penton_article_type[LANGUAGE_NONE][]['tid'] = key(taxonomy_get_term_by_name('Article', 'article_type'));
    $node->field_penton_privacy_settings[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_privacy_settings'];

    $node->field_penton_promote_on_site[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_promote_on_site_lists_and_rss'];
    $node->field_penton_google_news_flag[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_google_news_flag'];
    $node->field_penton_press_release_flag[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_press_release_flag'];
    $node->field_penton_aggregated_content[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_aggregated_content'];
    $node->field_penton_native_advertising[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_native_advertising'];
    $node->field_penton_syndicate_atom[LANGUAGE_NONE][0]['value'] = $this->source_config['feed_syndicate'];

    static $included;
    if (!$included) {
      module_load_include('inc', 'node', 'node.pages');
      $included = TRUE;
    }
    node_object_prepare($node);

    $user = user_load_by_name($this->source_config['feed_author']);
    $node->status = $this->source_config['feed_publish_option'];
    $node->promote = $this->source_config['feed_promote_option'];
    $node->uid = $user->uid;

    // Populate properties that are set by node_object_prepare().
    $node->log = 'Created/updated by FeedsPentonAggregatorProcessor';
    return $node;
  }

  /**
   * Override parent::configDefaults().
   *
   * We want empty defaults to get rid of the FeedsNodeProcessor stuff.
   */
  public function configDefaults() {
    return array(
      'mappings' => array(),
      'content_type' => FALSE,
      'bundle' => FEEDS_DEFAULT_CONTENT_TYPE,
    );
  }

  /**
   * Return configuration form for this object.
   *
   * The keys of the configuration form must match the keys of the
   * array returned by configDefaults().
   *
   * @return array
   *   FormAPI style form definition.
   */
  public function configForm(&$form_state) {
    $form = array();
    // TODO: neccessary config form.
    return $form;
  }

  /**
   * Add config form.
   *
   * Add config form that allows us to pick a parent feed to save our additional
   * node data to.
   */
  public function sourceForm($source_config) {
    drupal_add_js(drupal_get_path('module', 'penton_feeds_aggregator') . '/mapping_table.js');
    $feed_id = arg(1);
    $parser = new FeedsPentonSyndicationParser($feed_id);
    $default_author = 'admin';
    if (!empty($source_config)) {
      $default_author = penton_feeds_aggregator_get_feed_author($feed_id);
    }
    $default_content_type = FEEDS_DEFAULT_CONTENT_TYPE;
    $form = array();
    $types = node_type_get_types('names');
    $brand_options = get_brands_options();
    $form['#prefix'] = "<fieldset class='collapsible collapsed form-wrapper'><legend><span class='fieldset-legend'>Mapping</span></legend>
    <div class='fieldset-wrapper'><div class='description'>Target <strong>\"GUID\"</strong> is highly recommended for detecting no changed content in remote feed</div>
    <div id='mapping-table-wrapper'>
    </div></div></fieldset>
          <script>
             var mapping = {\"map\": " . (!empty($source_config['feed_mapping']) && strlen($source_config['feed_mapping']) > 2 ? $source_config['feed_mapping'] : json_encode(penton_default_mappings(FEEDS_DEFAULT_CONTENT_TYPE))) . "};
             var mappingTargets = " . json_encode(penton_get_mapping_targets(FEEDS_DEFAULT_CONTENT_TYPE)) . ";
             var mappingSources = " . json_encode($parser->getMappingSources()) . ";
             var taxonomyVocabs = " . json_encode(taxonomy_get_vocabularies(FEEDS_DEFAULT_CONTENT_TYPE)) . ";
          </script>";
    $form['feed_mapping'] = array(
      '#type' => 'hidden',
      '#title' => t('Mappings'),
      '#attributes' => array(
        'id' => 'edit-feeds-FeedsPentonAggregatorProcessor-feed-mapping',
      ),
      '#default_value' => '[]',
    );
    $form['feed_publish_option'] = array(
      '#type' => 'checkbox',
      '#title' => t('Import items as Published'),
      '#description' => t('Check if your want to publish all imported nodes'),
      '#default_value' => !empty($source_config['feed_publish_option']) ? $source_config['feed_publish_option'] : FALSE,
    );
    $form['feed_promote_option'] = array(
      '#type' => 'checkbox',
      '#title' => t('Import items as Promoted on front page'),
      '#description' => t('Check if your want to promote all imported nodes'),
      '#default_value' => !empty($source_config['feed_promote_option']) ? $source_config['feed_promote_option'] : FALSE,
    );
    $period = drupal_map_assoc(
      array(
        900,
        1800,
        3600,
        10800,
        21600,
        43200,
        86400,
        259200,
        604800,
        2419200,
      ),
      'format_interval'
    );
    $period = array(FEEDS_EXPIRE_NEVER => 'Never') + $period;
    $form['feed_import_period'] = array(
      '#type' => 'select',
      '#title' => t('Minimum refresh period'),
      '#options' => $period,
      '#description' => t('This is the minimum time that must elapse before a feed may be refreshed automatically.'),
      '#default_value' => !empty($source_config['feed_import_period']) || (isset($source_config['feed_import_period']) && is_numeric($source_config['feed_import_period']) && $source_config['feed_import_period'] == 0) ? $source_config['feed_import_period'] : 3600,
    );
    $format_options = array(FILTER_FORMAT_DEFAULT => t('Default format'));
    $formats = filter_formats();
    foreach ($formats as $format) {
      $format_options[$format->format] = $format->name;
    }
    $form['feed_input_format'] = array(
      '#type' => 'select',
      '#title' => t('Input format'),
      '#description' => t('Select the input format for the body field of the nodes to be created.'),
      '#options' => $format_options,
      '#default_value' => !empty($source_config['feed_input_format']) ? $source_config['feed_input_format'] : 0,
    );
    $form['feed_author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#description' => t('Select the author of the nodes to be created - leave empty to assign "anonymous".'),
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => $default_author,
    );
    $form['feed_authorize'] = array(
      '#type' => 'hidden',
      '#title' => t('Authorize'),
      '#description' => t('Check that the author has permission to create the node.'),
      '#default_value' => TRUE, /* TODO: add permissions check */
    );
    $expire_period = drupal_map_assoc(
      array(
        FEEDS_EXPIRE_NEVER,
        60,
        180,
        300,
        3600,
        10800,
        21600,
        43200,
        86400,
        259200,
        604800,
        604800 * 4,
        604800 * 12,
        604800 * 24,
        31536000,
      ),
      'feeds_format_expire'
    );
    $form['feed_expire_period'] = array(
      '#type' => 'select',
      '#title' => t('Expire nodes'),
      '#options' => $expire_period,
      '#description' => t("Select after how much time nodes should be deleted/unpublished. The node's published date will be used for determining the node's age, see Mapping settings."),
      '#default_value' => !empty($source_config['feed_expire_period']) ? $source_config['feed_expire_period'] : FEEDS_EXPIRE_NEVER,
    );
    $form['feed_expire_action'] = array(
      '#type' => 'radios',
      '#title' => t('Action after expire period'),
      '#description' => t('Select action for expired nodes.'),
      '#options' => array(
        FEEDS_EXPIRE_ACTION_DELETE => 'Delete nodes after expired',
        FEEDS_EXPIRE_ACTION_UNPUBLISH => 'Unpublish nodes after expired',
      ),
      '#default_value' => !empty($source_config['feed_expire_action']) ? $source_config['feed_expire_action'] : FEEDS_EXPIRE_ACTION_UNPUBLISH,
    );
    $form['update_existing'] = array(
      '#type' => 'radios',
      '#title' => t('Update existing nodes'),
      '#description' => t('Select how existing nodes should be updated. Existing nodes will be determined using mappings that are a "unique target".'),
      '#options' => array(
        FEEDS_SKIP_EXISTING => 'Do not update existing nodes',
        FEEDS_REPLACE_EXISTING => 'Replace existing nodes',
        FEEDS_UPDATE_EXISTING => 'Update existing nodes (slower than replacing them)',
      ),
      '#default_value' => !empty($source_config['update_existing']) || (isset($source_config['update_existing']) && is_numeric($source_config['update_existing']) && $source_config['update_existing'] == 0) ? $source_config['update_existing'] : FEEDS_SKIP_EXISTING,
    );
    $form['feed_contributors'] = array(
      '#type' => 'textfield',
      '#title' => t('Contributors'),
      '#autocomplete_path' => 'entityreference/autocomplete/tags/field_penton_author/node/article/NULL',
      '#default_value' => !empty($source_config['feed_contributors']) ? $source_config['feed_contributors'] : '',
    );
    $all_roles = user_roles();
    $field_roles = field_info_field('field_penton_privacy_settings');
    foreach ($field_roles['settings']['roles'] as $role) {
      $privacy_options[$role] = $all_roles[$role];
    }
    $form['feed_privacy_settings'] = array(
      '#type' => 'select',
      '#title' => t('Privacy Settings'),
      '#options' => $privacy_options,
      '#default_value' => !empty($source_config['feed_privacy_settings']) ? $source_config['feed_privacy_settings'] : 1,
    );
    $form['feed_primary_category'] = array(
      '#type' => 'textfield',
      '#title' => t('Primary Category'),
      '#autocomplete_path' => 'taxonomy/autocomplete/field_penton_primary_category',
      '#default_value' => !empty($source_config['feed_primary_category']) ? $source_config['feed_primary_category'] : '',
    );
    $form['feed_secondary_category'] = array(
      '#type' => 'textfield',
      '#title' => t('Secondary Category'),
      '#autocomplete_path' => 'taxonomy/autocomplete/field_penton_primary_category',
      '#default_value' => !empty($source_config['feed_secondary_category']) ? $source_config['feed_secondary_category'] : '',
    );
    $form['feed_program'] = array(
      '#type' => 'textfield',
      '#title' => t('Program'),
      '#autocomplete_path' => 'taxonomy/autocomplete/field_penton_program',
      '#default_value' => !empty($source_config['feed_program']) ? $source_config['feed_program'] : '',
    );
    $form['feed_promote_on_site_lists_and_rss'] = array(
      '#type' => 'checkbox',
      '#title'  => t('Promote on Site List and RSS'),
      '#default_value' => !empty($source_config['feed_promote_on_site_lists_and_rss']) ? $source_config['feed_promote_on_site_lists_and_rss'] : FALSE,
    );
    $form['feed_google_news_flag'] = array(
      '#type' => 'checkbox',
      '#title'  => t('Google News Flag'),
      '#default_value' => !empty($source_config['feed_google_news_flag']) ? $source_config['feed_google_news_flag'] : FALSE,
    );
    $form['feed_press_release_flag'] = array(
      '#type' => 'checkbox',
      '#title'  => t('Press Release Flag'),
      '#default_value' => !empty($source_config['feed_press_release_flag']) ? $source_config['feed_press_release_flag'] : FALSE,
    );
    $form['feed_aggregated_content'] = array(
      '#type' => 'checkbox',
      '#title'  => t('Aggregated Content'),
      '#default_value' => !empty($source_config['feed_aggregated_content']) ? $source_config['feed_aggregated_content'] : TRUE,
    );
    $form['feed_native_advertising'] = array(
      '#type' => 'checkbox',
      '#title'  => t('Native Advertising/Marketing'),
      '#default_value' => !empty($source_config['feed_native_advertising']) ? $source_config['feed_native_advertising'] : FALSE,
    );
    $form['feed_syndicate'] = array(
      '#type' => 'checkbox',
      '#prefix' => '<div id="syndicate">',
      '#suffix' => '</div>',
      '#title'  => t('Syndicate (Atom)'),
      '#description' => t('If selected, all of the content that comes in as part of this feed will be available to our syndication partners.
      Un-check if this content should not be syndicated.'),
      '#default_value' => !empty($source_config['feed_syndicate']) ? $source_config['feed_syndicate'] : FALSE,
    );
    $form['feed_noindex'] = array(
      '#type' => 'checkbox',
      '#title'  => t('No index'),
      '#description' => t('Prevents search engines from indexing this page.'),
      '#default_value' => !empty($source_config['feed_noindex']) ? $source_config['feed_noindex'] : FALSE,
    );
    return $form;
  }

  /**
   * Validate the form.
   */
  public function sourceFormValidate(&$source_config) {
    $cleared_taxonomy = array();
    foreach (taxonomy_get_vocabularies(FEEDS_DEFAULT_CONTENT_TYPE) as $tax) {
      $tax_name = 'field_penton_' . $tax->machine_name;
      if (!empty($source_config['feed_taxonomy'][$tax_name])) {
        $cleared_taxonomy[$tax_name] = $source_config['feed_taxonomy'][$tax_name];
      }
    }
    $source_config['feed_bloomberg'] = (isset($_POST['feeds']['FeedsBloombergHTTPFetcher']['feed_bloomberg'])) ?
      $_POST['feeds']['FeedsBloombergHTTPFetcher']['feed_bloomberg'] : 0;
    $source_config['feed_taxonomy'] = $cleared_taxonomy;
    $source_config['feed_taxonomy'] = $cleared_taxonomy;
  }

  /**
   * Initialize source config.
   */
  private function initSourceConfig($feed_nid) {
    $conf_result = db_query('SELECT config FROM {feeds_source} WHERE feed_nid = :feed_nid', array(':feed_nid' => $feed_nid))->fetch();
    $config = unserialize($conf_result->config);
    $this->source_config = $config['FeedsPentonAggregatorProcessor'];
  }

  /**
   * Return mapping targets.
   */
  public function getMappingTargets() {
    $targets = penton_get_mapping_targets(FEEDS_DEFAULT_CONTENT_TYPE);
    foreach ($targets as $key => $target) {
      $targets[$key]['summary_callbacks'] = array();
    }
    return $targets;
  }

  /**
   * Create MD5 hash of item and mappings array.
   *
   * Include mappings as a change in mappings may have an affect on the item
   * produced.
   *
   * @return string
   *   Always returns a hash, even with empty, NULL, FALSE:
   *   Empty arrays return 40cd750bba9870f18aada2478b24840a
   *   Empty/NULL/FALSE strings return d41d8cd98f00b204e9800998ecf8427e
   */
  protected function hash($item) {
    static $serialized_mappings;
    if (!$serialized_mappings) {
      $serialized_mappings = serialize($this->config['mappings']);
    }
    return hash('md5', serialize($item) . $serialized_mappings);
  }

  /**
   * Override setTargetElement to operate on a target item that is a node.
   */
  public function setTargetElement(FeedsSource $source, $target_node, $target_element, $value) {
    if (in_array($target_element, array('url', 'guid'))) {
      $target_node->feeds_item->$target_element = $value;
    }
    elseif ($target_element == 'body') {
      $target_node->teaser = node_teaser($value);
      $target_node->body = $value;
    }
    elseif (in_array(
      $target_element,
      array('title', 'status', 'created', 'nid', 'uid'))
    ) {
      $target_node->$target_element = $value;
    }
  }

  /**
   * Return expiry time.
   */
  public function expiryTime() {
    return FEEDS_EXPIRE_NEVER;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    if ($author = user_load(array('name' => $values['author']))) {
      $values['author'] = $author->uid;
    }
    else {
      $values['author'] = 0;
    }
  }

  /**
   * Reschedule if expiry time changes.
   */
  public function configFormSubmit(&$values) {
    parent::configFormSubmit($values);
  }

}
