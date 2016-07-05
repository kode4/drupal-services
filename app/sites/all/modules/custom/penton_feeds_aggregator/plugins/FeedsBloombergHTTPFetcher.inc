<?php
/**
 * @file
 * HTTP Fetcher for Bloomberg feeds.
 */

require_once drupal_get_path('module', 'feeds') . '/includes/FeedsConfigurable.inc';
require_once drupal_get_path('module', 'feeds') . '/includes/FeedsSource.inc';

require_once drupal_get_path('module', 'feeds') . '/plugins/FeedsPlugin.inc';
require_once drupal_get_path('module', 'feeds') . '/plugins/FeedsFetcher.inc';
require_once drupal_get_path('module', 'feeds') . '/plugins/FeedsHTTPFetcher.inc';

/**
 * Fetcher for Bloomberg feeds.
 */
class FeedsBloombergHTTPFetcher extends FeedsHTTPFetcher {
  /**
   * Implements FeedsHTTPFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);

    if ($this->isBloomberg($source->feed_nid)) {
      return new FeedsBloombergHTTPFetcherResult($source_config['source']);
    }

    return new FeedsHTTPFetcherResult($source_config['source']);
  }

  /**
   * Returns true if feed is Bloomberg.
   */
  public function isBloomberg($id) {
    $query = db_query(
      'SELECT feed.config AS config FROM node AS n LEFT JOIN feeds_source AS feed ON feed.feed_nid = n.nid WHERE n.nid = :nid',
      array(':nid' => $id)
    );
    $config = unserialize($query->fetch()->config);

    return (
      isset($config['FeedsPentonAggregatorProcessor']['feed_bloomberg']) &&
      $config['FeedsPentonAggregatorProcessor']['feed_bloomberg'] == 1
    );
  }

}

/**
 * FeedsHTTPFetcherResult class for bloomberg feeds.
 */
class FeedsBloombergHTTPFetcherResult extends FeedsHTTPFetcherResult {
  protected $url;

  /**
   * Implementation of FeedsHTTPFetcherResult::getRaw().
   */
  public function getRaw() {
    $result = drupal_http_request($this->url, array(
      'headers' => array('Authorization' => 'Bearer'),
      'method' => 'POST',
    ));

    if (!in_array($result->code, array(200, 201, 202, 203, 204, 205, 206))) {
      throw new Exception(t('Download of @url failed with code !code.', array('@url' => $this->url, '!code' => $result->code)));
    }

    return $result->data;
  }

}
