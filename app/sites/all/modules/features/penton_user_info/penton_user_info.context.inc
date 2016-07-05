<?php
/**
 * @file
 * penton_user_info.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function penton_user_info_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'penton_core_blocks_user_profile';
  $context->description = 'user profile block';
  $context->tag = 'Penton Core Theme';
  $context->conditions = array(
    'user_page' => array(
      'values' => array(
        'form' => 'form',
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'current',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'penton_user-account_information' => array(
          'module' => 'penton_user',
          'delta' => 'account_information',
          'region' => 'left_col',
          'weight' => '-10',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'main_col',
          'weight' => '-10',
        ),
        'menu-menu-footer-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-footer-menu',
          'region' => 'footer',
          'weight' => '-10',
        ),
        'menu-menu-social-links' => array(
          'module' => 'menu',
          'delta' => 'menu-social-links',
          'region' => 'footer',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Penton Core Theme');
  t('user profile block');
  $export['penton_core_blocks_user_profile'] = $context;

  return $export;
}
