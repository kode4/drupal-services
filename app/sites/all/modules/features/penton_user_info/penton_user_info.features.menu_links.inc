<?php
/**
 * @file
 * penton_user_info.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function penton_user_info_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_logintoboggan:admin/config/system/logintoboggan
  $menu_links['management_logintoboggan:admin/config/system/logintoboggan'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/logintoboggan',
    'router_path' => 'admin/config/system/logintoboggan',
    'link_title' => 'LoginToboggan',
    'options' => array(
      'attributes' => array(
        'title' => 'Set up custom login options like instant login, login redirects, pre-authorized validation roles, etc.',
      ),
      'identifier' => 'management_logintoboggan:admin/config/system/logintoboggan',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_system:admin/config/system',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('LoginToboggan');


  return $menu_links;
}
