<?php
/**
 * @file
 * A module to create custom drush commands.
 */

/**
 * Implements hook_drush_command().
 */
function penton_drush_drush_command() {
  $items['reset-environment'] = array(
    'description' => 'Reset the settings file for a drupal installation.',
    'aliases' => array('rde'),
  );

  $items['rebuild-updated-profile'] = array(
    'description' => 'Update database with latest settings from current installation profile.',
    'aliases' => array('rup'),
  );

  return $items;
}

/**
 * Callback for the reset-environment command.
 */
function drush_penton_drush_reset_environment() {
  drupal_set_message('Deleting old settings.php');
  penton_drush_delete_settings();
  drupal_set_message('Creating new settings.php');
  penton_drush_create_settings();
}

/**
 * Callback for the rebuild-updated-profile command.
 */
function drush_penton_drush_rebuild_updated_profile() {
  $install_profile = variable_get('install_profile', 'penton_tt');
  require_once DRUPAL_ROOT . "/profiles/$install_profile/$install_profile.install";
  call_user_func($install_profile . '_install');
}

/**
 * Helper function to delete settings.php.
 */
function penton_drush_delete_settings() {
  $filename = '/var/www/penton/sites/default/settings.php';
  if (file_exists($filename)) {
    chmod($filename, 0777);
    unlink($filename);
    drupal_set_message('Old settings.php file deleted.');
  }
  else {
    drupal_set_message('settings.php does not exist.');
  }
}

/**
 * Helper function to create settings.php.
 */
function penton_drush_create_settings() {
  $default_filename = '/var/www/penton/sites/default/default.settings.php';
  $filename = '/var/www/penton/sites/default/settings.php';
  if (file_exists($filename)) {
    drupal_set_message('settings.php already exists.');
  }
  else {
    if (!copy($default_filename, $filename)) {
      drupal_set_message('Failed to copy settings.php.');
    }
    else {
      if (!chmod($filename, 0777)) {
        drupal_set_message('settings.php copied but unable to set permissions.');
      }
      else {
        drupal_set_message('settings.php copied.');
      }
    }
  }
}
