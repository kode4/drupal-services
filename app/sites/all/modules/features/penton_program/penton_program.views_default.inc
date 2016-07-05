<?php
/**
 * @file
 * penton_program.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function penton_program_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'penton_program_term';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Penton Program Term';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '<none>';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Icon Badge (Asset Link) */
  $handler->display->display_options['fields']['field_penton_icon_badge']['id'] = 'field_penton_icon_badge';
  $handler->display->display_options['fields']['field_penton_icon_badge']['table'] = 'field_data_field_penton_icon_badge';
  $handler->display->display_options['fields']['field_penton_icon_badge']['field'] = 'field_penton_icon_badge';
  $handler->display->display_options['fields']['field_penton_icon_badge']['label'] = '';
  $handler->display->display_options['fields']['field_penton_icon_badge']['element_type'] = '0';
  $handler->display->display_options['fields']['field_penton_icon_badge']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_penton_icon_badge']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_penton_icon_badge']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_penton_icon_badge']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_penton_icon_badge']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_penton_icon_badge']['field_api_classes'] = TRUE;
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
  /* Contextual filter: Taxonomy term: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'program' => 'program',
  );

  /* Display: Program Logo / Summary Block */
  $handler = $view->new_display('block', 'Program Logo / Summary Block', 'block_1');
  $handler->display->display_options['block_description'] = 'Program Logo / Summary Block';
  $export['penton_program_term'] = $view;

  return $export;
}
