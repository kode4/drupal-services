<?php
/**
 * @file
 * penton_store.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function penton_store_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-info_block'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'info_block',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => 'ecommerce_sidebar',
        'status' => 1,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_sidebar',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-73ab767b05d2f0ef23614b105d540eba'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '73ab767b05d2f0ef23614b105d540eba',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-89ec5e0b013520e0dcd1ec8a5bb0b443'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '89ec5e0b013520e0dcd1ec8a5bb0b443',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-browse_by_product_type-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'browse_by_product_type-block',
    'module' => 'views',
    'node_types' => array(
      0 => 'store_front',
    ),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => 'ecommerce_sidebar',
        'status' => 1,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_sidebar',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-browse_by_topic_view-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'browse_by_topic_view-block',
    'module' => 'views',
    'node_types' => array(
      0 => 'store_front',
    ),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => 'ecommerce_sidebar',
        'status' => 1,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_sidebar',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-d1f3e09ec20a2d47c45fd4f95daa7ef3'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'd1f3e09ec20a2d47c45fd4f95daa7ef3',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'topics/*
product_types/*',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-fb77691359bedfc8fc2ef0f31c905e92'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'fb77691359bedfc8fc2ef0f31c905e92',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-featured_topics_view-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'featured_topics_view-block',
    'module' => 'views',
    'node_types' => array(
      0 => 'store_front',
    ),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-featured_topics_view-block_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'featured_topics_view-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-featured_topics_view-block_2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'featured_topics_view-block_2',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-related_products-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'related_products-block',
    'module' => 'views',
    'node_types' => array(
      0 => 'product',
    ),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'penton_core_theme' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_core_theme',
        'weight' => 0,
      ),
      'penton_subtheme_waste360' => array(
        'region' => 'ecommerce_content',
        'status' => 1,
        'theme' => 'penton_subtheme_waste360',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
