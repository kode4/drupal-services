<?php
/**
 * @file
 * penton_block_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_block_content_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function penton_block_content_node_info() {
  $items = array(
    'block_content' => array(
      'name' => t('Block Content'),
      'base' => 'node_content',
      'description' => t('Content type used to create blocks.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
