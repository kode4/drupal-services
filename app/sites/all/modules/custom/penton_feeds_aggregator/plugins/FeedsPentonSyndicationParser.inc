<?php
/**
 * @file
 * Feeds Parser.
 */

 /**
  * Implementation of FeedsSyndicationParser class.
  */
class FeedsPentonSyndicationParser extends FeedsSyndicationParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    feeds_include_library('common_syndication_parser.inc', 'common_syndication_parser');
    $feed = common_syndication_parser_parse($fetcher_result->getRaw());
    $result = new FeedsParserResult();
    $result->title = $feed['title'];
    $result->description = $feed['description'];
    $result->link = $feed['link'];
    if (is_array($feed['items'])) {
      foreach ($feed['items'] as $item) {
        if (isset($item['geolocations'])) {
          foreach ($item['geolocations'] as $k => $v) {
            $item['geolocations'][$k] = new FeedsGeoTermElement($v);
          }
        }
        if (empty($item['url'])) {
          $item['url'] = 'guid-' . $item['guid'];
        }
        $result->items[] = $item;
      }
    }
    return $result;
  }

  /**
   * Returns mapping sources.
   */
  public function getMappingSources() {
    return array(
      'title' => array(
        'name' => t('Title'),
        'description' => t('Title of the feed item.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'summary' => array(
        'name' => t('Summary'),
        'description' => t('Summary of the feed item.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'description' => array(
        'name' => t('Description'),
        'description' => t('Description of the feed item.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'author_name' => array(
        'name' => t('Author name'),
        'description' => t("Name of the feed item's author."),
        'target' => '',
        'unique' => FALSE,
      ),
      'timestamp' => array(
        'name' => t('Published date'),
        'description' => t('Published date as UNIX time GMT of the feed item.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'url' => array(
        'name' => t('Item URL (link)'),
        'description' => t('URL of the feed item.'),
        'target' => 'url',
        'unique' => TRUE,
      ),
      'guid' => array(
        'name' => t('Item GUID'),
        'description' => t('Global Unique Identifier of the feed item.'),
        'target' => '',
        'unique' => TRUE,
      ),
      'tags' => array(
        'name' => t('Categories'),
        'description' => t('An array of categories that have been assigned to the feed item.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'geolocations' => array(
        'name' => t('Geo Locations'),
        'description' => t('An array of geographic locations with a name and a position.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'parent:uid' => array(
        'name' => t('Feed node: User ID'),
        'description' => t('The feed node author uid.'),
        'target' => '',
        'unique' => FALSE,
      ),
      'parent:nid' => array(
        'name' => t('Feed node: Node ID'),
        'description' => t('The feed node nid.'),
        'target' => '',
        'unique' => FALSE,
      ),
    );
  }

}
