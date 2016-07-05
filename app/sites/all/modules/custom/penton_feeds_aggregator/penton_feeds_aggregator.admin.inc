<?php
/**
 * @file
 * Admin-related callbacks for Penton Feeds Aggregator.
 */

/**
 * Menu callback; displays the aggregator administration page.
 */
function penton_feeds_aggregator_admin_overview() {
  return penton_feeds_aggregator_view_admin_page();
}

/**
 * Displays the aggregator administration page.
 *
 * @return string
 *   The page HTML.
 */
function penton_feeds_aggregator_view_admin_page() {
  $attached_content_type = penton_feeds_aggregator_get_attached_content_type();
  $result = db_query('SELECT node.title, node.nid FROM {node} WHERE node.type = :type', array(':type' => $attached_content_type));
  $output = '<h3>' . t('Feeds') . '</h3>';

  $header = array(
    t('Title'),
    t('Items'),
    array('data' => t('Feed operations'), 'colspan' => '2'),
    array('data' => t('Feed items operations'), 'colspan' => '3'),
  );
  $rows = array();

  while ($feed = $result->fetch()) {
    $imported_feeds_name_result = db_query('SELECT COUNT(*) as items_count from {feeds_item} fni WHERE fni.feed_nid = :feed_nid', array(':feed_nid' => $feed->nid))->fetch();
    $imported_feeds_name = $imported_feeds_name_result->items_count;
    $imported_feeds_type = penton_feeds_aggregator_get_target_content_type($feed->nid);
    $rows[] = array(
      l($feed->title, "node/$feed->nid"),
      $imported_feeds_type . " (" . format_plural($imported_feeds_name, '1 node', '@count nodes') . ")",
      l(t('Edit'), "node/$feed->nid/edit"),
      l(t('Delete'), "node/$feed->nid/delete"),
      l(t('List items'), "node/$feed->nid"),
      l(t('Import items'), "node/$feed->nid/import"),
      l(t('Delete items'), "node/$feed->nid/delete-items"),
    );
  }

  if (empty($rows)) {
    $output .= t('There are no imported feeds yet') . '<br>';
  }
  else {
    $output .= theme_table(array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(),
      'caption' => '',
      'colgroups' => array(),
      'sticky' => '',
      'empty' => '',
    ));
  }

  $content_link = str_replace('_', '-', $attached_content_type);
  $output .= "<a href='../../node/add/" . $content_link . "'> Add new feed</a>";

  return $output;
}
