<?php
/**
 * @file
 * penton_data_table_detail.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_data_table_detail_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function penton_data_table_detail_node_info() {
  $items = array(
    'data_table_detail' => array(
      'name' => t('Data Table Detail'),
      'base' => 'node_content',
      'description' => t('The detail page for data table content. This content is built dynamically when csvs are uploaded '),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
