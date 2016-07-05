<?php
/**
 * @file
 * penton_program.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function penton_program_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete terms in program'.
  $permissions['delete terms in program'] = array(
    'name' => 'delete terms in program',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in program'.
  $permissions['edit terms in program'] = array(
    'name' => 'edit terms in program',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  return $permissions;
}
