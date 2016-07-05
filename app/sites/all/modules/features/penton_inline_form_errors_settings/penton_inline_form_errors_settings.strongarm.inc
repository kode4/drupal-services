<?php
/**
 * @file
 * penton_inline_form_errors_settings.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_inline_form_errors_settings_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ife_display';
  $strongarm->value = '2';
  $export['ife_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ife_general_message';
  $strongarm->value = 'Please correct all highlighted errors and try again.';
  $export['ife_general_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ife_show_form_ids';
  $strongarm->value = 0;
  $export['ife_show_form_ids'] = $strongarm;

  return $export;
}
