<?php
/**
 * @file
 * File creates form for TKLi settings and handle submit of this form.
 */

/**
 * Implements hook_form().
 */
function penton_tkli_settings_form($form, &$form_state) {

  $form['penton_tkli_enable'] = array(
    '#type' => 'checkbox',
    '#description' => t('Enable third-party offers, powered by
      <a href="!url" target="_blank">TKL Interactive</a>
      TKLi is a full-service interactive marketing,
      creative services and technology company.',
      array('!url' => url('http://www.tkli.com/'))),
    '#title' => t('Enable'),
    '#default_value' => variable_get('penton_tkli_enable', TRUE),
  );

  $form['penton_tkli_sandbox_mode'] = array(
    '#type' => 'checkbox',
    '#description' => t('In computer security, a sandbox is a security mechanism
      for separating running programs.'),
    '#title' => t('Sandbox mode'),
    '#default_value' => variable_get('penton_tkli_sandbox_mode', FALSE),
  );

  $form['penton_tkli_pid'] = array(
    '#type' => 'textfield',
    '#maxlength' => 15,
    '#size' => 20,
    '#description' => t('Several different clients and
      publishers use the services provided by TKLi.
      Therefore, TKLi authenticates them separately.'),
    '#default_value' => variable_get('penton_tkli_pid', ''),
    '#title' => t('Publisher ID:'),
  );

  $form['penton_tkli_pgid'] = array(
    '#type' => 'textfield',
    '#maxlength' => 15,
    '#size' => 20,
    '#description' => t('Corresponds to the specific page
      transferring control to the TKLi system.'),
    '#default_value' => variable_get('penton_tkli_pgid', ''),
    '#title' => t('Page ID:'),
  );

  return system_settings_form($form);
}
