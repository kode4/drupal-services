<?php
/**
 * @file
 * penton_media_entity.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_media_entity_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function penton_media_entity_node_info() {
  $items = array(
    'media_entity' => array(
      'name' => t('Media Entity'),
      'base' => 'node_content',
      'description' => t('A content-type concerned with storing media, including files, embed links, images'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
