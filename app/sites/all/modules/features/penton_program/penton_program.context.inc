<?php
/**
 * @file
 * penton_program.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function penton_program_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'program_term';
  $context->description = 'Display of the Program term page';
  $context->tag = 'program';
  $context->conditions = array(
    'taxonomy_term' => array(
      'values' => array(
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
        'views-penton_program_term-block_1' => array(
          'module' => 'views',
          'delta' => 'penton_program_term-block_1',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display of the Program term page');
  t('program');
  $export['program_term'] = $context;

  return $export;
}
