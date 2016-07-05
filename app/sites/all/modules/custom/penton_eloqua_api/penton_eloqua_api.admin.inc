<?php
/**
 * @file
 * Admin-related callbacks related to Eloqua API.
 */

/**
 * Admin form for Eloqua API config.
 */
function penton_eloqua_api_api_settings() {
  $form = array();

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('Eloqua Settings'),
    '#collapsinle' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['general']['penton_eloqua_api_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Eloqua API Username'),
    '#default_value' => variable_get('penton_eloqua_api_username', ''),
  );
  $form['general']['penton_eloqua_api_pw'] = array(
    '#type' => 'password',
    '#title' => t('Eloqua API Password'),
    '#default_value' => '',
  );

  $opt = array('0' => t('Disabled'), 'rest' => t('REST API'));
  $form['general']['penton_eloqua_api_enabled'] = array(
    '#type' => 'radios',
    '#title' => t('Enable Eloqua API'),
    '#options' => $opt,
    '#default_value' => variable_get('penton_eloqua_api_enabled', '0'),
  );

  $form['general']['penton_eloqua_api_cdo'] = array(
    '#type' => 'textfield',
    '#title' => t('Eloqua Custom Data Object'),
    '#description' => t('Fill this field to pass user data to Custom Data Object in Eloqua during site registration'),
    '#default_value' => variable_get('penton_eloqua_api_cdo', 'Subscriptions Opt-In History'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validate function for Eloqua API config.
 */
function penton_eloqua_api_api_settings_validate($form, &$form_state) {
  if ($form_state['values']['penton_eloqua_api_enabled'] == 'rest') {
    $current_pass = variable_get('penton_eloqua_api_pw', '');
    if (empty($form_state['values']['penton_eloqua_api_username']) ||
      (empty($form_state['values']['penton_eloqua_api_pw']) && empty($current_pass))) {
      if (empty($form_state['values']['penton_eloqua_api_username'])) {
        form_set_error('penton_eloqua_api_username', 'Username required to enable Eloqua REST API');
      }
      if (empty($form_state['values']['penton_eloqua_api_pw'])) {
        form_set_error('penton_eloqua_api_pw', 'Password required to enable Eloqua REST API');
      }
    }
    if (!empty($form_state['values']['penton_eloqua_api_pw'])) {
      include_once drupal_get_path('module', 'penton_eloqua_api') . '/includes/penton_eloqua_api.helper.inc';
      $client = penton_eloqua_api_get_rest_client($form_state['values']['penton_eloqua_api_username'], $form_state['values']['penton_eloqua_api_pw']);
      if ($client === FALSE) {
        form_set_error('penton_eloqua_api_username');
        form_set_error('penton_eloqua_api_pw');
      }
    }
    if (empty($form_state['values']['penton_eloqua_api_pw']) && !empty($current_pass)) {
      include_once drupal_get_path('module', 'penton_eloqua_api') . '/includes/penton_eloqua_api.helper.inc';
      $client = penton_eloqua_api_get_rest_client($form_state['values']['penton_eloqua_api_username'], base64_decode($current_pass));
      if ($client === FALSE) {
        form_set_error('penton_eloqua_api_pw');
      }
      else {
        $form_state['values']['penton_eloqua_api_pw'] = base64_decode($current_pass);
      }
    }
  }
}

/**
 * Submit function for Eloqua API config.
 */
function penton_eloqua_api_api_settings_submit($form, &$form_state) {
  if (variable_get('penton_eloqua_api_username', '') != $form_state['values']['penton_eloqua_api_username']) {
    variable_set('penton_eloqua_api_reg_form_name', 'Blank');
  }

  variable_set('penton_eloqua_api_enabled', $form_state['values']['penton_eloqua_api_enabled']);
  variable_set('penton_eloqua_api_username', $form_state['values']['penton_eloqua_api_username']);
  variable_set('penton_eloqua_api_pw', base64_encode($form_state['values']['penton_eloqua_api_pw']));
  if (variable_get('penton_eloqua_api_cdo', '') != $form_state['values']['penton_eloqua_api_cdo']) {
    variable_set('penton_eloqua_api_cached_cdo', '');
  }
  variable_set('penton_eloqua_api_cdo', $form_state['values']['penton_eloqua_api_cdo']);
}

/**
 * Determines the form for Eloqua field mapping.
 */
function penton_eloqua_api_mapping($form, &$form_state) {
  include_once drupal_get_path('module', 'penton_eloqua_api') . '/includes/penton_eloqua_api.helper.inc';
  $eloqua_rest_client = penton_eloqua_api_get_rest_client();
  $eloqua_error_message = check_plain('Eloqua API is not currently enabled ' .
    l(t('Eloqua API Settings'), 'admin/config/services/penton_eloqua_api/api_settings'));
  $form_options = array();
  $eloqua_api_enabled = variable_get('penton_eloqua_api_enabled', '0') == 'rest';
  $trip_error = 0;
  if ($eloqua_api_enabled) {
    $form_options = penton_eloqua_api_get_form_list('form_id', $eloqua_rest_client);
  }
  else {
    $trip_error = 1;
    drupal_set_message($eloqua_error_message, 'error');
  }
  $form['registration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site Registration'),
  );

  $reg_form_id = variable_get('penton_eloqua_api_reg_form_id', '0');
  $reg_form_id = isset($form_state['values']['registration_form']) ? $form_state['values']['registration_form'] : $reg_form_id;
  $form['registration']['registration_form'] = array(
    '#type' => 'select',
    '#title' => t('Eloqua Site Registration Form'),
    '#options' => $form_options,
    '#default_value' => $reg_form_id,
    '#empty_value' => 0,
    '#ajax' => array(
      'event' => 'change',
      'wrapper' => 'site-field',
      'callback' => '_penton_eloqua_api_replace_site_field',
      'method' => 'replace',
    ),
  );
  $form['registration']['site_field'] = array(
    '#type' => 'select',
    '#title' => t('Site Field'),
    '#suffix' => t('The "Site Field" determines which Eloqua field needs to receive the Site name'),
    '#options' => array(),
    '#empty_value' => 0,
  );
  $form['registration']['site_field']['#prefix'] = '<div id="site-field">';
  $form['registration']['site_field']['#suffix'] .= '</div>';

  $site_field_options = array();
  if ($reg_form_id != '0') {
    if ($eloqua_api_enabled) {
      $site_field_options = penton_eloqua_api_get_form_fields_by_form_id($reg_form_id, 'internal', $eloqua_rest_client);
    }
    elseif ($trip_error == 0) {
      $trip_error = 1;
      drupal_set_message($eloqua_error_message, 'error');
    }
  }

  // Email Address is required field.
  $fields = variable_get('penton_eloqua_api_eloqua_map', array('C_EmailAddress' => array('data_type' => 'text', 'profile_field' => 'mail')));
  $fields = is_array($fields) ? $fields : unserialize($fields);

  $profile_fields = array();
  // Grab profile fields from 'user' entity fields.
  foreach (field_info_instances('user', 'user') as $field_name => $instance) {
    if ($field_name != 'field_penton_profile') {
      $profile_fields[$field_name] = $instance['label'];
    }
  }
  $profile_fields = array_merge($profile_fields, _penton_eloqua_api_get_profile_fields());
  $profile_fields['mail'] = 'User: E-mail Address';
  $profile_fields['name'] = 'Username';
  asort($profile_fields);

  $entity_list = array();
  if ($eloqua_api_enabled) {
    $entity_list = penton_eloqua_api_get_contact_field_list($eloqua_rest_client);
  }
  elseif ($trip_error == 0) {
    $trip_error = 1;
    drupal_set_message($eloqua_error_message, 'error');
  }

  $eloqua_data = array();
  $eloqua_options = array();
  foreach ($entity_list as $entity) {
    if (!$entity->isReadOnly()) {
      $eloqua_data[$entity->getInternalName()] = array(
        'display_name' => $entity->getName(),
        'data_type' => $entity->getDataType(),
      );
      $eloqua_options[$entity->getInternalName()] = $entity->getName();
    }
  }
  asort($eloqua_options);

  $form['fields'] = array(
    '#type' => 'markup',
    '#tree' => TRUE,
  );
  foreach ($fields as $eloqua_field => $field_data) {
    if ($eloqua_field != 'new' && $field_data['profile_field'] != PENTON_ELOQUA_API_SITE_FIELD) {
      $form['fields'][$eloqua_field] = array(
        '#type' => 'fieldset',
        '#title' => isset($field_data['display']) ? $field_data['display'] : $profile_fields[$field_data['profile_field']],
        '#tree' => TRUE,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      // Preserve custom association display names.
      if (isset($field_data['display'])) {
        $form['fields'][$eloqua_field]['display'] = array(
          '#type' => 'hidden',
          '#value' => $field_data['display'],
        );
      }
      // E-mail address needs to be mapped for Eloqua submissions, so it should
      // never be deleted.
      if ($eloqua_field != 'C_EmailAddress') {
        $form['fields'][$eloqua_field]['delete'] = array(
          '#type' => 'checkbox',
          '#title' => t('Delete this association'),
          '#default_value' => '0',
        );
      }
      $form['fields'][$eloqua_field]['profile_field'] = array(
        '#type' => 'hidden',
        '#prefix' => '<div><b>Machine Name:</b> ' . $field_data['profile_field'] . '</div>',
        '#value' => $field_data['profile_field'],
      );
      $form['fields'][$eloqua_field]['data_type'] = array(
        '#type' => 'hidden',
        '#prefix' => '<div><b>Data Type:</b> ' . penton_eloqua_api_get_rest_data_type($field_data['data_type']) . '</div>',
        '#value' => $field_data['data_type'],
      );

      if (isset($eloqua_data[$eloqua_field])) {
        $form['fields'][$eloqua_field]['eloqua_field'] = array(
          '#type' => 'markup',
          '#markup' => '<div><b>Associated with:</b> ' . $eloqua_data[$eloqua_field]['display_name'] . ' (' . $eloqua_field . ')</div>',
        );
      }
      else {
        $form['fields'][$eloqua_field]['eloqua_field'] = array(
          '#type' => 'markup',
          '#markup' => '<div><b>Associated with:</b> ' . $eloqua_field . '</div>',
        );
      }
      // Unset options to avoid overwriting data.
      unset($site_field_options[$eloqua_field]);
    }
    else {
      if ($reg_form_id != '0') {
        $form['registration']['site_field']['#default_value'] = $eloqua_field;
      }
    }
    // Unset the option to avoid overwriting existing values.
    unset($eloqua_options[$eloqua_field]);
  }

  // Only assign options if they're needed.
  if ($reg_form_id != '0') {
    $form['registration']['site_field']['#options'] = $site_field_options;
  }

  $form['fields']['new'] = array(
    '#type' => 'fieldset',
    '#title' => t('New Field Association'),
  );

  $form['fields']['new']['content_pillar_fields'] = array(
    '#type' => 'select',
    '#options' => $profile_fields,
    '#empty_value' => 0,
    '#empty_option' => '--',
    '#title' => t('Profile Field'),
  );

  $form['fields']['new']['eloqua_fields'] = array(
    '#type' => 'select',
    '#options' => $eloqua_options,
    '#empty_value' => 0,
    '#empty_option' => '--',
    '#title' => t('Eloqua Contact Field'),
  );
  $form['fields']['new']['multiselect'] = array(
    '#type' => 'checkbox',
    '#default_value' => 0,
    '#title' => t('Is Multi-Select List'),
  );
  $form['fields']['new']['freeform'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Field Association'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['fields']['new']['freeform']['freeform_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Eloqua Field'),
    '#description' => 'Use this field for Eloqua form fields that are not "Contact" fields. <br/><b>Note:</b> This will override anything set in the Eloqua Contact Fields dropdown.',
  );
  $form['fields']['new']['freeform']['freeform_data_type'] = array(
    '#type' => 'select',
    '#title' => t('Data Type'),
    '#options' => penton_eloqua_api_get_rest_data_type(),
  );
  $form['fields']['new']['freeform']['freeform_multiselect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Is Multi-Select List'),
  );
  $form['fields']['new']['freeform']['freeform_data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom Data Key'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['fields']['new']['freeform']['freeform_data']['display'] = array(
    '#type' => 'textfield',
    '#title' => t('Display Name'),
    '#description' => 'Provide a display name for this association (ex: \'File Name\')',
  );
  $form['fields']['new']['freeform']['freeform_data']['key'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Key'),
    '#description' => 'The key (ex: "mail" in $data[\'mail\']) of the array that will be sent to Eloqua. Use this to send non-profile data to Eloqua. <br/><b>Note:</b> This will override anything set in the Profile Fields dropdown.',
  );

  $form['eloqua_data'] = array('#type' => 'hidden', '#value' => serialize($eloqua_data));
  $form['profile_fields'] = array('#type' => 'hidden', '#value' => $profile_fields);
  if ($eloqua_api_enabled) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    );
  }
  elseif ($trip_error == 0) {
    drupal_set_message($eloqua_error_message, 'error');
  }

  return $form;
}

/**
 * Validate handler for Eloqua field mapping.
 */
function penton_eloqua_api_mapping_validate(&$form, &$form_state) {
  $freeform_field = $form_state['values']['fields']['new']['freeform']['freeform_field'];
  $freeform_field = preg_replace('/\s/', '', $freeform_field);
  // If the Eloqua field being mapped to is already mapped, throw error.
  if (!empty($freeform_field) && isset($form_state['values']['fields'][$freeform_field])) {
    form_error($form['fields']['new']['freeform']['freeform_field'], $freeform_field . ' has already been mapped.');
  }
  // For proper form display, a custom key requires a display name.
  if (!empty($form_state['values']['fields']['new']['freeform']['freeform_data']['key']) &&
    empty($form_state['values']['fields']['new']['freeform']['freeform_data']['display'])) {
    form_error($form['fields']['new']['freeform']['freeform_data']['display'], 'Provide a display name for your custom key.');
  }
}

/**
 * Submit handler for Eloqua field mapping.
 */
function penton_eloqua_api_mapping_submit(&$form, &$form_state) {
  include_once drupal_get_path('module', 'penton_eloqua_api') . '/includes/penton_eloqua_api.helper.inc';
  $eloqua_data = unserialize($form_state['values']['eloqua_data']);
  $eloqua_map = array();
  foreach ($form_state['values']['fields'] as $field_name => $field_data) {
    if ($field_name == 'new' && ($field_data['eloqua_fields'] != '0' ||
        !empty($field_data['freeform']['freeform_field'])) && ($field_data['content_pillar_fields'] != '0' ||
        !empty($field_data['freeform']['freeform_data']['key']))) {
      $eloqua_field = !empty($field_data['freeform']['freeform_field']) ? preg_replace('/\s/', '', $field_data['freeform']['freeform_field']) : $field_data['eloqua_fields'];
      $data_type = !empty($field_data['freeform']['freeform_field']) ? ($field_data['freeform']['freeform_multiselect'] == '0' ? $field_data['freeform']['freeform_data_type'] : 'multi-select') : ($field_data['multiselect'] == 0 ? $eloqua_data[$field_data['eloqua_fields']]['data_type'] : 'multi-select');
      $eloqua_map[$eloqua_field] = array(
        'data_type' => $data_type,
        'profile_field' => !empty($field_data['freeform']['freeform_data']['key']) ? $field_data['freeform']['freeform_data']['key'] : $field_data['content_pillar_fields'],
      );
      if (!empty($field_data['freeform']['freeform_data']['key']) || isset($field_data['display'])) {
        $eloqua_map[$eloqua_field]['display'] = $field_data['freeform']['freeform_data']['display'];
      }
    }
    elseif (isset($field_data['delete']) && $field_data['delete'] == '1') {
      unset($eloqua_map[$field_name]);
    }
    else {
      unset($field_data['delete']);
      $eloqua_map[$field_name] = $field_data;
    }
  }

  if ($form_state['values']['registration_form'] != '0' && !empty($form_state['values']['site_field'])) {
    $eloqua_map[$form_state['values']['site_field']] = array(
      'data_type' => 'text',
      'profile_field' => PENTON_ELOQUA_API_SITE_FIELD,
    );
  }

  variable_set('penton_eloqua_api_eloqua_map', serialize($eloqua_map));

  $eloqua_registration_form_id = $form_state['values']['registration_form'];
  variable_set('penton_eloqua_api_reg_form_id', $eloqua_registration_form_id);
  variable_set('penton_eloqua_api_reg_form_html_name', penton_eloqua_api_get_form_html_name_by_form_id($eloqua_registration_form_id));

  $eloqua_registration_form_name = $form['registration']['registration_form']['#options'][$eloqua_registration_form_id];
  variable_set('penton_eloqua_api_reg_form_name', $eloqua_registration_form_name);

  if ($form_state['values']['registration_form'] != '0') {
    $fields = penton_eloqua_api_get_form_fields_by_form_id($form_state['values']['registration_form'], 'id');
    $fields = serialize($fields);
    variable_set('penton_eloqua_api_reg_form_fields', $fields);
  }
}

/**
 * Admin form for Eloqua tracking config.
 */
function penton_eloqua_api_tracking() {
  $form = array();

  $form['tracking'] = array(
    '#type' => 'fieldset',
    '#title' => t('Eloqua User Tracking Settings'),
    '#collapsinle' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['tracking']['penton_eloqua_api_tracking_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Tracking enabled'),
    '#description' => t('When enabled, each page visit is tracked by Eloqua and customer GUID is sent to Eloqua to associate with contact'),
    '#default_value' => variable_get('penton_eloqua_api_tracking_enabled'),
  );

  $form['tracking']['penton_eloqua_api_site_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Eloqua site id'),
    '#description' => t('Fill this field with site id generated in Eloqua admin panel in tracking section'),
    '#default_value' => variable_get('penton_eloqua_api_site_id'),
  );

  return system_settings_form($form);
}

/**
 * Replaces site field.
 */
function _penton_eloqua_api_replace_site_field($form, &$form_state) {
  unset($form['registration']['site_field']['#value']);
  return $form['registration']['site_field'];
}
