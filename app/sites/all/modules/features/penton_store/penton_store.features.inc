<?php
/**
 * @file
 * penton_store.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_store_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function penton_store_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function penton_store_node_info() {
  $items = array(
    'store_front' => array(
      'name' => t('Store Front'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Store'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_uc_product_default_classes().
 */
function penton_store_uc_product_default_classes() {
  $items = array(
    'product' => array(
      'name' => t('Product'),
      'base' => 'uc_product',
      'description' => t('Use <em>products</em> to represent items for sale on the website, including all the unique information that can be attributed to a specific model number.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
