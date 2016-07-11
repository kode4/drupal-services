<?php
/**
 * @file
 * Data Table migration.
 * The naming  is concerned with legacy Data Table migration into new Articles.
 */

/**
 * Class PiscesDataTableMigration
 *
 * Migrate legacy Data Tables into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesDataTableMigration extends PentonArticleMigration {

  // Where to suck the image files to.
  const IMAGE_DEST_DIR = 'public://';
  const FILES_DEST_DIR = 'public://';

  /**
   * Map fields.
   *
   * @param array $arguments
   *   Array from migration setup.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies[] = 'Articles';
    $this->dependencies[] = 'Blogs';
    $this->dependencies[] = 'Datasheets';

    // Program mapping.
    $this->addFieldMapping('field_penton_program', 'field_content_source')
      ->sourceMigration('Program');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Publication date.
    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone');

    // Exclude from lists.
    $this->addFieldMapping('field_penton_allow_in_rss_feed', 'rssFlag');

    // Privacy level.
    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // Image and CSV mapping.
    $this->addFieldMapping('field_penton_link_media_feat_img', 'image_assets');
    $this->addFieldMapping('field_penton_link_media_feat_img:source_type')
      ->defaultValue('nid');

    $this->addFieldMapping('field_penton_link_media_entity', 'media_assets');
    $this->addFieldMapping('field_penton_link_media_entity:source_type')
      ->defaultValue('nid');

    // Set the asset migration fields.
    $this->createFileMigrateDirectory(self::IMAGE_DEST_DIR);
    $this->createFileMigrateDirectory(self::FILES_DEST_DIR);
  }

  /**
   * Prepare any migration is a field to field migration won't do.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $row
   *   Source data.
   *
   * @return bool
   *   Returns any changes to source data.
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Exclude from lists.
    if (isset($row->field_exclude_from_lists)) {
      $row->rssFlag = $this->includeInRSS($row->field_exclude_from_lists);
    }
    else {
      // Well there is no value so this is like saying it's set to zero and in
      // that case needs to be converted to 1.
      $row->rssFlag = 1;
    }

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);

    // Article Type.
    $row->articleTypes = $this->articleType("Data Table");

    // Create media asset from csv.
    $csvs = array();
    if (isset($row->field_csv_file)) {
      array_push($csvs, $row->field_csv_file);
    }

    // Get data associated with this csv.
    $query = $this->sourceDbConnection()
      ->select('penton_data_tables', 'pdt')
      ->fields('pdt', array('nid', 'data'));
    $query->where('pdt.nid=:nid', array(':nid' => $row->nid));
    $result = $query->execute();
    $data = $result->fetchObject();
    $data = unserialize($data->data);
    $media_assets = $this->csvMigration($csvs, self::FILES_DEST_DIR, variable_get('penton_migrate_asset_host'), $data, $row->created);

    // Create media asset from image promo.
    $image_assets = array();
    if (isset($row->field_image_promo)) {
      $credits = "";
      if (isset($row->field_image_promo_credits)) {
        $credits = $row->field_image_promo_credits;
      }
      $image_assets = $this->imagePromoMigration($row->nid, $row->field_image_promo, self::IMAGE_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $credits, $row->created);
    }

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        unset($row->field_content_source);
      }
    }

    $row->image_assets = $image_assets;
    $row->media_assets = $media_assets;
    $row->Assets = array_merge($media_assets, $image_assets);
  }

  /**
   * Create DataTableDetail pages.
   *
   * @author James Linnell james.linnell@ixus.com
   *
   * @param array $files
   *   All files associated with this node as an array.
   * @param string $local_dir
   *   The local directory to save to.
   * @param string $prod
   *   The production environment.
   * @param array $data
   *   Extra data needed to contruct the csv pages.
   *
   * @return array
   *   An array of node ids.
   */
  protected function csvMigration($files, $local_dir, $prod, $data, $created) {
    $nids = array();
    if (isset($files)) {
      // Get all the fids.
      foreach ($files as $key => $item) {
        $fid = $item;
        // Query the source db for the file.
        $file_info = $this->fileDetails($fid, $local_dir, $prod);
        $title = $file_info['title'];
        $newfile = $file_info['newfile'];

        $_node = array();
        // Node title.
        $_node['title'] = $title;
        // Set the media type.
        $_node['mimetype'] = 'datasheet';
        // Creation date.
        $_node['created'] = $created;

        if (strpos($newfile->filemime, 'text/csv') !== FALSE) {
          // We will also need the data to determine which columns are
          // displayed where.
          // The main page columns.
          if (isset($data['#settings']['#presets']['default']['use_col_array'])) {
            $columns = "";
            foreach ($data['#settings']['#presets']['default']['use_col_array'] as $column) {
              if (empty($columns)) {
                $columns = ($column - 2);
              }
              else {
                $columns = $columns . ", " . ($column - 2);
              }
            }
            $_node['main_columns'] = $columns;
            // Format the csvs to work with newline characters.
            $file_contents = file_get_contents($newfile->uri);
            $file_cont_new = str_replace("\r", "\n", $file_contents);

            if ($wrapper = file_stream_wrapper_get_instance_by_uri($newfile->uri)) {
              $realpath = $wrapper->realpath();
              file_put_contents(file_create_url($realpath), $file_cont_new);
            }
          }

          // Now lets look at the subpages.
          $sub_columns = "";
          if (array_key_exists('main_columns', $data['#settings']['#presets']['row'])) {
            $count = count($data['#settings']['#header_row']);
            $temp_array = array();
            for ($i = 0; $i < $count; $i++) {
              // Create an array of numbers from 0 to the array length.
              array_push($temp_array, $i);
            }

            $columns_m = array();
            foreach ($data['#settings']['#presets']['row']['main_columns'] as $key => $sub_column) {
              array_push($columns_m, $sub_column - 1);
            }

            // We need to convert the array of columns to keep into an array of
            // columns to exclude.
            foreach ($temp_array as $key_item) {
              $exclude = TRUE;
              foreach ($columns_m as $sub_column) {
                if ($sub_column == $key_item) {
                  $exclude = FALSE;
                  break;
                }
              }
              if ($exclude == TRUE) {
                if (empty($sub_columns)) {
                  if (($key_item - 1) != -1) {
                    $sub_columns = ($key_item - 1);
                  }
                }
                else {
                  $sub_columns = $sub_columns . ", " . ($key_item - 1);
                }
              }
            }

          }
          else {
            // Theres no sub columns specified. But if not all the main columns.
            $count = count($data['#settings']['#header_row']);
            $count_main = count($data['#settings']['#presets']['default']['use_col_array']);
            if ($count != $count_main) {
              $_node['datatable_sub'] = 0;
            }
          }

          $_node['detail_columns'] = $sub_columns;

        }

        // Prepare node for saving.
        $nid = $this->createMediaEntity($_node, $newfile);
        array_push($nids, $nid);
      }
    }
    // Return the new node IDs.
    return $nids;
  }

}
