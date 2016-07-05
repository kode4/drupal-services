<?php
/**
 * @file
 * penton_feature_forward.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_feature_forward_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
