<?php
/**
 * @file
 * penton_cache_expire.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_cache_expire_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
