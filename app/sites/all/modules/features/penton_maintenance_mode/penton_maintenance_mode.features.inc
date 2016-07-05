<?php
/**
 * @file
 * penton_maintenance_mode.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_maintenance_mode_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
