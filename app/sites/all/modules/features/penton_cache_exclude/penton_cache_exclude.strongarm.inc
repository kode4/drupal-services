<?php
/**
 * @file
 * penton_cache_exclude.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_cache_exclude_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cacheexclude_list';
  $strongarm->value = 'ajax/penton-legal-comm
ajax/penton-legal-comm-get-message
ajax/penton-legal-comm-count';
  $export['cacheexclude_list'] = $strongarm;

  return $export;
}
