<?php
/**
 * @file
 * penton_page_type.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function penton_page_type_taxonomy_default_vocabularies() {
  return array(
    'page_type' => array(
      'name' => 'Page Type',
      'machine_name' => 'page_type',
      'description' => 'describes the type of page for Page content type',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
