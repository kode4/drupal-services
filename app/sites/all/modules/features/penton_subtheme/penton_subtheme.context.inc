<?php
/**
 * @file
 * penton_subtheme.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function penton_subtheme_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'penton_core_theme_blocks';
  $context->description = 'Standard blocks output to the regions';
  $context->tag = 'Penton Core Theme';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~penton_core_blocks_user_profile' => '~penton_core_blocks_user_profile',
      ),
    ),
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'penton_blocks-penton_sidebar_recent' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_sidebar_recent',
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
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Penton Core Theme');
  t('Standard blocks output to the regions');
  $export['penton_core_theme_blocks'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'penton_core_theme_blocks_homepage';
  $context->description = 'Blocks output for homepage';
  $context->tag = 'Penton Core Theme';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'display_admin' => 'display_admin',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'penton_blocks-penton_newsletter_signup' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_newsletter_signup',
          'region' => 'main_col',
          'weight' => '-10',
        ),
        'penton_blocks-penton_featured_categories' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_featured_categories',
          'region' => 'main_col',
          'weight' => '-9',
        ),
        'penton_blocks-penton_featured_program' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_featured_program',
          'region' => 'main_col',
          'weight' => '-7',
        ),
        'penton_blocks-penton_featured_media' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_featured_media',
          'region' => 'main_col',
          'weight' => '-6',
        ),
        'penton_blocks-penton_top_stories_main' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_top_stories_main',
          'region' => 'main_col_first',
          'weight' => '-10',
        ),
        'penton_blocks-penton_usermarketing_promo' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_usermarketing_promo',
          'region' => 'main_col_second',
          'weight' => '-10',
        ),
        'penton_blocks-penton_top_stories_right' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_top_stories_right',
          'region' => 'main_col_second',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blocks output for homepage');
  t('Penton Core Theme');
  $export['penton_core_theme_blocks_homepage'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'penton_core_theme_category_and_program';
  $context->description = '';
  $context->tag = 'Penton Core Theme';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
        'categories' => 'categories',
        'program' => 'program',
      ),
      'options' => array(
        'term_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'penton_blocks-penton_usermarketing_promo' => array(
          'module' => 'penton_blocks',
          'delta' => 'penton_usermarketing_promo',
          'region' => 'main_col_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Penton Core Theme');
  $export['penton_core_theme_category_and_program'] = $context;

  return $export;
}
