<?php
/**
 * @file
 * This is a admin part forms and callbacks for core module.
 */

/**
 * Admin variables form callback.
 *
 * @return mixed
 *   form object.
 */
function penton_core_admin_variables_tab_form() {
  $form['typekit'] = array(
    '#type' => 'fieldset',
    '#title' => t('Typekit'),
  );

  $form['typekit']['penton_core_typekit_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Kit ID'),
    '#default_value' => variable_get('penton_core_typekit_id', 'ntl8rdl'),
    '#size' => 30,
    '#maxlength' => 255,
    '#description' => t('Typekit KitID configured for this site.'),
  );

  return system_settings_form($form);
}
