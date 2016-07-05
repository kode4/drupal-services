<?php
/**
 * @file
 * penton_menus.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function penton_menus_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-footer-menu_privacy-policy:http://www.penton.com/privacy-policy.
  $menu_links['menu-footer-menu_privacy-policy:http://www.penton.com/privacy-policy'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'http://www.penton.com/privacy-policy',
    'router_path' => '',
    'link_title' => 'Privacy Policy',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_privacy-policy:http://www.penton.com/privacy-policy',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_terms-of-service:http://www.penton.com/terms-of-service.
  $menu_links['menu-footer-menu_terms-of-service:http://www.penton.com/terms-of-service'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'http://www.penton.com/terms-of-service',
    'router_path' => '',
    'link_title' => 'Terms of Service',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_terms-of-service:http://www.penton.com/terms-of-service',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -30,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Privacy Policy');
  t('Terms of Service');

  return $menu_links;
}
