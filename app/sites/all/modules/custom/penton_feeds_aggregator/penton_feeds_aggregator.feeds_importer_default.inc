<?php
/**
 * @file
 * Importer defaults.
 */

/**
 * Implements hook_feeds_importer_default().
 */
function penton_feeds_aggregator_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'penton_feed_importer';
  $feeds_importer->config = array(
    'name' => 'Penton Feed Importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsBloombergHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsPentonSyndicationParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsPentonAggregatorProcessor',
      'config' => array(
        'expire' => '-1',
        'mappings' => array(),
        'content_type' => FALSE,
      ),
    ),
    'content_type' => PENTON_FEEDS_AGGREGATOR_FEED_CONTENT_TYPE,
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => '-1',
    'import_on_create' => 0,
  );
  $export['penton_feed_importer'] = $feeds_importer;

  return $export;
}
