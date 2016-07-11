<?php

function _custom_file_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
  $file_select = db_select('file_managed', 't');

  custom_services_resource_build_index_query($file_select, $page, $fields, $parameters, $page_size, 'file', $options);

  $results = services_resource_execute_index_query($file_select);

  // Put together array of matching files to return.
  return custom_services_resource_build_index_list($results, 'file', 'fid');
}