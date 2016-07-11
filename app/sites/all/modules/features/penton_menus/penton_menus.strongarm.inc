<?php
/**
 * @file
 * penton_menus.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_menus_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_menu_fields__menu_pillar_navigation';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'menu_fields_links_primary' => array(
          'default' => array(
            'weight' => 10,
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_menu_fields__menu_pillar_navigation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_menu_fields__menu_social_links';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(
        'menu_fields_links_primary' => array(
          'default' => array(
            'weight' => 10,
            'visible' => FALSE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_menu_fields__menu_social_links'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_fields_menus';
  $strongarm->value = array(
    0 => 'menu-pillar-navigation',
    1 => 'menu-social-links',
  );
  $export['menu_fields_menus'] = $strongarm;

  return $export;
}
