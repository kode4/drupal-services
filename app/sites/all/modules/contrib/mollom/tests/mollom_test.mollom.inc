<?php
/**
 * @file
 * mollom_test.mollom.inc
 */

/**
 * Implements hook_default_mollom_form().
 */
function mollom_test_default_mollom_form() {
  $mollom_form = new stdClass();
  $mollom_form->disabled = FALSE; /* Edit this to true to make a default mollom_form disabled initially */
  $mollom_form->api_version = 1;
  $mollom_form->form_id = 'mollom_exported_basic_test_form';
  $mollom_form->entity = '';
  $mollom_form->bundle = '';
  $mollom_form->mode = 2;
  $mollom_form->checks = array(
    0 => 'spam',
  );
  $mollom_form->unsure = 'captcha';
  $mollom_form->discard = TRUE;
  $mollom_form->moderation = FALSE;
  $mollom_form->enabled_fields = array(
    0 => 'title',
    1 => 'body',
    2 => 'exclude',
    3 => 'parent][child',
    4 => 'field',
  );
  $mollom_form->strictness = 'normal';
  $mollom_form->module = 'mollom_test';

  $export['mollom_exported_basic_test_form'] = $mollom_form;

  return $export;
}
