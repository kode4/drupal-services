<?php
/**
 * @file
 * Base class for the Penton Migrations.
 */

/*
 * Class PentonArticleMigration
 *
 * Class is used as a base class for migration into D7 Articles.
 * It contains mapping and functions that are called for all article node
 * migrations.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
abstract class PentonArticleMigration extends DrupalNode6Migration {

  protected $sourcedbname = 'pisces';
  protected $destdbname = 'default';

  /**
   * Map fields.
   *
   * @param array $arguments
   *   Array from migration setup.
   */
  public function __construct($arguments) {
    include 'connection.inc';
    parent::__construct($arguments);
    $this->softDependencies = array('Categories', 'Program');
    $this->dependencies[] = 'Authors';
    $this->setHardDependencies(array());

    // Set highwater field to "changed" as we are dealing with nodes here.
    $this->setHighwaterField(array(
      'name' => 'changed',
      'alias' => 'n',
      'type' => 'int',
    ));

    // User id.
    $default_uid = 1;
    $this->removeFieldMapping('uid');
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('Users')
      ->defaultValue($default_uid);

    $this->removeFieldMapping('body:format');
    $this->addFieldMapping('body:format')
      ->defaultValue('full_html');

    // Category reference migration.
    $this->addFieldMapping('field_penton_primary_category', 'primary_tid')
      ->sourceMigration('Categories');
    $this->addFieldMapping('field_penton_primary_category:source_type')
      ->defaultValue('tid');
    $this->addFieldMapping('field_penton_secondary_category', 'secondary_cats')
      ->sourceMigration('Categories');
    $this->addFieldMapping('field_penton_secondary_category:source_type')
      ->defaultValue('tid');

    // Set legacy ID.
    $this->addFieldMapping('field_penton_legacy_id', 'nid');

    // Set UUID.
    $this->addFieldMapping('uuid', 'uuid')
      ->defaultValue('uuid');

    // Set meta Data.
    if ('metadata_pagetitle') {
      $this->addFieldMapping('metatag_title', 'metadata_pagetitle');
    }
    $this->addFieldMapping('metatag_canonical', 'metadata_canonical');
    $this->addFieldMapping('metatag_description', 'metadata_description');

  }

  /**
   * Extend the base D6 migration query.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @return \QueryConditionInterface
   *   The updated query.
   */
  protected function query() {
    // Get the default query.
    $query = parent::query();
    // Join the penton_UUID table.
    $query->innerJoin('penton_uuid', 'pu', 'n.nid=pu.id');
    $query->fields('pu', array('uuid'));
    $query->leftJoin('primary_term', 'pt', 'n.nid=pt.vid');
    $query->addField('pt', 'tid', 'primary_tid');
    $query->orderBy($this->newOnly ? 'n.nid' : 'n.changed');
    return $query;
  }

  /**
   * Source DB connection.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @return \DatabaseConnection
   *   The database connection.
   */
  protected function sourceDbConnection() {
    return Database::getConnection('default', $this->sourcedbname);
  }

  /**
   * Destination DB connection.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @return \DatabaseConnection
   *   The database connection.
   */
  protected function destDbConnection() {
    return Database::getConnection('default', $this->destdbname);
  }

  /**
   * Prepare the migration before saving.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $node
   *   The node object about to be saved.
   * @param \stdClass $row
   *   The source data.
   */
  public function prepare($node, stdClass $row) {
    // We previously set uid 1 to 0 because the user migration ignores it.
    // We now need to set this user back to 1.
    if ($node->uid == 0) {
      $row->uid = 1;
      $node->uid = 1;
    }
  }

  /**
   * Prepare any migration is a field to field migration won't do.
   *
   * @param object $row
   *   Source data.
   *
   * @return bool
   *   Returns any changes to source data.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @see MigrateSource::next()
   */
  public function prepareRow($row) {
    drush_print_r("Migrating Legacy node " . $row->nid);
    // In MigrateSource::next() we see under step 6 that when using highwater
    // marks, it actually calls the prepareRow method, which can take time,
    // especially on articles with a lot of processing. Let's help it with
    // checking the highwater field status ourselves and exit.
    if (!empty($this->highwaterField)) {
      if ($row->{$this->highwaterField['name']} < $this->getHighwater()) {
        // It is actually not important what we return here unless it's FALSE.
        return TRUE;
      }
    }

    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    if (isset($row->field_image_promo_portrait)) {
      if (isset($row->field_featured_image_credits)) {
        $row->body = $this->addPortraitImageToBody($row->nid, $row->field_image_promo_portrait[0], $row->body, $row->field_featured_image_credits[0]);
      }
      else {
        $row->body = $this->addPortraitImageToBody($row->nid, $row->field_image_promo_portrait[0], $row->body);
      }
    }

    if ($row->uid == 1) {
      $row->uid = '';
    }

    // Set metadata.
    $metadata = $this->metaData($row->nid);
    if ($metadata['pagetitle']) {
      $row->metadata_pagetitle = $metadata['pagetitle'];
    }
    if ($metadata['canonical']) {
      $row->metadata_canonical = $metadata['canonical'];
    }
    if ($metadata['description']) {
      $row->metadata_description = $metadata['description'];
    }

    // Remove primary term from secondary category.
    $cats = variable_get('penton_migrate_categories_vid');
    if ($row->$cats) {
      $temp_array = $row->$cats;
      if (($key = array_search($row->primary_tid, $temp_array)) !== FALSE) {
        unset($temp_array[$key]);
      }
      $row->secondary_cats = $temp_array;
    }
  }

  /**
   * Add the portrait image to the body if there is one.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $fid
   *   The file ID.
   * @param string $body
   *   The body text.
   * @param string $credits
   *   Associated image credits.
   *
   * @return string
   *   Return the amended body copy.
   */
  protected function addPortraitImageToBody($nid, $fid, $body, $credits = "") {
    $file = $this->fileDetails($fid, 'public://', variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'));
    $image_details = $this->imageDetails($nid, 'content_field_image_promo_portrait');
    // Create HTML5 link to be prepended to the body.
    if (!empty($image_details['description'])) {
      $file = '<img class="portrait_img" alt="' . substr(preg_replace("/[^A-Za-z0-9 ]/", '', strip_tags($image_details['description'])), 0, 511) . '" title="' . substr(preg_replace("/[^A-Za-z0-9 ]/", '', strip_tags($image_details['description'])), 0, 511) . '" src="' . file_create_url($file['newfile']->uri) . '" />';
    }
    else {
      $file = '<img class="portrait_img" src="' . file_create_url($file['newfile']->uri) . '" />';
    }
    $body = $file . '<p>' . $credits . '</p>' . $body;
    return $body;
  }

  /**
   * Db query to return the a tid  of the newly created program.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $program
   *   An array of node IDs.
   *
   * @return array
   *   An array of term IDs.
   */
  protected function rowGetProgramTID($program) {
    $tids = array();
    foreach ($program as $nid) {
      $query = $this->destDbConnection()
        ->select('field_data_field_penton_legacy_id', 'fdfpli')
        ->fields('fdfpli', array('entity_id'))
        ->where('fdfpli.field_penton_legacy_id_value=:nid', array(':nid' => $nid))
        ->execute();

      $row = $query->fetchObject();

      if (!empty($row)) {
        foreach ($row as $item) {
          array_push($tids, $item);
        }
      }
    }
    return $tids;
  }

  /**
   * Flip state of include in RSS flag around as it's is excluded in Pisces.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $value
   *   Source field value.
   *
   * @return int
   *   Return the value for the boolean field.
   */
  protected function includeInRSS($value) {
    if ($value[0] == 0) {
      $value = 1;
    }
    else {
      $value = 0;
    }
    return $value;
  }

  /**
   * Get and save the new file information.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $fid
   *   The file id.
   * @param string $local_dir
   *   The directory to save to.
   * @param string $prod
   *   The production environment.
   *
   * @return array
   *   An array of file details.
   */
  protected function fileDetails($fid, $local_dir, $prod) {
    // Query the source db for the file.
    $query = $this->sourceDbConnection()
      ->select('files', 'f')
      ->fields('f', array(
        'fid',
        'filename',
        'filepath',
        'filemime',
        'filesize',
        'status',
        'timestamp',
      ));
    $query->where('f.fid=:fid', array(':fid' => $fid));
    $result = $query->execute();
    $file = $result->fetchObject();
    $dir = dirname($file->filepath);
    $pos = strpos($dir, '/files');
    if ($pos != FALSE) {
      $dir_local = substr_replace($dir, "", 0, $pos + 6);
    }
    $filename = basename($file->filepath);
    $title = $file->filename;
    // Set the destination and source file locations.
    $download_file = $prod . '/' . $dir . '/' . urlencode($filename);
    // Set the destination and source file locations.
    $success = FALSE;
    if (!file_exists($local_dir . '/' . $dir_local)) {
      $old_umask = umask(0);
      $success = mkdir($local_dir . '/' . $dir_local, 0775, TRUE);
      umask($old_umask);
    }
    else {
      $success = TRUE;
    }
    // Create the source directory on the new system if it doesn't exist.
    if ($success == TRUE) {
      $destination_file = $local_dir . '/' . MigrateFileUri::urlencode($dir_local . '/' . $filename);
    }
    else {
      $destination_file = $local_dir . '/' . MigrateFileUri::urlencode($filename);
    }

    // Replace or add new file.
    try {
      if (!file_exists($destination_file)) {
        $newfile = system_retrieve_file(str_replace('+', '%20', $download_file), $destination_file, TRUE, FILE_EXISTS_REPLACE);
      }
      else {
        $newfile = system_retrieve_file(str_replace('+', '%20', $download_file), $destination_file, TRUE, FILE_EXISTS_RENAME);

      }
    }
    catch (Exception $e) {
      watchdog('node', 'Failed to retrieve file %filename during gallery migration.', array('%filename' => $filename), WATCHDOG_ALERT);
      $newfile = NULL;
    }

    $result = array();
    $result['title'] = $title;
    $result['newfile'] = $newfile;
    return $result;
  }

  /**
   * Creates some image media entities based on image Promo.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $images
   *   File IDs.
   * @param string $local_dir
   *   The directory to save to.
   * @param string $prod
   *   The production environment.
   * @param array $credits
   *   Array of image credits.
   *
   * @return array
   *   Return node IDs.
   */
  protected function imagePromoMigration($nid, $images, $local_dir, $prod, $credits, $created) {
    $nids = array();
    if (isset($images)) {
      // Get all the fids.
      foreach ($images as $key => $item) {
        $fid = $item;
        // Query the source db for the file.
        $file_info = $this->fileDetails($fid, $local_dir, $prod);
        $file_details = $this->imageDetails($nid, 'content_field_image_promo');
        $_node = array();
        if (isset($file_details['alt']) && $file_details['alt'] != "") {
          if (strlen($file_details['alt']) > 512) {
            $_node['alt'] = substr(preg_replace("/[^A-Za-z0-9 ]/", '', strip_tags($file_details['alt'])), 0, 511);
          }
          else {
            $_node['alt'] = preg_replace("/[^A-Za-z0-9 ]/", '', strip_tags($file_details['alt']));
          }
        }
        else {
          if (isset($file_details['description']) && $file_details['description'] != "") {
            $file_details['description'] = str_replace("&nbsp;", " ", $file_details['description']);
            $_node['alt'] = substr(preg_replace("/[^A-Za-z0-9 ]/", '', strip_tags($file_details['description'])), 0, 511);
          }
          else {
            $_node['alt'] = "";
          }
        }

        if (isset($file_details['description']) && $file_details['description'] != "") {
          $_node['description'] = $file_details['description'];
        }

        if (isset($file_details['title'])) {
          $_node['metatitle'] = $file_details['title'];
        }

        $title = $file_info['title'];
        $newfile = $file_info['newfile'];

        // Set the title.
        $_node['title'] = $title;
        // Set the media type.
        $_node['mimetype'] = 'image';
        // Add credits to the media asset.
        $_node['image_credits'] = $credits;
        // Creation date.
        $_node['created'] = $created;
        // Prepare node for saving.
        $nid = $this->createMediaEntity($_node, $newfile);
        array_push($nids, $nid);
      }
    }
    // Return the new node IDs.
    return $nids;
  }

  /**
   * Return details about the image attched to the node.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $nid
   *   The legacy node id.
   * @param string $table
   *   The database table to query.
   *
   * @return mixed
   *   An array of image data.
   */
  protected function imageDetails($nid, $table) {
    $field = str_replace('content_', '', $table) . '_data';
    $query = $this->sourceDbConnection()
      ->select($table, 'f')
      ->fields('f', array(
          $field,
        )
      );
    $query->where('f.nid=:nid', array(':nid' => $nid));
    $result = $query->execute();
    $file = $result->fetchObject();
    $file = unserialize($file->$field);
    return $file;
  }

  /**
   * Return the pagetitle, canonical and description metadata.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $source_nid
   *   Legacy nid.
   *
   * @return metadata
   *   An array of metadata.
   */
  protected function metaData($source_nid) {
    $query = $this->sourceDbConnection()
      ->select('page_title', 'pt')
      ->fields('pt', array('page_title'))
      ->condition('pt.type', 'node', '=')
      ->condition('pt.id', $source_nid, '=');
    $q = $query->execute();
    $page_title = $q->fetchAll();

    $query = $this->sourceDbConnection()
      ->select('nodewords', 'n')
      ->fields('n', array('content'))
      ->condition('n.id', $source_nid, '=')
      ->condition('n.name', 'description', '=')
      ->condition('n.content', '%' . db_like(';s:0:') . '%', 'NOT LIKE');
    $q = $query->execute();
    $description = $q->fetchAll();

    $query = $this->sourceDbConnection()
      ->select('nodewords', 'n')
      ->fields('n', array('content'))
      ->condition('n.id', $source_nid, '=')
      ->condition('n.name', 'canonical', '=')
      ->condition('n.content', '%' . db_like(';s:0:') . '%', 'NOT LIKE');
    $q = $query->execute();
    $canonical = $q->fetchAll();

    $metadata = array();
    foreach ($page_title as $title) {
      $metadata['pagetitle'] = $title->page_title;
    }
    foreach ($description as $desc) {
      $mdescription = unserialize($desc->content);
      $metadata['description'] = $mdescription['value'];
    }
    foreach ($canonical as $can) {
      $mcanonical = unserialize($can->content);
      $metadata['canonical'] = $mcanonical['value'];
    }

    return $metadata;
  }

  /**
   * Create a media asset of type whitepaper.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $pdfs
   *   File IDs.
   * @param string $local_dir
   *   The directory to save to.
   * @param string $prod
   *   The production environment.
   *
   * @return array
   *   An array of node ids.
   */
  protected function pdfMigration($pdfs, $local_dir, $prod, $created) {
    $nids = array();
    if (isset($pdfs)) {
      // Get all the fids.
      foreach ($pdfs as $key => $item) {
        $fid = $item;
        // Query the source db for the file.
        $file_info = $this->fileDetails($fid, $local_dir, $prod);
        $title = $file_info['title'];
        $newfile = $file_info['newfile'];

        $_node = array();
        // Set the title.
        $_node['title'] = $title;
        // Set the media type.
        $_node['mimetype'] = 'whitepaper';
        // Creation date.
        $_node['created'] = $created;
        // Prepare node for saving.
        $nid = $this->createMediaEntity($_node, $newfile);
        array_push($nids, $nid);
      }
    }
    // Return the new node IDs.
    return $nids;
  }

  /**
   * Create a media entity node.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $_node
   *   An array with node details.
   * @param null $newfile
   *   A file object.
   *
   * @return mixed
   *   Return a node id.
   * @throws \Exception
   */
  protected function createMediaEntity($_node, $newfile = NULL) {
    $node = new stdClass();
    $node->title = $_node['title'];
    $node->type = 'media_entity';
    // Sets some defaults. Invokes hook_prepare() and hook_node_prepare().
    node_object_prepare($node);
    // Or e.g. 'en' if locale is enabled.
    $node->language = LANGUAGE_NONE;
    $node->uid = 1;
    // (1 or 0): published or not.
    $node->status = 1;
    // (1 or 0): promoted to front page.
    $node->promote = 0;
    // 0 = comments disabled, 1 = read only, 2 = read/write.
    $node->comment = 0;
    // Set created date.
    if (isset($_node['created'])) {
      $node->created = $_node['created'];
    }
    // Add description.
    if (isset($_node['description'])) {
      $node->field_penton_media_caption[$node->language][0]['value'] = $_node['description'];
      $node->field_penton_media_caption[$node->language][0]['format']  = 'filtered_html';
    }
    if (isset($_node['summary'])) {
      $node->field_penton_content_summary[$node->language][0]['value'] = $_node['summary'];
      $node->field_penton_content_summary[$node->language][0]['format']  = 'filtered_html';
    }
    // Add mimetype.
    if (isset($_node['mimetype'])) {
      $node->field_penton_media_type[$node->language][0]['value'] = $_node['mimetype'];
    }
    // Add the file to the field.
    if ($newfile != NULL) {
      if ($_node['mimetype'] != 'image') {
        $node->field_penton_media_content[$node->language][0] = (array) $newfile;
        $node->field_penton_media_content[$node->language][0]['display'] = 1;
        $node->field_penton_media_content[$node->language][0]['description'] = $_node['title'];
      }
      else {
        $node->field_penton_media_image[$node->language][0] = (array) $newfile;
        if (isset($_node['alt'])) {
          $node->field_penton_media_image[$node->language][0]['alt'] = $_node['alt'];
        }
        if (isset($_node['metatitle'])) {
          $node->field_penton_media_image[$node->language][0]['title'] = $_node['metatitle'];
        }
      }
    }
    // Add image credits.
    if (isset($_node['image_credits'])) {
      $node->field_penton_media_credit[$node->language][0]['value'] = $_node['image_credits'];
    }
    // Add embed.
    if (isset($_node['embed'])) {
      $node->field_penton_media_embed[$node->language][0]['value'] = $_node['embed'];
    }
    // Add main page columns.
    if (isset($_node['main_columns'])) {
      $node->field_penton_main_page_columns['und'][0]['value'] = $_node['main_columns'];
    }
    // Add whether it requires sub pages..
    if (isset($_node['datatable_sub'])) {
      $node->field_penton_datatable_sub['und'][0]['value'] = $_node['datatable_sub'];
    }
    // Add detail page omitted columns.
    if (isset($_node['detail_columns'])) {
      $node->field_penton_detail_page_columns['und'][0]['value'] = $_node['detail_columns'];
    }

    // Prepare node for saving.
    node_save($node);

    return $node->nid;
  }

  /**
   * Function returns image details for desc, credits etc on the new nodes.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $images
   *   An array of image fids.
   *
   * @return array
   *   Image objects
   */
  protected function getImageDetails($images) {
    $image_data = array();
    $query = $this->sourceDbConnection()
      ->select('content_field_images', 'cfi')
      ->fields('cfi', array('field_images_fid', 'field_images_data'))
      ->condition('cfi.field_images_fid', $images, 'IN');
    $q = $query->execute();
    $results = $q->fetchAll();
    foreach ($results as $result) {
      array_push($image_data, $result->field_images_data);
    }

    return $image_data;
  }

  /**
   * Map the gating levels to the new levels.
   *
   * @param array $row
   *   The node data being migrated.
   *
   * @return int
   *   Return the Role ID
   */
  protected function prepareGating($row) {

    // We need to get the vid of the Gating vocab. On Waste360 this is 31 but
    // we can't be certain this is the same for all sites.
    $query = $this->sourceDbConnection()
      ->select('vocabulary', 'v')
      ->fields('v', array('vid', 'name'));
    $query->where('v.name=:name', array(':name' => 'Gating'));
    $result = $query->execute();
    $vocab = $result->fetchObject();
    $vid = $vocab->vid;

    // Now we know what the array is in the row so we can get the tids.
    $rid = DRUPAL_ANONYMOUS_RID;
    if (isset($row->$vid)) {
      $gating = $row->$vid;

      // This is actually only 1 value.
      $query = $this->sourceDbConnection()
        ->select('term_data', 'td')
        ->fields('td', array('tid', 'vid', 'name'));
      $query->where('td.tid=:level', array(':level' => end($gating)));
      $query->where('td.vid=:vid', array(':vid' => $vid));
      $result = $query->execute();
      $term = $result->fetchObject();

      // Check the terms against the gating mapping and send back the user role
      // gating required for the new system.
      // Anonymous User = 1.
      // Basic Registered = 2.
      // Advanced Registered = 3.
      // Paid Premium = 4.

      if (!empty($term)) {
        switch ($term->name) {
          case 'Public':
            $rid = DRUPAL_ANONYMOUS_RID;
            break;

          case 'Advisor Trend Monitor':
            $rid = DRUPAL_AUTHENTICATED_RID;
            break;

          case 'Expo East Subscriber':
            $rid = DRUPAL_AUTHENTICATED_RID;
            break;

          case 'Freemium':
            $rid = DRUPAL_AUTHENTICATED_RID;
            break;

          case 'Online Education':
            $rid = DRUPAL_AUTHENTICATED_RID;
            break;

          case 'Internal Video User Term':
            $rid = DRUPAL_AUTHENTICATED_RID;
            break;

          case 'Value My Practice':
            $rid = DRUPAL_AUTHENTICATED_RID;
            break;

          case 'NBJ Subscriber':
            $rid = PENTON_GATED_PAID_PREMIUM_RID;
            break;

          case 'Premium T&E':
            $rid = PENTON_GATED_PAID_PREMIUM_RID;
            break;

          default:
            $rid = DRUPAL_ANONYMOUS_RID;
            break;

        }
      }

    }

    return $rid;
  }

  /**
   * Delete any media asset associated to this node.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $nids
   *   An array of node ids.
   */
  public function prepareRollback($nids) {
    foreach ($nids as $nid) {
      $node = node_load($nid);
      // Media entities.
      if (isset($node->field_penton_link_media_entity['und'])) {
        foreach ($node->field_penton_link_media_entity['und'] as $asset) {
          drupal_set_message(check_plain(t("Rollback - Deleted Media Asset nid=")) . $asset['target_id'], 'status');
          node_delete($asset['target_id']);
        }
      }
      // Galleries.
      if (isset($node->field_penton_link_image_gallery['und'])) {
        foreach ($node->field_penton_link_image_gallery['und'] as $asset) {
          drupal_set_message(check_plain(t("Rollback - Deleted Media Asset nid=")) . $asset['target_id'], 'status');
          node_delete($asset['target_id']);
        }
      }
    }
  }

  /**
   * Return an article type based on the legacy sub content type.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $article_names
   *   Array of article types.
   *
   * @return array
   *   Return term ids.
   */
  protected function subcontent2articleType($article_names) {

    $articles = array(
      'article' => 'Article',
      'best_practices' => 'Best Practices',
      'commentary' => 'Commentary',
      'dealer_profiles' => 'Dealer Profiles',
      'education' => 'Education',
      'exclusive' => 'Exclusive',
      'humor' => 'Humor',
      'industry_awards' => 'Industry Awards',
      'industry_voices' => 'Industry Voices',
      'inforgraphic' => 'Infographic',
      'interview' => 'Interview',
      'new_to_market' => 'New to the Market',
      'news' => 'News',
      'product' => 'Product',
      'press_release' => 'Press Release',
      'sponsored' => 'Sponsored',
      'the_daily_brief' => 'The Daily Brief',
      'user_generated' => 'User Submitted Content',
      'video' => 'Video',
      'webinar' => 'Webinar',
      'white_paper' => 'White Paper',
    );

    $tids = array();
    foreach ($article_names as $article_type) {
      $name = $articles[$article_type];
      $term = taxonomy_get_term_by_name($name, 'article_type');
      if (isset($term)) {
        foreach ($term as $_term) {
          $tid = $_term->tid;
          array_push($tids, $tid);
        }
      }
    }
    return $tids;
  }

  /**
   * Return the Article type based on the content type.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param string $article_type
   *   The name of the article type.
   *
   * @return array
   *   Return the tid in an array.
   */
  protected function articleType($article_type) {

    $tids = array();
    $term = taxonomy_get_term_by_name($article_type, 'article_type');
    if (isset($term)) {
      foreach ($term as $_term) {
        $tid = $_term->tid;
        array_push($tids, $tid);
      }
    }
    return $tids;
  }

  /**
   * During migration, we want to suck down the files from production.
   *
   * Then store it so we have a copy of them in our filesystem. Easier than
   * scanning the production files directory which isn't divided into
   * directories. This checks and creates the directory where the sucked down
   * files are stored. This should be called in the constructor, so the
   * directory is created before any migration is done.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param string $dir
   *   Directory to create.
   */
  protected function createFileMigrateDirectory($dir) {
    // Check the directories.
    if (!file_exists($dir)) {
      $old_umask = umask(0);
      if (mkdir($dir, 0775, TRUE) === FALSE) {
        drupal_set_message(t('Could not create @dir error', array('@dir' => $dir)));
      }
      else {
        drupal_set_message(t('Created @dir', array('@dir' => $dir)));
      }
      umask($old_umask);
    }
  }

  /**
   * Return the legacy uuid.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $id
   *   The legacy node id.
   *
   * @return int
   *   Return the legacy uuid.
   */
  public static function migrateUUID($id, $source) {
    $uuid = "";

    $query = $source
      ->select('penton_uuid', 'pu')
      ->fields('pu', array('uuid'));
    $query->where('pu.id=:id', array(':id' => $id));
    $query->where('pu.entity_type=:type', array(':type' => 'node'));
    $result = $query->execute();
    $uuid = $result->fetchObject();
    return $uuid->uuid;
  }

  /**
   * Implementation of Migration::createStub().
   *
   * @param object $migration
   *   Migration object.
   *
   * @return array|bool
   *   Return Stub created.
   */
  protected function createStub($migration, $source_key) {

    // Allowed legacy import types.
    $types = array(
      'article',
      'blog',
      'datasheet',
      'data_table',
      'gallery',
      'press_release',
      'video',
      'link',
    );

    // Well this is unfortunate but I can't think of any other way to do it
    // right now. As there is related content that is not being migrated we
    // have to make sure it is the correct type before building the stub.
    $query = $this->sourceDbConnection()
      ->select('node', 'n')
      ->fields('n', array());
    $query->where('n.nid=:nid', array(':nid' => $source_key[0]));
    $result = $query->execute();
    $refnode = $result->fetchObject();

    if (in_array($refnode->type, $types)) {
      migrate_instrument_start('DrupalNodeMigration::createStub');
      $node = new stdClass();
      $node->title = t('Stub');
      $node->body = array(LANGUAGE_NONE => array(array("value" => t('Stub body'))));
      $node->type = $this->destination->getBundle();
      $node->uid = 1;
      node_save($node);
      migrate_instrument_stop('DrupalNodeMigration::createStub');
      if (isset($node->nid)) {
        return array($node->nid);
      }
      else {
        return FALSE;
      }
    }
    else {
      if ($this->sourceValues->nid) {
        watchdog('node', '%node has a related content reference to an illegal legacy node type. Referenced item not migrated. Parent legacy nid = %node. Referenced legacy nid = %ref.', array(
          '%node' => $this->sourceValues->nid,
          '%ref' => $source_key[0],
        ), WATCHDOG_NOTICE);
      }
      return FALSE;
    }
  }

  /**
   * Adapted from https://www.drupal.org/node/1096132.
   *
   * Migrations do not handle multiple migration sources well. So this is needed
   * to deal with that.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param mixed $source_migrations
   *   An array of source migrations.
   * @param mixed $source_keys
   *   The source IDs.
   * @param null $default
   *   Default value.
   * @param null $migration
   *   The migration object.
   *
   * @return array|mixed|null
   *   Return an array of ids.
   */
  protected function handleSourceMigration($source_migrations, $source_keys, $default = NULL, $migration = NULL) {
    $mig_result = array();
    if ((is_array($source_migrations) && (!empty($source_keys)))) {
      // Have an array of objects
      // So unfortunately another call to the db.
      $query = $this->sourceDbConnection()
        ->select('node', 'n')
        ->fields('n')
        ->condition('n.nid', $source_keys, 'IN');
      $q = $query->execute();
      $results = $q->fetchAll();
      foreach ($results as $result) {
        if (!empty($result)) {
          switch ($result->type) {
            case 'blog':
              $partial_result = parent::handleSourceMigration($source_migrations[1], $result->nid, $default, $migration);
              break;

            case 'datasheet':
              $partial_result = parent::handleSourceMigration($source_migrations[2], $result->nid, $default, $migration);
              break;

            case 'data_table':
              $partial_result = parent::handleSourceMigration($source_migrations[3], $result->nid, $default, $migration);
              break;

            case 'gallery':
              $partial_result = parent::handleSourceMigration($source_migrations[4], $result->nid, $default, $migration);
              break;

            case 'press_release':
              $partial_result = parent::handleSourceMigration($source_migrations[5], $result->nid, $default, $migration);
              break;

            case 'video':
              $partial_result = parent::handleSourceMigration($source_migrations[6], $result->nid, $default, $migration);
              break;

            case 'link':
              $partial_result = parent::handleSourceMigration($source_migrations[7], $result->nid, $default, $migration);
              break;

            default:
              $partial_result = parent::handleSourceMigration($source_migrations[0], $result->nid, $default, $migration);
              break;

          }
          if (!is_array($partial_result)) {
            $mig_result[] = $partial_result;
          }
          else {
            $mig_result = array_merge($mig_result, $partial_result);
          }
        }
      }
    }
    else {
      $mig_result = parent::handleSourceMigration($source_migrations, $source_keys, $default, $migration);
    }
    return $mig_result;
  }

  /**
   * Ensure source node id corresponds to a term in destination.
   *
   * @param int $source_nid
   *   Node id in source db.
   *
   * @return bool
   *   Returns TRUE if the node is mapped, FALSE otherwise.
   */
  protected function nodeIsMapped($source_nid) {
    $count = db_select('migrate_map_program', 'map')
      ->fields('map', array('sourceid1'))
      ->condition('sourceid1', $source_nid, '=')
      ->condition('needs_update', 0, '=')
      ->countQuery()
      ->execute()
      ->fetchField();

    return $count > 0 ? TRUE : FALSE;
  }

}

/**
 * Class PentonMigrateUuidHandler
 *
 * Class is used to create a handler for the uuid field in the term and user
 * tables.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PentonMigrateUuidHandler extends MigrateDestinationHandler {
  /**
   * Register types.
   */
  public function __construct() {
    $this->registerTypes(array('user', 'comment', 'taxonomy_term'));
  }

  /**
   * Register new fields.
   */
  public function fields() {
    if (module_exists('uuid')) {
      return array(
        'uuid' => t('Universally Unique Identifier'),
      );
    }
    else {
      return array();
    }
  }

}

/**
 * Class PentonMigrateUuidNodeHandler
 *
 * Class is used to create a handler for the uuid field in the node table.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PentonMigrateUuidNodeHandler extends MigrateDestinationHandler {
  /**
   * Register Node tables.
   */
  public function __construct() {
    $this->registerTypes(array('node', 'node_revision'));
  }

  /**
   * Register new fields.
   */
  public function fields() {
    if (module_exists('uuid')) {
      return array(
        'uuid' => t('Universally Unique Identifier'),
        'vuuid' => t('Universally Unique IDentifier (revision)'),
      );
    }
    else {
      return array();
    }
  }

}
