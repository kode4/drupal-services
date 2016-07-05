<?php
/**
 * @file
 * penton_core.metatag.inc
 */

/**
 * Implements hook_metatag_bundled_config_alter().
 */
function penton_core_metatag_bundled_config_alter(&$config) {
  if ($config['global:frontpage']) {
    $config['global:frontpage']->disabled = TRUE;
  }
  return $config;
}
