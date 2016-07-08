<?php
function _custom_node_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
  $node_select = db_select('node', 't')
      ->addTag('node_access');
  $node_select = custom_services_get_parameter($node_select);
  custom_services_resource_build_index_query($node_select, $page, $fields, $parameters, $page_size, 'node', $options);

  if (!user_access('administer nodes')) {
    $node_select->condition('status', 1);
  }

  $results = services_resource_execute_index_query($node_select);

  return custom_services_resource_build_index_list($results, 'node', 'nid');
}