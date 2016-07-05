<?php
/**
 * @file
 * Admin-related callbacks for Fulfillment Services.
 */

/**
 * Admin settings form for Fulfillment Services.
 */
function penton_fulfillment_services_admin_settings($form, &$form_state) {
  $form['esp_web_services'] = array(
    '#type' => 'fieldset',
    '#title' => t('ESP Web Services'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['esp_web_services']['esp_web_services_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable'),
    '#default_value' => variable_get('esp_web_services_enable', FALSE),
    '#description' => t('<a href="!esp" rel="external" target="_blank">ESP</a> has developed a suite of Fulfillment Web Services. These Web Services support subscription and product fulfillment in a real-time integrated database environment. Services are provided for all basic subscription functions, e-commerce, and gate keeping functions. Services can be used for single subscriptions or for multiple subscriptions integrated with ancillary products. These Web Services support both an individual subscriber model and a customer-centric model for e-commerce transactions and include the ability to retrieve history on multiple titles and products for one subscriber.',
      array(
        '!esp' => url('http://www.espcomp.com/', array('external' => TRUE)),
      )),
    '#required' => FALSE,
  );

  $form['esp_web_services']['esp_web_services_sandbox_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sandbox Mode'),
    '#default_value' => variable_get('esp_web_services_sandbox_mode', FALSE),
    '#description' => t('In computer security, a sandbox is a security mechanism for separating running programs.'),
    '#required' => FALSE,
  );

  $form['esp_web_services']['esp_web_services_cuid'] = array(
    '#type' => 'textfield',
    '#title' => t('Customer User ID'),
    '#default_value' => variable_get('esp_web_services_cuid', ''),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('Several different clients and publishers use the services provided by ESP. Therefore, ESP authenticates them separately.'),
  );

  $form['esp_web_services']['esp_web_services_cpwd'] = array(
    '#type' => 'textfield',
    '#title' => t('Customer Password'),
    '#default_value' => variable_get('esp_web_services_cpwd', NULL),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('The password to be able to call the service.'),
  );

  $form['esp_web_services']['esp_web_services_pubcode'] = array(
    '#type' => 'select',
    '#title' => t('Publication Code'),
    '#default_value' => variable_get('esp_web_services_pubcode', ''),
    '#options' => array(
      '' => t('Select'),
      'RN' => t("Nation's Restaurant News (RN)"),
      'SN' => t('Supermarket News (SN)'),
      'TE' => t('Trusts and Estates (TE)'),
    ),
    '#description' => t('The identification code of the publication.'),
  );

  $form['esp_web_services']['esp_web_services_promo_code_for_new_subscriptions'] = array(
    '#type' => 'textfield',
    '#title' => t('Promo Code for New Subscriptions'),
    '#default_value' => variable_get('esp_web_services_promo_code_for_new_subscriptions', ''),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('The promo code value to populate the parameter "PK" at new subscriptions.'),
  );

  $form['esp_web_services']['esp_web_services_promo_code_for_renewals'] = array(
    '#type' => 'textfield',
    '#title' => t('Promo Code for Renewals'),
    '#default_value' => variable_get('esp_web_services_promo_code_for_renewals', ''),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('The promo code value to populate the parameter "PK" at renewals.'),
  );

  $form['esp_web_services']['esp_web_services_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => variable_get('esp_web_services_label', t('ESP Web Services')),
    '#size' => 30,
    '#maxlength' => 55,
    '#description' => t('The distinctive name to identify "ESP Web Services" to end users.'),
  );

  return system_settings_form($form);
}
