<?php
function _custom_user_resource_index($page, $fields, $parameters, $page_size, $options = array())
{
    $user_select = db_select('users', 't');
    $user_select->innerjoin('users_roles', 'ur', 't.uid = ur.uid');
    $user_select->innerjoin('role', 'r', 'ur.rid = r.rid');
    $user_select = custom_services_get_parameter($user_select);
    custom_services_resource_build_index_query($user_select, $page, $fields, $parameters, $page_size, 'user', $options);

    $results = services_resource_execute_index_query($user_select);

    return custom_services_resource_build_index_list($results, 'user', 'uid');
}