<?php
/**
 * @file
 * penton_mollom.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_mollom_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "mollom" && $api == "mollom") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
