<?php
/**
 * @file
 * penton_feeds_aggregator_settings.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_feeds_aggregator_settings_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_penton_feed';
  $strongarm->value = '0';
  $export['comment_anonymous_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_penton_feed';
  $strongarm->value = 1;
  $export['comment_default_mode_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_penton_feed';
  $strongarm->value = '50';
  $export['comment_default_per_page_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_penton_feed';
  $strongarm->value = 1;
  $export['comment_form_location_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_penton_feed';
  $strongarm->value = '0';
  $export['comment_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_penton_feed';
  $strongarm->value = '1';
  $export['comment_preview_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_penton_feed';
  $strongarm->value = 1;
  $export['comment_subject_field_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_penton_feed';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_penton_feed';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_penton_feed';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_penton_feed';
  $strongarm->value = '1';
  $export['node_preview_penton_feed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_penton_feed';
  $strongarm->value = 1;
  $export['node_submitted_penton_feed'] = $strongarm;

  return $export;
}
