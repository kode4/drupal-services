<?php
/**
 * @file
 * Code for the Penton Datasheets that are concerned with hook_node functions.
 */

/**
 * Implements hook_node_presave().
 *
 * Anything related to pre saving the node.
 * Sets the article to be a book if it is a datasheet type.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
function penton_datasheet_node_presave($node) {
  $parent_flag = FALSE;
  // Check if the node type is article & there's media entity attached.
  if ($node->type == 'article' && !empty($node->field_penton_link_media_entity['und'][0])) {
    foreach ($node->field_penton_link_media_entity['und'] as $asset) {
      $media = node_load($asset['target_id']);
      // Determine if this is a csv type.
      if (isset($media->field_penton_media_type['und'])) {
        switch ($media->field_penton_media_type['und'][0]['value']) {
          case 'datasheet':
            // Finally make sure the mimetype is correct. and that it exists.
            if (!empty($media->field_penton_media_content['und'][0])) {
              if ($media->field_penton_media_content['und'][0]['filemime'] == 'text/csv') {
                // Good to go.
                // Check if the master column is empty. If it is there's no
                // need to turn into a book.
                if ($media->field_penton_datatable_sub['und'][0]['value'] != 0
                    && !empty($media->field_penton_main_page_columns['und'][0])
                    && $parent_flag != TRUE
                    && !empty($node->book['nid'])
                    && $node->book['nid'] === "new"
                    && ($node->book['bid'] === "" || $node->book['bid'] === "0")) {
                  // Lets assume all csvs are to exist under the same parent
                  // and set this article as the book.
                  // This is a new article so we will need to assign it
                  // as a parent unless we've already set it or it exists
                  // already.
                  // Then it can be made into a book.
                  $node->book['bid'] = "new";
                  $parent_flag = TRUE;
                }
              }
              else {
                // The mimetype does not match the selected media type.
                watchdog("Penton Article", "The mimetype does not match the selected media type on the created Media Asset", array(), WATCHDOG_ERROR);
              }
            }
            else {
              // This is empty so we will send an alert to watchdog.
              watchdog("Penton Article", "The datasheet mediatype has been set but no file uploaded", array(), WATCHDOG_ERROR);
            }
            break;

          default:
            if (empty($media->field_penton_media_content['und'][0]) && empty($media->field_penton_media_image['und'][0])) {
              // Just set a default error message if the media asset has no
              // file.
              watchdog("Penton Article", "The media asset has been created but no file uploaded", array(), WATCHDOG_NOTICE);
            }
            break;

        }
      }
    }
  }
}

/**
 * Implements hook_node_insert().
 *
 * When the article is saved, we need to create the sub pages if this is an
 * article with a datasheet.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
function penton_datasheet_node_insert($node) {
  if ($node->type == 'article') {
    // Check if a a media entity has been associated.
    if (!empty($node->field_penton_link_media_entity['und'][0])) {
      // There is a media entity attached to this article.
      // They maybe multiple assets referenced so we have to go through each.
      foreach ($node->field_penton_link_media_entity['und'] as $asset) {
        $media = node_load($asset['target_id']);
        // Determine if this is a csv type.
        if (isset($media->field_penton_media_type['und']) && $media->field_penton_media_type['und'][0]['value'] == 'datasheet') {
          // Finally make sure the mimetype is correct. and that it exists.
          if (!empty($media->field_penton_media_content['und'][0])) {
            if ($media->field_penton_media_content['und'][0]['filemime'] == 'text/csv') {
              _penton_datasheet_init($node);
            }
            else {
              // This is not a csv file so we will not process anything.
              watchdog("Penton Datasheet", "The media asset has been created but with the wrong file type, no tables created", array(), WATCHDOG_NOTICE);
            }
          }
          else {
            // There is no file so we cannot process it.
            watchdog("Penton Datasheet", "The media asset has been created but no file uploaded, no tables created", array(), WATCHDOG_NOTICE);
          }
        }
      }
    }
  }
}

/**
 * Implements hook_node_update().
 *
 * When the article is updated, we may need to do something if the datasheet
 * has been updated.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
function penton_datasheet_node_update($node) {
  if ($node->type == 'article') {
    // Check if a a media entity has been associated.
    if (!empty($node->field_penton_link_media_entity['und'][0])) {
      // There is a media entity attached to this article.
      // They maybe multiple assets referenced so we have to go through each.
      foreach ($node->field_penton_link_media_entity['und'] as $asset) {
        $media = node_load($asset['target_id']);
        // Determine if this is a csv type.
        if ($media->field_penton_media_type['und'][0]['value'] == 'datasheet') {
          // Finally make sure the mimetype is correct. and that it exists.
          if (!empty($media->field_penton_media_content['und'][0])) {
            if ($media->field_penton_media_content['und'][0]['filemime'] == 'text/csv') {
              _penton_datasheet_delete_all($node->nid);
              _penton_datasheet_init($node);
            }
            else {
              // This is not a csv file so we will not process anything.
              watchdog("Penton Datasheet", "The media asset has been created but with the wrong file type, nothing updated", array(), WATCHDOG_NOTICE);
            }
          }
          else {
            // There is no file so we cannot process it.
            watchdog("Penton Datasheet", "The media asset has been created but no file uploaded, nothing updated", array(), WATCHDOG_NOTICE);
          }
        }
      }
    }
  }
}

/**
 * Implements hook_node_delete().
 *
 * When a datasheet article is deleted we need to delete it's table and all of
 * it's children.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
function penton_datasheet_node_delete($node) {
  // Delete the children and the parent table.
  if ($node->type == 'article' && !empty($node->field_penton_link_media_entity['und'][0])) {
    // There is a media entity attached to this article so we can do
    // something with it.
    // They maybe multiple assets referenced so we have to go through each.
    foreach ($node->field_penton_link_media_entity['und'] as $asset) {
      $media = node_load($asset['target_id']);
      // Determine if this is a csv type.
      if ($media->field_penton_media_type['und'][0]['value'] == 'datasheet') {
        _penton_datasheet_delete_all($node->nid);
      }
    }
  }
}

/**
 * Initiate the datasheet functionality.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param object $node
 *   The node object.
 */
function _penton_datasheet_init($node) {
  // Now the parent article has been created so we need to set about
  // manipulating the data and creating nodes.
  // Make sure everything is ok to get started.
  $data = _penton_datasheet_datasheet_node($node);

  $omitted_columns = array();
  if ($data[0] == "TRUE") {
    // $data will be an array with all associated files.
    // remove the first key.
    array_shift($data);
    foreach ($data as $asset) {
      $master_columns = array();
      if (array_key_exists('master_columns', $asset)) {
        // We have been explicitly told by the user not to create sub pages.
        if ($asset['sub_pages'] != 0) {
          if ($asset['master_columns'] != "") {
            // It has been specified that the master table will not show all
            // columns, therefore there must be sub pages which need to be
            // created first so nids can be used in the master table for links.
            $master_columns = explode(",", $asset['master_columns']);
            $master_columns = _penton_datasheet_excel_columns_to_numeric($master_columns);
            $table = _penton_datasheet_csv_to_array($asset['fid']);
            $omitted_columns = array();
            if (array_key_exists('omitted_columns', $asset)) {
              if ($asset['omitted_columns'] != "") {
                // So there will be some ommitted columns from each page.
                $omitted_columns = explode(",", $asset['omitted_columns']);
                $omitted_columns = _penton_datasheet_excel_columns_to_numeric($omitted_columns);
              }
            }
            // Send the data to start creating nodes.
            // Create sub pages.
            $nids = _penton_datasheet_create_tables($node->nid, $master_columns, $table, $omitted_columns, FALSE);
          }
          else {
            // The master table will show all columns so we won't need child
            // pages.
            $table = _penton_datasheet_csv_to_array($asset['fid']);
            $master = _penton_datasheet_create_tables($node->nid, $master_columns, $table, $omitted_columns, TRUE);
          }
        }
        else {
          $master_columns = explode(",", $asset['master_columns']);
          $master_columns = _penton_datasheet_excel_columns_to_numeric($master_columns);
          $table = _penton_datasheet_csv_to_array($asset['fid']);
          $master = _penton_datasheet_create_tables($node->nid, $master_columns, $table, $omitted_columns, TRUE);
        }
      }
      else {
        // The master table will show all columns so we won't need child pages.
        // Create master page table.
        $table = _penton_datasheet_csv_to_array($asset['fid']);
        $master = _penton_datasheet_create_tables($node->nid, $master_columns, $table, $omitted_columns, TRUE);
      }
    }
  }
}

/**
 * Implements hook_node_view().
 *
 * Used to display the table on datasheet detail pages.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
function penton_datasheet_node_view($node, $view_mode, $langcode) {
  if ($view_mode === 'full') {
    // Retrieve & process table data.
    if ($node->type === 'data_table_detail' || $node->type === 'article' && penton_core_node_subtype($node->nid) === 'data-table') {
      $table_data = _penton_datasheet_get_table_data($node->nid);
      // Process tokens.
      $node->datasheet_tokens = array_fill_keys(penton_datasheet_get_tokens(), NULL);
      foreach ($node->datasheet_tokens as $token => &$token_value) {
        foreach ($table_data['header_data'] as $i => $th) {
          if (stripos($th, $token) !== FALSE) {
            $token_value = array(
              'label' => $th,
              'value' => current($table_data['array_data'])[$i],
            );
            if ($node->type === 'data_table_detail') {
              // If detail page -- remove TH and respective TD from the table.
              unset($table_data['header_data'][$i]);
              unset($table_data['array_data'][0][$i]);
            }
          }
        }
      }
      $node->content['table_field'] = array(
        '#node' => $node->nid,
        '#markup' => _penton_datasheet_return_table($table_data, $node),
      );
    }
    // Then do some preparations for the template.
    if ($node->type === 'data_table_detail') {
      list($node->parent_nid, $node->prev_nid, $node->next_nid) = _penton_datasheet_entry_relatives($node->nid);
      $node->parent_node = node_load($node->parent_nid);
    }
    if ($node->type === 'article' && penton_core_node_subtype($node->nid) === 'data-table') {
      $scripts_scope = is_ajax() ? 'ajax' : 'header';
      drupal_add_js(drupal_get_path('module', 'penton_datasheet') . '/js/jquery.tablesorter.min.js', ['type' => 'file', 'scope' => $scripts_scope]);
      drupal_add_js(drupal_get_path('module', 'penton_datasheet') . '/js/datasheet.js', ['type' => 'file', 'scope' => $scripts_scope]);
    }
  }
}

/**
 * Implements theme_preprocess_table().
 */
function penton_datasheet_preprocess_table(&$variables) {
  // Limit to only data tables.
  if (isset($variables['datasheet_mode'])) {
    $fields_to_show = array();
    $article = node_load(isset($variables['parent_nid']) ? $variables['parent_nid'] : $variables['article_nid']);
    $article_meta = entity_metadata_wrapper('node', $article, array('bundle' => 'article'));
    $datasheet_node = $article_meta->field_penton_link_media_entity->get(0);
    if ($variables['datasheet_mode'] === 'detail' && $datasheet_node->value()) {
      // Detail page.
      if ($datasheet_node->field_penton_detail_page_columns->value()) {
        // Remove blacklisted fields.
        $exclude_fields = array_map('trim', explode(',', $datasheet_node->field_penton_detail_page_columns->value()));
      }
      else {
        // Remove blacklisted fields.
        $exclude_fields = array();
      }
      $variables['rows'] = array_filter($variables['rows'], function($v, $k) use ($exclude_fields) {
        return !in_array($v[0], $exclude_fields) && !in_array($k + 1, $exclude_fields);
      }, ARRAY_FILTER_USE_BOTH);
    }
    elseif ($variables['datasheet_mode'] !== 'detail') {
      // Table page.
      $all_columns = array_map('trim', array_keys($variables['header']));
      if ($variables['datasheet_mode'] === 'preview') {
        // Show only first 3 rows for infinite scroll mode.
        $variables['rows'] = array_slice($variables['rows'], 0, 3);
      }
      // Leave only whitelisted fields.
      if ($datasheet_node->value() && $datasheet_node->field_penton_main_page_columns->value()) {
        $include_fields = explode(',', $datasheet_node->field_penton_main_page_columns->value());
        foreach ($include_fields as $col_name) {
          $col_name = trim($col_name);
          $offset = is_numeric($col_name) && array_key_exists($col_name - 1, $all_columns) ? $col_name - 1 : array_search($col_name, $all_columns);
          if ($offset !== FALSE) {
            $fields_to_show[$offset] = $all_columns[$offset];
          }
        }
      }
    }

    // Now, remove everything except the allowed columns.
    if ($fields_to_show) {
      // If key of first row is proper nid, <tr> can be clickable.
      $is_row_clickable = key($variables['rows']) > 0 ? TRUE : FALSE;
      $first_column_index = key($fields_to_show);
      $rows = array();
      $header = array();
      foreach ($fields_to_show as $i => $col_name) {
        $header[$col_name] = $variables['header'][$col_name];
        $header[$col_name]['data'] .= ' <i class="fa fa-sort"></i>';
        foreach ($variables['rows'] as $j => $row) {
          $td_text = trim($row[$i]);
          if ($is_row_clickable) {
            if ($i === $first_column_index) {
              $td_text = l($td_text, 'node/' . $j);
            }
            $rows[$j]['data-link'] = url('node/' . $j);
            $rows[$j]['class'] = array('row-clickable');
          }
          $rows[$j]['data'][$i]['data'] = '<p>' . $td_text . '</p>';
        }
      }
      $variables['rows'] = $rows;
      $variables['header'] = $header;
    }

  }
}

/**
 * Implements hook_preprocess_node().
 */
function penton_datasheet_preprocess_node(&$variables) {
  $node = $variables['node'];
  if ($variables['view_mode'] === 'full' && $node->type === 'data_table_detail') {
    $variables['data_rank'] = $node->datasheet_tokens['[Rank]'] ? $node->datasheet_tokens['[Rank]']['value'] : NULL;
    $variables['data_logo'] = $node->datasheet_tokens['[Logo]'] ? $node->datasheet_tokens['[Logo]']['value'] : NULL;
    $variables['data_subtitle'] = $node->datasheet_tokens['[Subtitle]'] ? $node->datasheet_tokens['[Subtitle]']['value'] : NULL;
    $variables['data_website'] = $node->datasheet_tokens['[Website]'] ? $node->datasheet_tokens['[Website]']['value'] : NULL;
    if ($variables['data_website']) {
      $variables['data_website_view'] = preg_replace('#^(http:\/\/|https:\/\/|\/\/)#i', '', $variables['data_website']);
      if (!preg_match('#^(http:\/\/|https:\/\/|\/\/)#i', $variables['data_website'])) {
        $variables['data_website'] = 'http://' . $variables['data_website'];
      }
    }
    $variables['data_items'] = [];
    $variables['data_featured'] = [
      'attributes' => ['class' => ['data-featured']]
    ];
    foreach ($node->datasheet_tokens as $key => $value) {
      if (strpos($key, '[Item') === 0 && $value) {
        $variables['data_items'][] = $value['value'];
      }
      elseif (strpos($key, '[Featured') === 0 && $value) {
        $variables['data_featured']['rows'][] = [_penton_datasheet_stip_tokens($value['label']), $value['value']];
      }
    }
  }
}

/**
 * Strips out [tokens] from a srting.
 *
 * @param string $string
 *   String with tokens
 *
 * @return string
 *   Clean string
 */
function _penton_datasheet_stip_tokens($string) {
  $string = preg_replace('#\[.+?\]#', '', $string);
  return $string;
}
