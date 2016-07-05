<?php
/**
 * @file
 * penton_display_admin.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_display_admin_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function penton_display_admin_node_info() {
  $items = array(
    'display_admin' => array(
      'name' => t('Display Admin'),
      'base' => 'node_content',
      'description' => t('The Homepage display, could be expanded to other pages in the future.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
