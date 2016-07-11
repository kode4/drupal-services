<?php
/**
 * @file
 * penton_inline_form_errors_settings.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_inline_form_errors_settings_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ife" && $api == "ife") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
