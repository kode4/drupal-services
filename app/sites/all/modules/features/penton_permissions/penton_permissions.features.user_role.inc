<?php
/**
 * @file
 * penton_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function penton_permissions_user_default_roles() {
  $roles = array();

  // Exported role: Production User.
  $roles['Production User'] = array(
    'name' => 'Production User',
    'weight' => 10,
  );

  // Exported role: feeds manager.
  $roles['feeds manager'] = array(
    'name' => 'feeds manager',
    'weight' => 9,
  );

  return $roles;
}
