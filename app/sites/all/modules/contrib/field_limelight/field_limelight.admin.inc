<?php
/**
 * @file
 * Admin interface for a field using the Field Types API to integrate videos from http://field_limelight.com
 */


/**
 * Vvailable limelight.com player version list
 * @see http://videoplatform.limelight.com/: login -> media -> embed code
 * @return array players
 */
function field_limelight_admin_players() {

  // @todo maybe an admin interface for the players
  // also including customized players

  return array(
    'Player' => 'Widescreen Player',
    'PlayerHorizontalPlaylist' => 'Widescreen Player (width horizontal playlist)',
    'HoverPlayer' => 'Hover Player',
    'MiniPlayer' => 'Mini Player',
  );
}


/**
 * List of the player dimensions (width and height)
 * @return array $player_dimensions
 */
function field_limelight_admin_player_sizes() {

  // @todo maybe an admin interface for the players and their sizes
  // also including customized players

  $player_dimensions = array(
    'Player' => array('width' => 480, 'height' => 321),
    'PlayerHorizontalPlaylist' => array('width' => 960, 'height' => 360),
    'HoverPlayer' => array('width' => 480, 'height' => 270),
    'MiniPlayer' => array('width' => 249, 'height' => 168),
  );
  return $player_dimensions;
}


/**
 * Admin settings form for the limelight field
 * @return mixed
 */
function field_limelight_admin_settings_form() {

  $form = array();

  // get the possible limelight players

  // -> use field_limelight_player_id
  // select the limelight player
  $players = field_limelight_admin_players();
  $form['field_limelight_player'] = array(
    '#type' => 'select',
    '#title' => t('Limelight.com player (not in use, please use the player id)'),
    '#description' => t('Please select the player version you want to user from limelight.com.'),
    '#options' => $players,
    '#default_value' => variable_get('field_limelight_player', 'Player'),
  );

  // the organization id on limelight.com
  $form['field_limelight_organization_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Limelight.com organization id'),
    '#description' => t('Please enter your organization id from limelight.com'),
    '#default_value' => variable_get('field_limelight_organization_id', ''),
  );

  // the limelight.com access key
  $form['field_limelight_access_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Limelight.com access key'),
    '#description' => t('Please enter your limelight.com access key'),
    '#default_value' => variable_get('field_limelight_access_key', ''),
  );

  // the limelight.com secret
  $form['field_limelight_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Limelight.com secret'),
    '#description' => t('Please enter your limelight.com secret'),
    '#default_value' => variable_get('field_limelight_secret', ''),
  );

  // the limelight.com player id for the videos
  $form['field_limelight_player_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Limelight.com player id'),
    '#description' => t('Please enter your limelight.com player id.'),
    '#default_value' => variable_get('field_limelight_player_id', ''),
  );

  // the limelight.com channel id the videos should be uploaded to
  $form['field_limelight_channel_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Limelight.com channel id'),
    '#description' => t('Please enter your limelight.com channel id to where the videos should be uploaded to.'),
    '#default_value' => variable_get('field_limelight_channel_id', ''),
  );

  // setting if videos should be deleted on limelight.com if the video is removed locally
  // will be done by cron
  $form['field_limelight_removed_locally_deleted_videos'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete removed videos on Limelight.com'),
    '#description' => t('When deleting a video in a Drupal node, just the assignment is locally deleted.
    The video itself is still hosted on limelight.com. If this setting is enabled the Drupal cron will check if there
    are still videos on limlight.com without any reference in the local Drupal environment. These videos will be deleted on limeliht.com.'),
    '#default_value' => variable_get('field_limelight_removed_locally_deleted_videos', FALSE),
  );

  return system_settings_form($form);
}