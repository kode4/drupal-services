<?php
/**
 * @file
 * penton_inline_form_errors_settings.ife.inc
 */

/**
 * Implements hook_ife_default_settings().
 */
function penton_inline_form_errors_settings_ife_default_settings() {
  $export = array();

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'user_login';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['user_login'] = $ife;

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'user_pass';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['user_pass'] = $ife;

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'user_register_form';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['user_register_form'] = $ife;

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'penton_user_register_advanced_form';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['penton_user_register_advanced_form'] = $ife;

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'penton_user_register_basic_form';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['penton_user_register_basic_form'] = $ife;

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'penton_user_register_email_this_form';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['penton_user_register_email_this_form'] = $ife;

  $ife = new stdClass();
  $ife->api_version = 1;
  $ife->form_id = 'penton_user_register_advanced_questions_form';
  $ife->field_types = '';
  $ife->status = 1;
  $ife->display = -1;
  $export['penton_user_register_advanced_questions_form'] = $ife;

  return $export;
}
