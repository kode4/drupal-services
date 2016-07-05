<?php
/**
 * @file
 * penton_wysiwyg.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function penton_wysiwyg_filter_default_formats() {
  $formats = array();

  // Exported format: Comments.
  $formats['comments'] = array(
    'format' => 'comments',
    'name' => 'Comments',
    'cache' => 1,
    'status' => 1,
    'weight' => 5,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<em> <strong> <blockquote> <br> <p>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_htmlcorrector' => array(
        'status' => 1,
        'weight' => 10,
      ),
    ),
  );

  return $formats;
}
