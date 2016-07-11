<?php
/**
 * @file
 * penton_dev.backup_migrate_exportables.inc
 */

/**
 * Implements hook_exportables_backup_migrate_profiles().
 */
function penton_dev_exportables_backup_migrate_profiles() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'default';
  $item->name = 'content pillar content';
  $item->filename = 'cp_db';
  $item->append_timestamp = TRUE;
  $item->timestamp_format = 'M d Y\\TH-i-s';
  $item->filters = array(
    'compression' => 'gzip',
    'notify_success_enable' => 0,
    'notify_success_email' => 'admin@example.com',
    'notify_failure_enable' => 0,
    'notify_failure_email' => 'admin@example.com',
    'utils_site_offline' => 0,
    'utils_site_offline_message' => 'default is currently under maintenance. We should be back shortly. Thank you for your patience.',
    'utils_description' => '',
    'use_cli' => 0,
    'ignore_errors' => 0,
    'sources' => array(
      'db' => array(
        'exclude_tables' => array(
          'actions' => 'actions',
          'authmap' => 'authmap',
          'backup_migrate_destinations' => 'backup_migrate_destinations',
          'backup_migrate_profiles' => 'backup_migrate_profiles',
          'backup_migrate_schedules' => 'backup_migrate_schedules',
          'backup_migrate_sources' => 'backup_migrate_sources',
          'batch' => 'batch',
          'block' => 'block',
          'block_custom' => 'block_custom',
          'block_role' => 'block_role',
          'blocked_ips' => 'blocked_ips',
          'cache' => 'cache',
          'cache_admin_menu' => 'cache_admin_menu',
          'cache_block' => 'cache_block',
          'cache_bootstrap' => 'cache_bootstrap',
          'cache_coder' => 'cache_coder',
          'cache_features' => 'cache_features',
          'cache_field' => 'cache_field',
          'cache_filter' => 'cache_filter',
          'cache_image' => 'cache_image',
          'cache_menu' => 'cache_menu',
          'cache_menu_fields' => 'cache_menu_fields',
          'cache_metatag' => 'cache_metatag',
          'cache_page' => 'cache_page',
          'cache_path' => 'cache_path',
          'cache_token' => 'cache_token',
          'cache_update' => 'cache_update',
          'cache_variable' => 'cache_variable',
          'cache_views' => 'cache_views',
          'cache_views_data' => 'cache_views_data',
          'captcha_points' => 'captcha_points',
          'captcha_sessions' => 'captcha_sessions',
          'context' => 'context',
          'ctools_css_cache' => 'ctools_css_cache',
          'ctools_object_cache' => 'ctools_object_cache',
          'date_format_locale' => 'date_format_locale',
          'date_format_type' => 'date_format_type',
          'date_formats' => 'date_formats',
          'dfp_tags' => 'dfp_tags',
          'elysia_cron' => 'elysia_cron',
          'entity_modified' => 'entity_modified',
          'fe_block_boxes' => 'fe_block_boxes',
          'filter' => 'filter',
          'filter_format' => 'filter_format',
          'flood' => 'flood',
          'forward_log' => 'forward_log',
          'forward_statistics' => 'forward_statistics',
          'history' => 'history',
          'image_effects' => 'image_effects',
          'image_styles' => 'image_styles',
          'metatag' => 'metatag',
          'metatag_config' => 'metatag_config',
          'migrate_field_mapping' => 'migrate_field_mapping',
          'migrate_group' => 'migrate_group',
          'migrate_log' => 'migrate_log',
          'migrate_status' => 'migrate_status',
          'penton_data_table' => 'penton_data_table',
          'penton_newsletter' => 'penton_newsletter',
          'queue' => 'queue',
          'role' => 'role',
          'role_permission' => 'role_permission',
          'search_dataset' => 'search_dataset',
          'search_index' => 'search_index',
          'search_node_links' => 'search_node_links',
          'search_total' => 'search_total',
          'semaphore' => 'semaphore',
          'sequences' => 'sequences',
          'services_endpoint' => 'services_endpoint',
          'services_user' => 'services_user',
          'sessions' => 'sessions',
          'simpletest' => 'simpletest',
          'simpletest_test_id' => 'simpletest_test_id',
          'system' => 'system',
          'taxonomy_index' => 'taxonomy_index',
          'users' => 'users',
          'variable' => 'variable',
          'views_display' => 'views_display',
          'views_view' => 'views_view',
          'watchdog' => 'watchdog',
        ),
        'nodata_tables' => array(
          'cache' => 'cache',
          'cache_admin_menu' => 'cache_admin_menu',
          'cache_block' => 'cache_block',
          'cache_bootstrap' => 'cache_bootstrap',
          'cache_field' => 'cache_field',
          'cache_filter' => 'cache_filter',
          'cache_form' => 'cache_form',
          'cache_image' => 'cache_image',
          'cache_menu' => 'cache_menu',
          'cache_page' => 'cache_page',
          'cache_path' => 'cache_path',
          'cache_update' => 'cache_update',
          'cache_views' => 'cache_views',
          'cache_views_data' => 'cache_views_data',
          'search_dataset' => 'search_dataset',
          'search_index' => 'search_index',
          'search_total' => 'search_total',
          'sessions' => 'sessions',
          'watchdog' => 'watchdog',
        ),
        'utils_lock_tables' => 1,
      ),
      'files' => array(
        'exclude_filepaths' => 'backup_migrate
styles
css
js
ctools
less',
      ),
      'archive' => array(
        'exclude_filepaths' => 'public://backup_migrate
public://styles
public://css
public://js
public://ctools
public://less
private://backup_migrate
sites/default/settings.php
/tmp',
      ),
    ),
  );
  $export['default'] = $item;

  return $export;
}
