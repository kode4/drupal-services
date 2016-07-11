<?php
/**
 * @file
 * Eloqua API helper functions.
 */

/**
 * Returns REST client.
 */
function penton_eloqua_api_get_rest_client($user = NULL, $pass = NULL) {
  include_once drupal_get_path('module', 'penton_eloqua_api') . '/includes/EloquaPentonClient.class.inc';
  $user = is_null($user) ? variable_get('penton_eloqua_api_username', '') : $user;
  $pass = is_null($pass) ? base64_decode(variable_get('penton_eloqua_api_pw', '')) : $pass;

  $result = FALSE;
  try {
    $result = new EloquaPentonClient(new EloquaCredentials($user, $pass));
  }
  catch (Exception $e) {
    _penton_eloqua_api_rest_fault_error($e);
  }
  return $result;
}

/**
 * Returns list of form with specified id.
 */
function penton_eloqua_api_get_form_list($key = 'form_id', $client = NULL) {
  $client = is_null($client) ? penton_eloqua_api_get_rest_client() : $client;

  $result = array();
  if ($client !== FALSE) {
    try {
      $forms = $client->getAllEloquaForms();
      foreach ($forms as $form) {
        if ($key == 'form_id') {
          $result[$form->id] = $form->name;
        }
        else {
          $result[$form->name] = $form->name;
        }
      }
    }
    catch (Exception $e) {
      _penton_eloqua_api_rest_fault_error($e);
    }
  }
  return $result;
}

/**
 * Returns fields of form with specified id.
 */
function penton_eloqua_api_get_form_fields_by_form_id($id, $key = 'internal', $client = NULL) {
  $client = is_null($client) ? penton_eloqua_api_get_rest_client() : $client;

  $result = array();
  if ($client !== FALSE) {
    try {
      $form = $client->getEloquaFormById($id);
      foreach ($form->getFields() as $field) {
        if ($key == 'internal') {
          $result[$field->getContactFieldInternalName()] = $field->getHtmlName();
        }
        else {
          $result[$field->getId()] = $field->getContactFieldInternalName();
        }
      }
    }
    catch (Exception $e) {
      _penton_eloqua_api_rest_fault_error($e);
    }
  }
  return $result;
}

/**
 * Returns form html name with specified id.
 */
function penton_eloqua_api_get_form_html_name_by_form_id($id, $key = 'internal', $client = NULL) {
  $client = is_null($client) ? penton_eloqua_api_get_rest_client() : $client;

  $result = array();
  if ($client !== FALSE) {
    try {
      if ($form = $client->getEloquaFormById($id)) {
        $result = $form->html_name;
      }
    }
    catch (Exception $e) {
      _penton_eloqua_api_rest_fault_error($e);
    }
  }
  return $result;
}

/**
 * Returns contact fields.
 */
function penton_eloqua_api_get_contact_field_list($client = NULL) {
  $client = is_null($client) ? penton_eloqua_api_get_rest_client() : $client;

  $result = array();
  if ($client !== FALSE) {
    try {
      $result = $client->getAllContactFields();
    }
    catch (Exception $e) {
      _penton_eloqua_api_rest_fault_error($e);
    }
  }
  return $result;
}

/**
 * Submits form.
 */
function penton_eloqua_api_submit_form($form_id, $data, $client = NULL) {
  $client = is_null($client) ? penton_eloqua_api_get_rest_client() : $client;

  if ($client !== FALSE) {
    $data = _penton_eloqua_api_build_form_data($data);
    try {
      $client->submitFormToEloqua($form_id, $data);
    }
    catch (Exception $e) {
      _penton_eloqua_api_rest_fault_error($e);
    }
  }
}

/**
 * Subscribes user to newsletter.
 */
function penton_eloqua_api_subscribe_user($eloqua_email_group_id, $user_email_address = NULL) {
  if (is_null($user_email_address)) {
    global $user;
    $user_email_address = $user->mail;
  }

  $client = penton_eloqua_api_get_rest_client();

  if ($client !== FALSE) {
    try {
      $client->subscribeUserToEmailGroup($user_email_address, $eloqua_email_group_id);
    }
    catch (Exception $e) {
      _penton_eloqua_api_rest_fault_error($e);
    }
  }
}

/**
 * Builds form data.
 */
function _penton_eloqua_api_build_form_data($data) {
  $data_wrapper = entity_metadata_wrapper('user', $data);

  $data = (array) $data;
  $eloqua_fields = unserialize(variable_get('penton_eloqua_api_reg_form_fields', array()));
  $eloqua_map = variable_get('penton_eloqua_api_eloqua_map', array());
  $eloqua_map = is_array($eloqua_map) ? $eloqua_map : unserialize($eloqua_map);
  $matches = array_intersect($eloqua_fields, array_keys($eloqua_map));
  $profile_fields = array_keys(_penton_eloqua_api_get_profile_fields());

  $formatted_data = array();
  foreach ($matches as $id => $eloqua_field) {
    $profile_field_name = $eloqua_map[$eloqua_field]['profile_field'];
    $value = '';
    if ($profile_field_name == PENTON_ELOQUA_API_SITE_FIELD) {
      // Site Field.
      $value = $data[$profile_field_name];
    }
    elseif (in_array($profile_field_name, $profile_fields)) {
      // Field from field_penton_profile array.
      if (isset($data_wrapper->field_penton_profile->{$profile_field_name})
        && !empty($data_wrapper->field_penton_profile->value())) {
        $value = $data_wrapper->field_penton_profile->{$profile_field_name}->value();
      }
    }
    elseif (isset($data_wrapper->{$profile_field_name})) {
      // Normal custom field.
      $value = $data_wrapper->{$profile_field_name}->value();

      // Retrieving value text out of value id.
      $field_info = field_info_field($profile_field_name);
      if (!empty($field_info)) {
        $possible_values = list_allowed_values($field_info);
        if (!empty($possible_values[$value])) {
          $value = $possible_values[$value];
        }
      }
    }
    if (!empty($value)) {
      // Format value according to Eloqua standards.
      $type = strtolower($eloqua_map[$eloqua_field]['data_type']);
      $formatted_data[$id] = _penton_eloqua_api_format_form_values($value, $type);
    }
  }
  return $formatted_data;
}

/**
 * Formats form values.
 */
function _penton_eloqua_api_format_form_values($value, $type) {
  $mapped_value = '';
  switch ($type) {
    case 'text':
    case 'numeric':
      $mapped_value = $value;
      break;

    case 'multi-select':
      $value_array = is_array($value) ? $value : (unserialize($value) ? unserialize($value) : explode(', ', $value));
      $mapped_value = implode('::', $value_array);
      break;

    case 'yesno':
      if ($value == '1' || $value == '0') {
        $mapped_value = $value == 1 ? 'Yes' : 'No';
      }
      if (strtolower($value) == 'yes' || strtolower($value) == 'no') {
        $mapped_value = strtolower($value) == 'yes' ? 'Yes' : 'No';
      }
      break;

    case 'date':
      $date = is_array($value) ? $value : unserialize($value);
      $date['month'] = strlen($date['month']) == 1 ? '0' . $date['month'] : $date['month'];
      $date['day'] = strlen($date['day']) == 1 ? '0' . $date['day'] : $date['day'];
      $mapped_value = $date['month'] . '/' . $date['day'] . '/' . $date['year'];
      break;
  }

  return $mapped_value;
}

/**
 * Returns type of REST data.
 */
function penton_eloqua_api_get_rest_data_type($type = NULL) {
  $types = array(
    'text' => 'Text',
    'numeric' => 'Numeric',
    'date' => 'Date',
    'yesno' => 'Yes/No',
    'multi-select' => 'Multi-Select',
  );

  if (is_null($type)) {
    return $types;
  }

  if (in_array($type, $types)) {
    return $types[$type];
  }

  return $type;
}

/**
 * Creates log entry with fault error.
 */
function _penton_eloqua_api_rest_fault_error(Exception $e) {
  watchdog('penton_eloqua_api', $e->getMessage());
  if (user_access('administer Eloqua settings')) {
    $error_message = check_plain('Eloqua: ' . $e->getMessage() . '. ' .
      l(t('Eloqua API Settings'), 'admin/config/services/penton_eloqua_api/api_settings'));
    drupal_set_message($error_message, 'error');
  }

}
