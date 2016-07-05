<?php
/**
 * @file
 * Code for the Penton Articles that are concerned with the datasheet
 * functionality
 */

/**
 * Checks to see that the node displays a datasheet and that everything is ok.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param object $node
 *   The node object
 *
 * @return object
 *   Array of fids
 */
function _penton_datasheet_datasheet_node($node) {
  $csvs = array();
  $csvs[0] = "FALSE";
  $key = 1;
  if ($node->type == 'article') {
    // Check if a a media entity has been associated.
    if (!empty($node->field_penton_link_media_entity['und'][0])) {
      foreach ($node->field_penton_link_media_entity['und'] as $asset) {
        // Load the media.
        $media = node_load($asset['target_id']);
        // Determine if this is a csv type.
        switch ($media->field_penton_media_type['und'][0]['value']) {
          case 'datasheet':
            // Finally make sure the mimetype is correct. and that it exists.
            if (!empty($media->field_penton_media_content['und'][0])) {
              if ($media->field_penton_media_content['und'][0]['filemime'] == 'text/csv') {
                $csvs[0] = "TRUE";
                if (!empty($media->field_penton_main_page_columns['und'][0]) && $media->field_penton_main_page_columns['und'][0]['value'] != NULL) {
                  $csvs[$key]['master_columns'] = $media->field_penton_main_page_columns['und'][0]['value'];
                }
                $csvs[$key]['fid'] = $media->field_penton_media_content['und'][0]['fid'];
                $csvs[$key]['sub_pages'] = $media->field_penton_datatable_sub['und'][0]['value'];
                if (!empty($media->field_penton_detail_page_columns['und'][0]) && $media->field_penton_detail_page_columns['und'][0]['value'] != NULL) {
                  $csvs[$key]['omitted_columns'] = $media->field_penton_detail_page_columns['und'][0]['value'];
                }
                $key++;
              }
              else {
                watchdog("Penton Article", "The mimetype does not match the selected media type on the created Media Asset", array(), WATCHDOG_ERROR);
              }
            }
            else {
              // The file doesn't exist.
              watchdog("Penton Article", "The media asset has been created but no file uploaded", array(), WATCHDOG_NOTICE);
            }
            break;

          default:
            if (empty($media->field_penton_media_content['und'][0])) {
              // Just set a default error message if the media asset has no
              // file.
              // This is used no matter the media-type.
              watchdog("Penton Article", "The media asset has been created but no file uploaded", array(), WATCHDOG_NOTICE);
            }
            break;
        }
      }
    }
  }
  return $csvs;
}

/**
 * Collect the data and formulate into arrays and nodes.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param int $pid
 *   Original parent ID
 * @param object $master_columns
 *   Master columns required.
 * @param object $table_data
 *   Table data.
 * @param object $omitted_columns
 *   Omitted columns in sub pages.
 *
 * @return bool
 *   Return empty boolean.
 */
function _penton_datasheet_create_tables($pid, $master_columns, $table_data, $omitted_columns, $master_page = TRUE) {
  // Start the build process.
  $result = FALSE;
  $header_array = $table_data[0];
  $table_array = array();
  $omitted_empty = FALSE;
  $master_empty = FALSE;
  $data = $table_data;
  unset($data[0]);
  // Check if $master_columns is empty, set a boolean.
  if (empty($master_columns)) {
    $master_empty = TRUE;
  }
  // Check if ommitted columns is empty.
  if (empty($omitted_columns)) {
    $omitted_empty = TRUE;
  }
  if ($master_page != TRUE) {
    // Building sub pages.
    if ($omitted_empty != TRUE) {
      // Now we can build all the sub pages.
      $nids = _penton_datasheet_build_sub_pages($pid, $header_array, $data, $omitted_columns, TRUE);
      // New set the table in for the master page.
      if ($master_empty != TRUE) {
        _penton_datasheet_build_master_table($pid, $data, $header_array, $nids, $master_columns, TRUE);
      }
      else {
        _penton_datasheet_build_master_table($pid, $data, $header_array, $nids, $master_columns, FALSE);
      }
    }
    else {
      // Now we can build all the sub pages.
      $nids = _penton_datasheet_build_sub_pages($pid, $header_array, $data, FALSE, TRUE);
      if ($master_empty != TRUE) {
        _penton_datasheet_build_master_table($pid, $data, $header_array, $nids, $master_columns, TRUE);
      }
      else {
        _penton_datasheet_build_master_table($pid, $data, $header_array, $nids, $master_columns, FALSE);
      }
    }
  }
  else {
    // Building a master page if no subpages exist.
    // Double check that it is empty.
    if ($master_empty != FALSE) {
      _penton_datasheet_build_master_table($pid, $data, $header_array, FALSE, $master_columns, FALSE);
    }
    else {
      _penton_datasheet_build_master_table($pid, $data, $header_array, FALSE, $master_columns, FALSE);
    }
  }

  return $result;
}

/**
 * Build each sub page.
 *
 * Create the datasheet detail page.
 * Assign as a child of the pid.
 * Retrieve the nid of the created page.
 * Enter the data into the penton_data_table table.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param int $pid
 *   The Parent ID
 * @param object $header
 *   The headers required
 * @param object $data
 *   The columns required
 *
 * @return object
 *   Return the node IDs of the nodes created.
 */
function _penton_datasheet_build_sub_pages($pid, $header, $data) {
  $nids = array();
  // Clear out empty rows.
  $data = array_filter($data, function($item) {
    return count($item) > 1 && $item[0] !== NULL;
  });
  // Push all rows of the csv into a queue.
  $title_offset = 0;
  foreach ($header as $i => $th) {
    if (stripos($th, '[Title]') !== FALSE) {
      $title_offset = $i;
      break;
    }
  }
  foreach ($data as $item) {
    // Create the node.
    $nid = _penton_datasheet_create_data_table_detail_node($pid, $item[$title_offset]);
    // Push nodeID to array with title.
    array_push($nids, [$nid, $item[$title_offset]]);
    // Add entry to penton_data_table.
    _penton_datasheet_create_penton_data_table_entry($pid, $nid, $header, $item);
    $replacements = array('!nid' => $nid);
    watchdog("Penton Datasheet", "Node !nid has been created with table.", $replacements, WATCHDOG_INFO);
  }
  return $nids;
}

/**
 * This will add master table to a queue eventually.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param int $nid
 *   The node ID of the master.
 * @param object $data
 *   The table data.
 * @param object $header
 *   The header data.
 * @param object|bool $nids
 *   The child nodeIDs.
 */
function _penton_datasheet_build_master_table($nid, $data, $header, $nids = FALSE) {
  $table = array();
  $data = array_values($data);
  // Clear out empty rows.
  $data = array_filter($data, function($item) {
    return count($item) > 1 && $item[0] !== NULL;
  });
  foreach ($data as $key => $item) {
    $index = empty($nids[$key][0]) ? $key : $nids[$key][0];
    $table[$index] = $item;
  }

  // Now add to the db.
  // Insert into the database.
  db_insert('penton_data_table')
    ->fields(array(
      'nid' => $nid,
      'pid' => $nid,
      'header_data' => serialize($header),
      'array_data' => serialize($table),
    ))
    ->execute();

}

/**
 * Retrieve & unserialize table data.
 *
 * @paramint  $nid
 *   Data table node id
 *
 * @return array
 *   ['header_data', 'array_data', 'pid']
 */
function _penton_datasheet_get_table_data($nid) {
  $data = array(
    'header_data' => array(),
    'array_data' => array(),
    'pid' => NULL,
  );
  $result = db_select('penton_data_table', 'pdt')
    ->fields('pdt', array('pid', 'header_data', 'array_data'))
    ->condition('nid', $nid)
    ->execute()
    ->fetchAssoc();
  if ($result) {
    $data['header_data'] = array_values(unserialize($result['header_data']));
    $data['array_data'] = array_map('array_values', unserialize($result['array_data']));
    $data['pid'] = $result['pid'];
  }
  return $data;
}

/**
 * Return the HTML table based on supplied table data.
 *
 * @param array $data
 *   array('header_data', 'array_data', 'pid')
 *
 * @param object $node
 *   Data table node id
 *
 * @return mixed
 *   The theme table output.
 */
function _penton_datasheet_return_table($data, $node) {
  $table['parent_nid'] = $data['pid'];
  $header = $data['header_data'];
  $data = $data['array_data'];
  $head = array();
  $table['article_nid'] = $node->nid;

  if ($node->type == 'data_table_detail') {
    // No table header, labels in left column.
    foreach ($header as $i => $label) {
      $table['rows'][$i][] = trim($label);
      $table['rows'][$i][] = $data[0][$i];
    }
    $table['attributes'] = array('class' => array('full-with-table', 'no-stripping-table'));
    $table['datasheet_mode'] = 'detail';
  }
  else {
    // Layout with table header.
    foreach ($header as $key => $row_label) {
      $row_label = trim($row_label);
      $head_row = array(
        'data' => _penton_datasheet_stip_tokens($row_label),
        'class' => 'sort ' . $row_label,
        'id' => 'column' . $key,
        'sort' => $key == 0 ? 'ASC' : '',
      );
      $head[$row_label] = $head_row;
    }
    $table['attributes'] = array('class' => array('tablesorter'), 'id' => array('datatable'));
    $table['rows'] = $data;
    $table['header'] = $head;
    $table['datasheet_mode'] = filter_input(INPUT_GET, 'full') ? 'full' : 'preview';
  }
  $output = theme('table', $table);
  return $output;
}

/**
 * Get parent, next and previous entries in data sheet.
 *
 * @param int $nid
 *   Node id
 *
 * @return array
 *   array(0=>parent, 1=>prev, 2=>next)
 */
function _penton_datasheet_entry_relatives($nid) {
  $return = array(NULL, NULL, NULL);
  $query = db_select('penton_data_table', 'pdt');
  $query->leftJoin('penton_data_table', 'pdt_prev', 'pdt_prev.pid = pdt.pid AND pdt_prev.nid < pdt.nid');
  $query->leftJoin('penton_data_table', 'pdt_next', 'pdt_next.pid = pdt.pid AND pdt_next.nid > pdt.nid');
  $query->fields('pdt', array('pid', 'nid'));
  $query->addExpression('IF(MAX(pdt_prev.nid) = pdt.pid, NULL, MAX(pdt_prev.nid))', 'prev');
  $query->addExpression('IF(MIN(pdt_next.nid) = pdt.pid, NULL, MIN(pdt_next.nid))', 'next');
  $query->condition('pdt.nid', $nid);
  $result = $query->execute()->fetchAssoc();
  if ($result) {
    $return[0] = $result['pid'];
    $return[1] = $result['prev'];
    $return[2] = $result['next'];
  }
  return $return;
}
