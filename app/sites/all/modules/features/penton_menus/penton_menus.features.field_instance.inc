<?php
/**
 * @file
 * penton_menus.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function penton_menus_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'menu_fields-menu_pillar_navigation-penton_field_icon'.
  $field_instances['menu_fields-menu_pillar_navigation-penton_field_icon'] = array(
    'bundle' => 'menu_pillar_navigation',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Icon showed in pillar menu.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'menu_fields',
    'fences_wrapper' => 'no_wrapper',
    'field_name' => 'penton_field_icon',
    'label' => 'Icon',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'menu_fields-menu_social_links-penton_field_social_icons'.
  $field_instances['menu_fields-menu_social_links-penton_field_social_icons'] = array(
    'bundle' => 'menu_social_links',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'menu_fields',
    'fences_wrapper' => 'div',
    'field_name' => 'penton_field_social_icons',
    'label' => 'social icons',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Icon');
  t('Icon showed in pillar menu.');
  t('social icons');

  return $field_instances;
}
