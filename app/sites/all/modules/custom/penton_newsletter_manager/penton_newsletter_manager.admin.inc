<?php
/**
 * @file
 * Admin-related callbacks for Penton Newsletter Manager.
 */

/**
 * Admin callback: Settings form for Newsletter import.
 */
function penton_newsletter_manager_import_settings() {
  $form = array();

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['general']['penton_newsletter_manager_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#description' => t('URL to CSV file from eNewsPRO'),
    '#default_value' => variable_get('penton_newsletter_manager_url', ''),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('penton_newsletter_manager_import_settings_submit'),
  );

  $form['import'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#submit' => array('penton_newsletter_manager_import_submit'),
  );

  return $form;
}

/**
 * Saves settings for Newsletter import.
 */
function penton_newsletter_manager_import_settings_submit($form, $form_state) {
  variable_set('penton_newsletter_manager_url', $form_state['values']['penton_newsletter_manager_url']);
}

/**
 * Saves settings for Newsletter import and import new newsletters.
 */
function penton_newsletter_manager_import_submit($form, $form_state) {
  variable_set('penton_newsletter_manager_url', $form_state['values']['penton_newsletter_manager_url']);
  penton_newsletter_manager_import_newsletters();
}

/**
 * Admin callback: Settings form for Newsletter manager.
 */
function penton_newsletter_manager_settings() {
  $form = array();

  $newsletters = entity_load('penton_newsletter');
  if (empty($newsletters)) {
    drupal_set_message(t('No newsletters have been imported.'), 'error');
    return;
  }

  $nl_options = array();
  $nl_enabled = variable_get('penton_newsletter_manager_enabled', array());
  foreach ($newsletters as $nlid => $newsletter) {
    if ($newsletter->active == 1) {
      $nl_options[$nlid] = $newsletter->title;
    }
  }

  $form['penton_newsletter_manager_enabled'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Newsletters'),
    '#description' => t('Set which newsletters will appear in the Newsletter Sign-Up box.'),
    '#options' => $nl_options,
    '#default_value' => $nl_enabled,
  );

  $form['penton_newsletter_manager_promoted'] = array(
    '#type' => 'select',
    '#title' => t('Promoted'),
    '#description' => t('This newsletter will be at top of list and be pre-checked'),
    '#options' => $nl_options,
    '#empty_value' => 0,
    '#default_value' => variable_get('penton_newsletter_manager_promoted', 0),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('penton_newsletter_manager_settings_submit'),
    '#weight' => 3,
  );

  return $form;
}

/**
 * Saves settings for Newsletter manager.
 */
function penton_newsletter_manager_settings_submit($form, $form_state) {
  $nl_enabled = array_keys(array_filter($form_state['values']['penton_newsletter_manager_enabled']));
  variable_set('penton_newsletter_manager_enabled', $nl_enabled);
  variable_set('penton_newsletter_manager_promoted', $form_state['values']['penton_newsletter_manager_promoted']);
}
