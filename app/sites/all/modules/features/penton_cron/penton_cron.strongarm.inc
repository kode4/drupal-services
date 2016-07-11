<?php
/**
 * @file
 * penton_cron.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_cron_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cron_safe_threshold';
  $strongarm->value = '0';
  $export['cron_safe_threshold'] = $strongarm;

  return $export;
}
