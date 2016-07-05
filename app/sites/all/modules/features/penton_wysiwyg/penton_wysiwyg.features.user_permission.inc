<?php
/**
 * @file
 * penton_wysiwyg.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function penton_wysiwyg_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format comments'.
  $permissions['use text format comments'] = array(
    'name' => 'use text format comments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
