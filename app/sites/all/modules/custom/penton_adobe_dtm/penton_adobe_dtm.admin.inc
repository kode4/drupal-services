<?php
/**
 * @file
 * Admin-related callbacks for Adobe DTM.
 */

/**
 * Settings form for Adobe DTM.
 */
function penton_adobe_dtm_admin_settings() {
  drupal_add_js(drupal_get_path('module', 'penton_adobe_dtm') . '/js/penton_adobe_dtm.admin.js');

  $adobe_dtm_id = variable_get('adobe_dtm_id', '');
  $adobe_dtm_site_hash = variable_get('adobe_dtm_site_hash', '');
  $adobe_dtm_environment = variable_get('adobe_dtm_environment', 'staging');

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
  );

  $form['general']['adobe_dtm_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Adobe DTM ID'),
    '#description' => t('Adobe DTM serial number.'),
    '#default_value' => $adobe_dtm_id,
  );

  $form['general']['adobe_dtm_site_hash'] = array(
    '#type' => 'textfield',
    '#title' => t('Adobe DTM Site Hash'),
    '#description' => t('Adobe DTM site hash.'),
    '#default_value' => $adobe_dtm_site_hash,
  );

  $form['general']['adobe_dtm_environment'] = array(
    '#type' => 'select',
    '#title' => t('Current Server Environment'),
    '#options' => array(
      'production' => t('Production'),
      'staging' => t('Staging'),
    ),
    '#default_value' => $adobe_dtm_environment,
    '#description' => '<b>Note</b>: choose \'Production\' <b>ONLY</b> on production environment.',
  );

  $adobe_dtm_id = !empty($adobe_dtm_id) ? $adobe_dtm_id : '{ID}';
  $adobe_dtm_site_hash = !empty($adobe_dtm_site_hash) ? $adobe_dtm_site_hash : '{SITE-HASH}';
  $adobe_dtm_environment = $adobe_dtm_environment == 'staging' ? '-staging' : '';

  $script_path = '<div class="dtm-complete-path">'
    . 'Complete path to Javascript file: "//assets.adobedtm.com/'
    . '<span class="dtm-id"><b>' . $adobe_dtm_id . '</b></span>/satelliteLib-'
    . '<span class="dtm-site-hash"><b>' . $adobe_dtm_site_hash . '</b></span>'
    . '<span class="dtm-environment">' . $adobe_dtm_environment . '</span>'
    . '.js"</div>';
  $form['general']['adobe_dtm_path'] = array(
    '#type' => 'markup',
    '#markup' => $script_path,
  );

  $form['roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('User role tracking'),
    '#collapsible' => TRUE,
    '#description' => t('Define which user roles should, or should not be tracked by Adobe DTM.'),
  );

  $form['roles']['adobe_dtm_role_tracking_type'] = array(
    '#type' => 'select',
    '#title' => t('Add tracking for specific roles'),
    '#options' => array(
      'inclusive' => t('Add to the selected roles only'),
      'exclusive' => t('Add to all roles except the ones selected'),
    ),
    '#default_value' => variable_get('adobe_dtm_role_tracking_type', 'inclusive'),
  );

  $result = db_select('role', 'r')
    ->fields('r')
    ->orderBy('name', 'ASC')
    ->execute();

  foreach ($result as $role) {
    // Can't use empty spaces in varname.
    $role_varname = str_replace(' ', '_', $role->name);
    $role_name = $role->name;
    $form['roles']["adobe_dtm_track_{$role_varname}"] = array(
      '#type' => 'checkbox',
      '#title' => $role_name,
      '#default_value' => variable_get("adobe_dtm_track_{$role_varname}", FALSE),
    );
  }

  $form['#submit'][] = 'penton_adobe_dtm_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Submit function for Penton Adobe DTM config form.
 *
 * Save complete path to variable.
 */
function penton_adobe_dtm_admin_settings_submit($form, $form_state) {
  $script_path = _penton_adobe_dtm_build_js_path(
    $form_state['values']['adobe_dtm_id'],
    $form_state['values']['adobe_dtm_site_hash'],
    $form_state['values']['adobe_dtm_environment']
  );
  variable_set('adobe_dtm_script_path', $script_path);
}
