<?php
/**
 * @file
 * penton_data_tables.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_data_tables_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
