<?php
/**
 * @file
 * penton_service_links.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function penton_service_links_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.service_links_show.value|pinterest_button"] = 0;

 return $overrides;
}
