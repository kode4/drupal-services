<?php
/**
 * @file
 * penton_article.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function penton_article_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'article_node';
  $context->description = 'The article node display';
  $context->tag = 'article';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'article' => 'article',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The article node display');
  t('article');
  $export['article_node'] = $context;

  return $export;
}
