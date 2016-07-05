<?php
/**
 * @file
 * penton_user_info.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function penton_user_info_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function penton_user_info_image_default_styles() {
  $styles = array();

  // Exported image style: article_small_thumb_standard.
  $styles['article_small_thumb_standard'] = array(
    'label' => 'article_small_thumb_standard',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 90,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 90,
          'height' => 50,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_author_profile_badge.
  $styles['non_feat_author_profile_badge'] = array(
    'label' => 'non_feat_author_profile_badge',
    'effects' => array(
      4 => array(
        'name' => 'image_resize',
        'data' => array(
          'width' => 120,
          'height' => 33,
        ),
        'weight' => -10,
      ),
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 120,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => -9,
      ),
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 120,
          'height' => 33,
        ),
        'weight' => -8,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_default_profile2_type().
 */
function penton_user_info_default_profile2_type() {
  $items = array();
  $items['main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "main",
    "label" : "Main profile",
    "weight" : "0",
    "data" : { "registration" : 0 }
  }');
  return $items;
}
