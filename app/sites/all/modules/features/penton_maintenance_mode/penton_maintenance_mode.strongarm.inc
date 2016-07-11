<?php
/**
 * @file
 * penton_maintenance_mode.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_maintenance_mode_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'maintenance_mode_message';
  $strongarm->value = '<p>$SITE is temporarily unavailable while we make some maintenance updates.</p>
<p>We apologize for the inconvenience and thank you for your patience.</p>';
  $export['maintenance_mode_message'] = $strongarm;

  return $export;
}
