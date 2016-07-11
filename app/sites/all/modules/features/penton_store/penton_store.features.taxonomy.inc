<?php
/**
 * @file
 * penton_store.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function penton_store_taxonomy_default_vocabularies() {
  return array(
    'product_types' => array(
      'name' => 'Product Types',
      'machine_name' => 'product_types',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -4,
    ),
    'topics' => array(
      'name' => 'Topics',
      'machine_name' => 'topics',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => -3,
    ),
  );
}
