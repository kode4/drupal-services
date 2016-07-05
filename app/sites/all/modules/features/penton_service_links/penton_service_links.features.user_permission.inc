<?php
/**
 * @file
 * penton_service_links.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function penton_service_links_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access service links'.
  $permissions['access service links'] = array(
    'name' => 'access service links',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'service_links',
  );

  // Exported permission: 'configure social widgets'.
  $permissions['configure social widgets'] = array(
    'name' => 'configure social widgets',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'penton_social',
  );

  // Exported permission: 'use PHP for service visibility'.
  $permissions['use PHP for service visibility'] = array(
    'name' => 'use PHP for service visibility',
    'roles' => array(),
    'module' => 'service_links',
  );

  return $permissions;
}
