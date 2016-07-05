<?php
/**
 * @file
 * penton_field_bases.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function penton_field_bases_user_default_roles() {
  $roles = array();

  // Exported role: comment moderator.
  $roles['comment moderator'] = array(
    'name' => 'comment moderator',
    'weight' => 4,
  );

  // Exported role: paid premium.
  $roles['paid premium'] = array(
    'name' => 'paid premium',
    'weight' => 3,
  );

  return $roles;
}
