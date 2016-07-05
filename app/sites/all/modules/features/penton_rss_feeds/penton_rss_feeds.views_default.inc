<?php
/**
 * @file
 * penton_rss_feeds.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function penton_rss_feeds_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'rss_views';
  $view->description = 'Stores all the RSS displays.';
  $view->tag = 'penton, rss';
  $view->base_table = 'node';
  $view->human_name = 'RSS views';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['slave'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Allow in RSS feed (field_penton_allow_in_rss_feed) */
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['id'] = 'field_penton_allow_in_rss_feed_value';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['table'] = 'field_data_field_penton_allow_in_rss_feed';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['field'] = 'field_penton_allow_in_rss_feed_value';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['group'] = 1;
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['reduce_duplicates'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
  );

  /* Display: Full text feed */
  $handler = $view->new_display('feed', 'Full text feed', 'full_text_feed');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Front page feed';
  $handler->display->display_options['display_description'] = 'Full text';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Full text articles';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['row_options']['item_length'] = 'rss';
  $handler->display->display_options['path'] = 'articles.xml';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
  );
  $handler->display->display_options['sitename_title'] = '1';

  /* Display: Public RSS feed */
  $handler = $view->new_display('feed', 'Public RSS feed', 'feed_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['style_options']['description'] = 'Public RSS feed';
  $handler->display->display_options['row_plugin'] = 'rss_fields';
  $handler->display->display_options['row_options']['title_field'] = 'title';
  $handler->display->display_options['row_options']['link_field'] = 'path';
  $handler->display->display_options['row_options']['description_field'] = 'field_penton_content_summary';
  $handler->display->display_options['row_options']['creator_field'] = 'field_penton_author';
  $handler->display->display_options['row_options']['date_field'] = 'field_penton_published_datetime';
  $handler->display->display_options['row_options']['guid_field_options'] = array(
    'guid_field' => 'nid',
    'guid_field_is_permalink' => 0,
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field: Content Summary */
  $handler->display->display_options['fields']['field_penton_content_summary']['id'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['table'] = 'field_data_field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['field'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['label'] = '';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_content_summary']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_content_summary']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_penton_content_summary']['field_api_classes'] = TRUE;
  /* Field: Content: Author */
  $handler->display->display_options['fields']['field_penton_author']['id'] = 'field_penton_author';
  $handler->display->display_options['fields']['field_penton_author']['table'] = 'field_data_field_penton_author';
  $handler->display->display_options['fields']['field_penton_author']['field'] = 'field_penton_author';
  $handler->display->display_options['fields']['field_penton_author']['label'] = '';
  $handler->display->display_options['fields']['field_penton_author']['alter']['preserve_tags'] = '<a>';
  $handler->display->display_options['fields']['field_penton_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_author']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_author']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_penton_author']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_penton_author']['delta_offset'] = '0';
  /* Field: Content: Published DateTime */
  $handler->display->display_options['fields']['field_penton_published_datetime']['id'] = 'field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['table'] = 'field_data_field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['field'] = 'field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_penton_published_datetime']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['settings'] = array(
    'format_type' => 'rss_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['path']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Allow in RSS feed (field_penton_allow_in_rss_feed) */
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['id'] = 'field_penton_allow_in_rss_feed_value';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['table'] = 'field_data_field_penton_allow_in_rss_feed';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['field'] = 'field_penton_allow_in_rss_feed_value';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['value'] = array(
    0 => '0',
  );
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['group'] = 1;
  $handler->display->display_options['filters']['field_penton_allow_in_rss_feed_value']['reduce_duplicates'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
  );
  /* Filter criterion: Content: Article Type (field_penton_article_type) */
  $handler->display->display_options['filters']['field_penton_article_type_tid']['id'] = 'field_penton_article_type_tid';
  $handler->display->display_options['filters']['field_penton_article_type_tid']['table'] = 'field_data_field_penton_article_type';
  $handler->display->display_options['filters']['field_penton_article_type_tid']['field'] = 'field_penton_article_type_tid';
  $handler->display->display_options['filters']['field_penton_article_type_tid']['value'] = array(
    0 => '1',
  );
  $handler->display->display_options['filters']['field_penton_article_type_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_penton_article_type_tid']['vocabulary'] = 'article_type';
  $handler->display->display_options['path'] = 'rss.xml';
  $handler->display->display_options['sitename_title'] = 1;
  $export['rss_views'] = $view;

  return $export;
}
