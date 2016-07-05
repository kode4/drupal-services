<?php
/**
 * @file
 * penton_print_settings.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function penton_print_settings_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access print'.
  $permissions['access print'] = array(
    'name' => 'access print',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'print',
  );

  // Exported permission: 'access printer-friendly version'.
  $permissions['access printer-friendly version'] = array(
    'name' => 'access printer-friendly version',
    'roles' => array(),
    'module' => 'book',
  );

  // Exported permission: 'administer print'.
  $permissions['administer print'] = array(
    'name' => 'administer print',
    'roles' => array(),
    'module' => 'print',
  );

  // Exported permission: 'node-specific print configuration'.
  $permissions['node-specific print configuration'] = array(
    'name' => 'node-specific print configuration',
    'roles' => array(),
    'module' => 'print_ui',
  );

  return $permissions;
}
