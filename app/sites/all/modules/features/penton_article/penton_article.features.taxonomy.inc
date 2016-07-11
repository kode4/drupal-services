<?php
/**
 * @file
 * penton_article.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function penton_article_taxonomy_default_vocabularies() {
  return array(
    'article_type' => array(
      'name' => 'Article Type',
      'machine_name' => 'article_type',
      'description' => 'The type of Article, e.g. Blog',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
