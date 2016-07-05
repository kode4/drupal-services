<?php
/**
 * @file
 * penton_cache_exclude.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_cache_exclude_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
