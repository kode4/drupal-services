<?php
/**
 * @file
 * penton_gating_copy.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_gating_copy_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function penton_gating_copy_node_info() {
  $items = array(
    'gating_copy' => array(
      'name' => t('Gating Copy'),
      'base' => 'node_content',
      'description' => t('Drupal blocks that can be used and displayed in defined regions in the template; for configurable messages (urgent communication, gating copy etc), promotional content (pillar promo unit, user marketing promo) etc.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
