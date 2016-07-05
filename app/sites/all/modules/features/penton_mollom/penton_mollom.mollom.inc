<?php
/**
 * @file
 * penton_mollom.mollom.inc
 */

/**
 * Implements hook_default_mollom_form().
 */
function penton_mollom_default_mollom_form() {
  $export = array();

  $mollom_form = new stdClass();
  $mollom_form->disabled = FALSE; /* Edit this to true to make a default mollom_form disabled initially */
  $mollom_form->api_version = 1;
  $mollom_form->form_id = 'comment_node_article_form';
  $mollom_form->entity = 'comment';
  $mollom_form->bundle = 'comment_node_article';
  $mollom_form->mode = 2;
  $mollom_form->checks = array(
    0 => 'spam',
  );
  $mollom_form->unsure = 'binary';
  $mollom_form->discard = TRUE;
  $mollom_form->moderation = FALSE;
  $mollom_form->enabled_fields = array(
    0 => 'comment_body',
  );
  $mollom_form->strictness = 'normal';
  $mollom_form->module = 'comment';
  $export['comment_node_article_form'] = $mollom_form;

  $mollom_form = new stdClass();
  $mollom_form->disabled = FALSE; /* Edit this to true to make a default mollom_form disabled initially */
  $mollom_form->api_version = 1;
  $mollom_form->form_id = 'forward_form';
  $mollom_form->entity = '';
  $mollom_form->bundle = '';
  $mollom_form->mode = 2;
  $mollom_form->checks = array(
    0 => 'spam',
  );
  $mollom_form->unsure = 'binary';
  $mollom_form->discard = TRUE;
  $mollom_form->moderation = FALSE;
  $mollom_form->enabled_fields = array(
    0 => 'message',
  );
  $mollom_form->strictness = 'normal';
  $mollom_form->module = 'forward';
  $export['forward_form'] = $mollom_form;

  $mollom_form = new stdClass();
  $mollom_form->disabled = FALSE; /* Edit this to true to make a default mollom_form disabled initially */
  $mollom_form->api_version = 1;
  $mollom_form->form_id = 'penton_user_register_email_this_form';
  $mollom_form->entity = '';
  $mollom_form->bundle = '';
  $mollom_form->mode = 2;
  $mollom_form->checks = array(
    0 => 'spam',
  );
  $mollom_form->unsure = 'binary';
  $mollom_form->discard = TRUE;
  $mollom_form->moderation = FALSE;
  $mollom_form->enabled_fields = array(
    0 => 'message',
    1 => 'mail',
  );
  $mollom_form->strictness = 'normal';
  $mollom_form->module = 'penton_user_register';
  $export['penton_user_register_email_this_form'] = $mollom_form;

  $mollom_form = new stdClass();
  $mollom_form->disabled = FALSE; /* Edit this to true to make a default mollom_form disabled initially */
  $mollom_form->api_version = 1;
  $mollom_form->form_id = 'user_profile_form';
  $mollom_form->entity = 'user';
  $mollom_form->bundle = 'user';
  $mollom_form->mode = 2;
  $mollom_form->checks = array(
    0 => 'spam',
  );
  $mollom_form->unsure = 'binary';
  $mollom_form->discard = TRUE;
  $mollom_form->moderation = FALSE;
  $mollom_form->enabled_fields = array(
    0 => 'field_penton_additional_degree',
    1 => 'field_penton_additional_school',
    2 => 'field_penton_advantage_id',
    3 => 'field_penton_degree_credential',
    4 => 'field_penton_job_title',
    5 => 'field_penton_legacy_node_access',
    6 => 'field_penton_legal_comm',
    7 => 'field_penton_marketing_tagline',
    8 => 'field_penton_primary_job_role',
    9 => 'field_penton_profile][und][0][first_name',
    10 => 'field_penton_profile][und][0][last_name',
    11 => 'field_penton_profile][und][0][organisation_name',
    12 => 'field_penton_secondary_job_role',
    13 => 'field_penton_skills',
    14 => 'field_penton_source_id',
    15 => 'field_penton_specialities',
    16 => 'field_penton_summary',
    17 => 'field_penton_transaction_id',
    18 => 'field_penton_twitter_account',
    19 => 'field_penton_university',
  );
  $mollom_form->strictness = 'normal';
  $mollom_form->module = 'user';
  $export['user_profile_form'] = $mollom_form;

  return $export;
}
