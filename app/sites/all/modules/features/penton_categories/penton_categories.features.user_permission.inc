<?php
/**
 * @file
 * penton_categories.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function penton_categories_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete terms in categories'.
  $permissions['delete terms in categories'] = array(
    'name' => 'delete terms in categories',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in categories'.
  $permissions['edit terms in categories'] = array(
    'name' => 'edit terms in categories',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  return $permissions;
}
