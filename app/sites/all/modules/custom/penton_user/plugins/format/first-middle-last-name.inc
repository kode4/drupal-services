<?php

/**
 * @file
 * Generates a first name + last name format.
 */

$plugin = array(
  'title' => t('Name (First name, Middle name, Last name)'),
  'format callback' => 'addressfield_format_name_full_penton_generate',
  'type' => 'name',
  'weight' => 0,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_name_full_penton_generate(&$format, $address, $context = array()) {
  $format['name_block'] = array(
    '#type' => 'addressfield_container',
    '#attributes' => array(
      'class' => array('addressfield-container-inline', 'name-block'),
    ),
    '#weight' => -100,
    // The addressfield is considered empty without a country, hide all fields
    // until one is selected.
    '#access' => !empty($address['country']),
  );
  // Maxlength is set to 127 so that the name_line still can be created without
  // exceeding the char limit from the database.
  $format['name_block']['first_name'] = array(
    '#title' => t('First name'),
    '#size' => 30,
    '#maxlength' => 127,
    '#required' => FALSE,
    '#attributes' => array(
      'class' => array('first-name'),
      'autocomplete' => 'given-name',
    ),
  );
  $format['name_block']['middle_name'] = array(
    '#title' => t('Middle name'),
    '#size' => 30,
    '#maxlength' => 127,
    '#required' => FALSE,
    '#prefix' => ' ',
    '#attributes' => array(
      'class' => array('middle-name'),
      'autocomplete' => 'mid-name',
    ),
  );
  $format['name_block']['last_name'] = array(
    '#title' => t('Last name'),
    '#size' => 30,
    '#maxlength' => 127,
    '#required' => FALSE,
    '#prefix' => ' ',
    '#attributes' => array(
      'class' => array('last-name'),
      'autocomplete' => 'family-name',
    ),
  );

  // Post-process the format stub, depending on the rendering mode.
  // Replace the addressfield #process and #pre_render which include hardcoded
  // keys to be able to use our additionnal fields.
  // This is basically a copy of it without their hardcoded stuff, until the
  // patch in https://www.drupal.org/node/1225292 is ready.
  if ($context['mode'] == 'form') {
    $format['#addressfield'] = TRUE;
    $format['#process'][] = 'penton_addressfield_process_format_form';
  }
  elseif ($context['mode'] == 'render') {
    $format['#pre_render'][] = 'penton_addressfield_render_address';
  }
}

/**
 * Render the specific elements in the form.
 *
 * As addressfield excludes custom fields.
 *
 * @see addressfield_process_format_form()
 */
function penton_addressfield_process_format_form($format, &$form_state, $complete_form) {
  // Make sure to load all the plugins that participated in this format.
  ctools_include('plugins');
  foreach ($format['#handlers'] as $handler) {
    ctools_plugin_load_function('addressfield', 'format', $handler, 'format callback');
  }

  _penton_addressfield_process_format_form($format, $format['#address']);
  return $format;
}

/**
 * Helper function for render elements in the form.
 *
 * @see penton_addressfield_process_format_form()
 */
function _penton_addressfield_process_format_form(&$format, $address) {
  // Allow more field flexibility.
  $address_fields = array_keys($address);

  foreach (element_children($format) as $key) {
    $child = &$format[$key];
    if (in_array($key, $address_fields)) {
      // Set the form element type for the address component to whatever the
      // address format specified in its #widget_type property.
      if (isset($child['#widget_type'])) {
        $child['#type'] = $child['#widget_type'];
      }
      else {
        // If the element didn't specify a #widget_type and has options, turn it
        // into a select list and unset its #size value, which is typically used
        // to provide the width of a textfield.
        if (isset($child['#options'])) {
          $child['#type'] = 'select';
          unset($child['#size']);
        }
        else {
          // Otherwise go ahead and make it a textfield.
          $child['#type'] = 'textfield';
        }
      }

      if (isset($address[$key])) {
        $child['#default_value'] = $address[$key];
      }
    }

    // Recurse through the element's children if it has any.
    _penton_addressfield_process_format_form($child, $address);
  }
}


/**
 * Render an address in a given format.
 */
function penton_addressfield_render_address($format) {
  _penton_addressfield_render_address($format, $format['#address']);
  return $format;
}

/**
 * Helper function for rendering addresses.
 *
 * @see penton_addressfield_render_address()
 */
function _penton_addressfield_render_address(&$format, $address) {
  // Allow more flexibility on the fields.
  $address_fields = array_keys($address);
  foreach (element_children($format) as $key) {
    $child = &$format[$key];
    if (in_array($key, $address_fields, TRUE)) {
      if (isset($child['#render_type'])) {
        $child['#type'] = $child['#render_type'];
      }
      else {
        $child['#type'] = 'addressfield_container';
        if (!isset($child['#tag'])) {
          $child['#tag'] = 'span';
        }
      }

      // If the element instructs us to render the option value instead of the
      // raw address element value and its #options array has a matching key,
      // swap it out for the option value now.
      if (!empty($child['#render_option_value']) && isset($address[$key]) && isset($child['#options'][$address[$key]])) {
        $child['#children'] = check_plain($child['#options'][$address[$key]]);
      }
      elseif (isset($address[$key])) {
        $child['#children'] = check_plain($address[$key]);
      }
      else {
        $child['#children'] = '';
      }

      // Skip empty elements.
      if ((string) $child['#children'] === '') {
        $child['#access'] = FALSE;
      }

      // Add #field_prefix and #field_suffix to the prefixes and suffixes.
      if (isset($child['#field_prefix'])) {
        $child['#prefix'] = (isset($child['#prefix']) ? $child['#prefix'] : '') . $child['#field_prefix'];
      }
      if (isset($child['#field_suffix'])) {
        $child['#suffix'] = (isset($child['#suffix']) ? $child['#suffix'] : '') . $child['#field_suffix'];
      }
    }

    // Recurse through the child.
    _penton_addressfield_render_address($child, $address);
  }
}
