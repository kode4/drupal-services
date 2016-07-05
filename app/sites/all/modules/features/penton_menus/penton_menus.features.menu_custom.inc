<?php
/**
 * @file
 * penton_menus.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function penton_menus_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-dropdown-bottom-menu.
  $menus['menu-dropdown-bottom-menu'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'title' => 'Dropdown bottom menu',
    'description' => 'Bottom menu in hamburger dropdown menu.',
  );
  // Exported menu: menu-dropdown-top-menu.
  $menus['menu-dropdown-top-menu'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'title' => 'Dropdown top menu',
    'description' => 'Top menu in hamburger dropdown menu.',
  );
  // Exported menu: menu-footer-menu.
  $menus['menu-footer-menu'] = array(
    'menu_name' => 'menu-footer-menu',
    'title' => 'Footer menu',
    'description' => 'Menu in footer.',
  );
  // Exported menu: menu-header-menu.
  $menus['menu-header-menu'] = array(
    'menu_name' => 'menu-header-menu',
    'title' => 'Header Menu',
    'description' => '',
  );
  // Exported menu: menu-pillar-navigation.
  $menus['menu-pillar-navigation'] = array(
    'menu_name' => 'menu-pillar-navigation',
    'title' => 'Pillar navigation',
    'description' => 'Topmost menu.',
  );
  // Exported menu: menu-social-links.
  $menus['menu-social-links'] = array(
    'menu_name' => 'menu-social-links',
    'title' => 'Social links',
    'description' => 'Social links in hamburger dropdown menu and footer.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Bottom menu in hamburger dropdown menu.');
  t('Dropdown bottom menu');
  t('Dropdown top menu');
  t('Footer menu');
  t('Header Menu');
  t('Menu in footer.');
  t('Pillar navigation');
  t('Social links');
  t('Social links in hamburger dropdown menu and footer.');
  t('Top menu in hamburger dropdown menu.');
  t('Topmost menu.');

  return $menus;
}
