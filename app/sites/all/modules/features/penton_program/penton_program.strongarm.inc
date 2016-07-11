<?php
/**
 * @file
 * penton_program.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_program_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'term_authoring_info_vocab_program_showfield';
  $strongarm->value = 1;
  $export['term_authoring_info_vocab_program_showfield'] = $strongarm;

  return $export;
}
