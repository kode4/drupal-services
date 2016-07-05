<?php
/**
 * @file
 * penton_dfp.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_dfp_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "dfp" && $api == "default_dfp_tags") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
