<?php
/**
 * @file
 * penton_data_tables.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_data_tables_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_allowed_types';
  $strongarm->value = array(
    0 => 'article',
    1 => 'data_table_detail',
  );
  $export['book_allowed_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'book_child_type';
  $strongarm->value = 'data_table_detail';
  $export['book_child_type'] = $strongarm;

  return $export;
}
