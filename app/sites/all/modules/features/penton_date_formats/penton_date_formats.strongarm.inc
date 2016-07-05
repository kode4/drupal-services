<?php
/**
 * @file
 * penton_date_formats.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_date_formats_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_default_timezone';
  $strongarm->value = 'America/New_York';
  $export['date_default_timezone'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_article_date_format';
  $strongarm->value = 'M d, Y';
  $export['date_format_article_date_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_article_date_format_full_month';
  $strongarm->value = 'F d, Y';
  $export['date_format_article_date_format_full_month'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_medium_date';
  $strongarm->value = 'M d, Y';
  $export['date_format_medium_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_rss_date_format';
  $strongarm->value = 'D, d M Y H:i:s O';
  $export['date_format_rss_date_format'] = $strongarm;

  return $export;
}
