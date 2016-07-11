<?php
/**
 * @file
 * penton_captcha.captcha.inc
 */

/**
 * Implements hook_captcha_default_points().
 */
function penton_captcha_captcha_default_points() {
  $export = array();

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'user_pass';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['user_pass'] = $captcha;

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'user_register_form';
  $captcha->module = '';
  $captcha->captcha_type = 'none';
  $export['user_register_form'] = $captcha;

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'penton_user_register_advanced_form';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['penton_user_register_advanced_form'] = $captcha;

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'penton_user_register_basic_form';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['penton_user_register_basic_form'] = $captcha;

  $captcha = new stdClass();
  $captcha->disabled = FALSE; /* Edit this to true to make a default captcha disabled initially */
  $captcha->api_version = 1;
  $captcha->form_id = 'penton_user_register_email_this_form';
  $captcha->module = '';
  $captcha->captcha_type = 'default';
  $export['penton_user_register_email_this_form'] = $captcha;

  return $export;
}
