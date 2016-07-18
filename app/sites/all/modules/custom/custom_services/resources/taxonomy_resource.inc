<?php
function _custom_taxonomy_term_resource_index($page, $fields, $parameters, $page_size, $options = array()) {
    $taxonomy_select = db_select('taxonomy_term_data', 't');
    $taxonomy_select->join('taxonomy_term_hierarchy', 'tth', 't.tid = tth.tid');
    $taxonomy_select->fields('tth');
    $taxonomy_select->innerjoin('taxonomy_vocabulary', 'tv', 'tv.vid = t.vid');
    
    $taxonomy_select = custom_services_get_parameter($taxonomy_select,'taxonomy_term');
    custom_services_resource_build_index_query($taxonomy_select, $page, $fields, $parameters, $page_size, 'taxonomy_term', $options);

    $results = services_resource_execute_index_query($taxonomy_select);

    return custom_services_resource_build_index_list($results, 'taxonomy_term', 'tid');
}
function _custom_taxonomy_parent($tid) {
    $taxonomy_parent = db_select('taxonomy_term_hierarchy', 't');
    $taxonomy_parent->condition('t.tid',$tid, "=");
    $taxonomy_parent->fields('t');
    $results = services_resource_execute_index_query($taxonomy_parent);
    foreach ($results as $result) {
        return $result;
    }
}