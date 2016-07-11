<?php
/**
 * @file
 * penton_google_sitemap.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function penton_google_sitemap_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_cache_timeout';
  $strongarm->value = '15';
  $export['googlenews_cache_timeout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_content_hours';
  $strongarm->value = '48';
  $export['googlenews_content_hours'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_node_types';
  $strongarm->value = array(
    0 => 'article',
  );
  $export['googlenews_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_publication_name';
  $strongarm->value = '';
  $export['googlenews_publication_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_tag_access';
  $strongarm->value = '';
  $export['googlenews_tag_access'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_tag_genres';
  $strongarm->value = array();
  $export['googlenews_tag_genres'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_tag_geo_locations';
  $strongarm->value = '';
  $export['googlenews_tag_geo_locations'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_tag_keywords';
  $strongarm->value = '';
  $export['googlenews_tag_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'googlenews_tag_stock_tickers';
  $strongarm->value = '';
  $export['googlenews_tag_stock_tickers'] = $strongarm;

  return $export;
}
