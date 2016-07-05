<?php
/**
 * @file
 * penton_categories.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_categories_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_taxonomy_term_categories_pattern';
  $strongarm->value = '[term:parents:join-path]/[term:name]';
  $export['pathauto_taxonomy_term_categories_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'term_authoring_info_vocab_categories_showfield';
  $strongarm->value = 1;
  $export['term_authoring_info_vocab_categories_showfield'] = $strongarm;

  return $export;
}
