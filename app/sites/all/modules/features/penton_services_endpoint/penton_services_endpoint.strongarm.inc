<?php
/**
 * @file
 * penton_services_endpoint.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_services_endpoint_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'contextual_range_filter_date_field_names';
  $strongarm->value = array(
    'node:created_fulldate' => 'node:created_fulldate',
    'users:created_fulldate' => 'users:created_fulldate',
  );
  $export['contextual_range_filter_date_field_names'] = $strongarm;

  return $export;
}
