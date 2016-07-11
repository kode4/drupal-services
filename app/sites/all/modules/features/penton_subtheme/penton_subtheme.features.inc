<?php
/**
 * @file
 * penton_subtheme.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_subtheme_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function penton_subtheme_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function penton_subtheme_image_default_styles() {
  $styles = array();

  // Exported image style: sc720x540.
  $styles['sc720x540'] = array(
    'label' => 'sc720x540',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 720,
          'height' => 540,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
