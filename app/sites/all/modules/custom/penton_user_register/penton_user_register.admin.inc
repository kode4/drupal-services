<?php
/**
 * @file
 * Admin-related callbacks for Penton User Registration.
 */

/**
 * Admin settings form for Penton User Registration.
 */
function penton_user_register_admin_settings($form, &$form_state) {
  $form['penton_user_register_newsletter_signup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Newsletter Sign-Up box'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['penton_user_register_newsletter_signup']['penton_user_register_newsletter_signup_enable_advanced'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show two custom questions in newsletter signup flow'),
    '#default_value' => variable_get('penton_user_register_newsletter_signup_enable_advanced', 1),
  );

  return system_settings_form($form);
}
