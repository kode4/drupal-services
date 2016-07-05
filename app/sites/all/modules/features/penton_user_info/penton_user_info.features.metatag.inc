<?php
/**
 * @file
 * penton_user_info.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function penton_user_info_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: user.
  $config['user'] = array(
    'instance' => 'user',
    'config' => array(
      'title' => array(
        'value' => '[user:name] | [site:name]',
      ),
      'description' => array(
        'value' => '[user:name]\'s profile.',
      ),
    ),
  );

  return $config;
}
