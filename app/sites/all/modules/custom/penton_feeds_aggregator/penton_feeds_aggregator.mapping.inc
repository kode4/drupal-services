<?php
/**
 * @file
 * Feed mappings.
 */

/**
 * Menu callback; displays the aggregator administration page.
 */
function penton_mapping_table() {
  if (is_ajax()) {
    drupal_json(penton_mapping_ajax_proccesor());
  }
}

/**
 * Displays the aggregator administration page.
 *
 * @return string
 *   The page HTML.
 */
function penton_mapping_ajax_proccesor() {
  $output = array();
  switch ($_POST['action']) {
    case 'targets':
      $output = array(
        'targets' => penton_get_mapping_targets($_POST['type']),
        'default_mapping' => penton_default_mappings($_POST['type']),
        'tax_vocabs' => taxonomy_get_vocabularies($_POST['type']),
      );
      break;

    case 'brands':
      $output = get_brands_options();
      break;
  }
  return $output;
}

/**
 * Returns brands options.
 */
function get_brands_options() {
  $brands = array();
  // Brands content type.
  $q = db_query('SELECT nid FROM {node} WHERE type=:type', array(':type' => 'content_source'));
  while ($obj = $q->fetch()) {
    $brands[] = node_load($obj->nid);
  }
  $c = count($brands);
  $brand_options = array();
  $brand_options[-1] = 'Select brand';
  for ($i = 0; $i < $c; $i++) {
    $brand_options[$brands[$i]->nid] = $brands[$i]->title;
  }
  return $brand_options;
}

/**
 * Returns default mappings for requested content type.
 */
function penton_default_mappings($content_type) {
  $targets = penton_get_mapping_targets($content_type);
  $out = array(
    array('source' => 'timestamp', 'target' => 'created'),
    array('source' => 'timestamp', 'target' => 'field_penton_published_datetime'),
    array('source' => 'summary', 'target' => 'field_penton_content_summary'),
    array('source' => 'description', 'target' => 'body'),
    array('source' => 'title', 'target' => 'title'),
    array('source' => 'guid', 'target' => 'guid'),
    array('source' => 'author_name', 'target' => 'field_byline'),
    array('source' => 'url', 'target' => 'url'),
  );
  switch ($content_type) {
    case 'aggregated_content':
      array_push($out,
         array('source' => 'guid', 'target' => 'field_guid'),
         array('source' => 'url', 'target' => 'field_source_url')
      );
      break;

    case 'press_release':
      array_push($out,
        array('source' => 'description', 'target' => 'teaser')
      );
      break;

  }
  $new_out = array();
  foreach ($out as $k => $o) {
    if (isset($targets[$o['target']])) {
      $new_out[] = $o;
    }
  }
  return $new_out;
}

/**
 * Return available mapping targets.
 */
function penton_get_mapping_targets($content_type) {
  $targets = array(
    'title' => array(
      'name' => t('Title'),
      'description' => t('The title of the node.'),
    ),
  );
  // Include body field only if available.
  $type = node_type_get_types();
  $type = empty($type[$content_type]) ? FALSE : $type[$content_type];
  if (!empty($type->has_body)) {
    if ($type->has_body) {
      // Using 'teaser' instead of 'body' forces entire content above the break.
      $targets['body'] = array(
        'name' => t('Body'),
        'description' => t('The body of the node. The teaser will be the same as the entire body.'),
      );
      // Using 'teaser' instead of 'body' forces entire content above the break.
      $targets['teaser'] = array(
        'name' => t('Teaser'),
        'description' => t('The teaser.'),
      );
    }
  }
  $targets += array(
    'nid' => array(
      'name' => t('Node ID'),
      'description' => t('The nid of the node. NOTE: use this feature with care, node ids are usually assigned by Drupal.'),
      'optional_unique' => TRUE,
    ),
    'uid' => array(
      'name' => t('User ID'),
      'description' => t('The Drupal user ID of the node author.'),
    ),
    'user_name' => array(
      'name' => t('Username'),
      'description' => t('The Drupal username of the node author.'),
    ),
    'user_mail' => array(
      'name' => t('User email'),
      'description' => t('The email address of the node author.'),
    ),
    'status' => array(
      'name' => t('Published status'),
      'description' => t('Whether a node is published or not. 1 stands for published, 0 for not published.'),
    ),
    'created' => array(
      'name' => t('Published date'),
      'description' => t('The UNIX time when a node has been published.'),
    ),
    'url' => array(
      'name' => t('URL'),
      'description' => t('The external URL of the node. E. g. the feed item URL in the case of a syndication feed. May be unique.'),
      'optional_unique' => TRUE,
    ),
    'guid' => array(
      'name' => t('GUID'),
      'description' => t('The external GUID of the node. E. g. the feed item GUID in the case of a syndication feed. May be unique.'),
      'optional_unique' => TRUE,
    ),
  );
  $fields = field_info_instances('node', $content_type);
  foreach ($fields as $field_key => $field) {
    $targets += array(
      $field_key => array(
        'name' => $field['field_name'],
        'type' => $field['widget']['type'],
      ),
    );
  }
  drupal_alter('feeds_node_processor_targets', $targets, $content_type);
  return $targets;
}
