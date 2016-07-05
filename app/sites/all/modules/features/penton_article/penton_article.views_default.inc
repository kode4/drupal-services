<?php
/**
 * @file
 * penton_article.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function penton_article_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'penton_article_node';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Penton Article Node';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
  );

  /* Display: Title Block */
  $handler = $view->new_display('block', 'Title Block', 'block_1');
  $handler->display->display_options['block_description'] = 'Article Title Block';

  /* Display: Summary Block */
  $handler = $view->new_display('block', 'Summary Block', 'block_2');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field: Content Summary */
  $handler->display->display_options['fields']['field_penton_content_summary']['id'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['table'] = 'field_data_field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['field'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['label'] = '';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_content_summary']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_content_summary']['field_api_classes'] = TRUE;
  $handler->display->display_options['block_description'] = 'Article Summary Block';

  /* Display: Publish DateTime Block */
  $handler = $view->new_display('block', 'Publish DateTime Block', 'block_3');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Published DateTime */
  $handler->display->display_options['fields']['field_penton_published_datetime']['id'] = 'field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['table'] = 'field_data_field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['field'] = 'field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['settings'] = array(
    'format_type' => 'medium_date',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_penton_published_datetime']['field_api_classes'] = TRUE;
  $handler->display->display_options['block_description'] = 'Article Publish DateTime Block';

  /* Display: Errata Block */
  $handler = $view->new_display('block', 'Errata Block', 'block_4');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Errata Date */
  $handler->display->display_options['fields']['field_penton_errata_date']['id'] = 'field_penton_errata_date';
  $handler->display->display_options['fields']['field_penton_errata_date']['table'] = 'field_data_field_penton_errata_date';
  $handler->display->display_options['fields']['field_penton_errata_date']['field'] = 'field_penton_errata_date';
  $handler->display->display_options['fields']['field_penton_errata_date']['label'] = '';
  $handler->display->display_options['fields']['field_penton_errata_date']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_errata_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_errata_date']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_errata_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_errata_date']['settings'] = array(
    'format_type' => 'medium_date',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_penton_errata_date']['field_api_classes'] = TRUE;
  /* Field: Content: Errata Note */
  $handler->display->display_options['fields']['field_penton_errata_note']['id'] = 'field_penton_errata_note';
  $handler->display->display_options['fields']['field_penton_errata_note']['table'] = 'field_data_field_penton_errata_note';
  $handler->display->display_options['fields']['field_penton_errata_note']['field'] = 'field_penton_errata_note';
  $handler->display->display_options['fields']['field_penton_errata_note']['label'] = '';
  $handler->display->display_options['fields']['field_penton_errata_note']['element_label_colon'] = FALSE;
  $handler->display->display_options['block_description'] = 'Article Errata Block';

  /* Display: Body Block */
  $handler = $view->new_display('block', 'Body Block', 'block_5');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
  $handler->display->display_options['block_description'] = 'Article Body Block';

  /* Display: Featured Program Block */
  $handler = $view->new_display('block', 'Featured Program Block', 'block_6');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_penton_link_media_feat_img_target_id']['id'] = 'field_penton_link_media_feat_img_target_id';
  $handler->display->display_options['relationships']['field_penton_link_media_feat_img_target_id']['table'] = 'field_data_field_penton_link_media_feat_img';
  $handler->display->display_options['relationships']['field_penton_link_media_feat_img_target_id']['field'] = 'field_penton_link_media_feat_img_target_id';
  $handler->display->display_options['relationships']['field_penton_link_media_feat_img_target_id']['label'] = 'field_penton_link_media_feat_img';
  $handler->display->display_options['relationships']['field_penton_link_media_feat_img_target_id']['required'] = TRUE;
  /* Relationship: Content: Program (field_penton_program) */
  $handler->display->display_options['relationships']['field_penton_program_tid']['id'] = 'field_penton_program_tid';
  $handler->display->display_options['relationships']['field_penton_program_tid']['table'] = 'field_data_field_penton_program';
  $handler->display->display_options['relationships']['field_penton_program_tid']['field'] = 'field_penton_program_tid';
  $handler->display->display_options['relationships']['field_penton_program_tid']['label'] = 'field_penton_program';
  $handler->display->display_options['relationships']['field_penton_program_tid']['required'] = TRUE;
  /* Relationship: Taxonomy term: Content using Program */
  $handler->display->display_options['relationships']['reverse_field_penton_program_node']['id'] = 'reverse_field_penton_program_node';
  $handler->display->display_options['relationships']['reverse_field_penton_program_node']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['relationships']['reverse_field_penton_program_node']['field'] = 'reverse_field_penton_program_node';
  $handler->display->display_options['relationships']['reverse_field_penton_program_node']['relationship'] = 'field_penton_program_tid';
  $handler->display->display_options['relationships']['reverse_field_penton_program_node']['label'] = 'ref_to_penton_program';
  $handler->display->display_options['relationships']['reverse_field_penton_program_node']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field: Media Image */
  $handler->display->display_options['fields']['field_penton_media_image']['id'] = 'field_penton_media_image';
  $handler->display->display_options['fields']['field_penton_media_image']['table'] = 'field_data_field_penton_media_image';
  $handler->display->display_options['fields']['field_penton_media_image']['field'] = 'field_penton_media_image';
  $handler->display->display_options['fields']['field_penton_media_image']['relationship'] = 'field_penton_link_media_feat_img_target_id';
  $handler->display->display_options['fields']['field_penton_media_image']['label'] = '';
  $handler->display->display_options['fields']['field_penton_media_image']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_media_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_media_image']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_media_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_media_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_penton_media_image']['settings'] = array(
    'image_style' => 'hp_program_standard',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_penton_media_image']['field_api_classes'] = TRUE;
  /* Field: Taxonomy term: Icon Badge (Asset Link) */
  $handler->display->display_options['fields']['field_penton_icon_badge']['id'] = 'field_penton_icon_badge';
  $handler->display->display_options['fields']['field_penton_icon_badge']['table'] = 'field_data_field_penton_icon_badge';
  $handler->display->display_options['fields']['field_penton_icon_badge']['field'] = 'field_penton_icon_badge';
  $handler->display->display_options['fields']['field_penton_icon_badge']['relationship'] = 'field_penton_program_tid';
  $handler->display->display_options['fields']['field_penton_icon_badge']['label'] = '';
  $handler->display->display_options['fields']['field_penton_icon_badge']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_icon_badge']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_penton_icon_badge']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Field: Content Summary */
  $handler->display->display_options['fields']['field_penton_content_summary_1']['id'] = 'field_penton_content_summary_1';
  $handler->display->display_options['fields']['field_penton_content_summary_1']['table'] = 'field_data_field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary_1']['field'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary_1']['relationship'] = 'field_penton_program_tid';
  $handler->display->display_options['fields']['field_penton_content_summary_1']['label'] = '';
  $handler->display->display_options['fields']['field_penton_content_summary_1']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Published DateTime */
  $handler->display->display_options['fields']['field_penton_published_datetime']['id'] = 'field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['table'] = 'field_data_field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['field'] = 'field_penton_published_datetime';
  $handler->display->display_options['fields']['field_penton_published_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_published_datetime']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_published_datetime']['settings'] = array(
    'format_type' => 'article_date_format',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  $handler->display->display_options['fields']['field_penton_published_datetime']['field_api_classes'] = TRUE;
  /* Field: Field: Content Summary */
  $handler->display->display_options['fields']['field_penton_content_summary']['id'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['table'] = 'field_data_field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['field'] = 'field_penton_content_summary';
  $handler->display->display_options['fields']['field_penton_content_summary']['label'] = '';
  $handler->display->display_options['fields']['field_penton_content_summary']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['relationship'] = 'reverse_field_penton_program_node';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'display_admin' => 'display_admin',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['block_description'] = 'Article Featured Program Block';
  $export['penton_article_node'] = $view;

  return $export;
}
