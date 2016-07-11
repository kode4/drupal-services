<?php

function _custom_comment_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
  $comment_select = db_select('comment', 't');

  custom_services_resource_build_index_query($comment_select, $page, $fields, $parameters, $page_size, 'comment', $options);

  if (!user_access('administer comments')) {
    $comment_select->condition('status', COMMENT_PUBLISHED);
  }

  $results = services_resource_execute_index_query($comment_select);

  return custom_services_resource_build_index_list($results, 'comment', 'cid');
}