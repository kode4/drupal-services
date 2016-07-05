<?php

/**
 * @file
 * Page callbacks for the Penton taxonomy module.
 */

/**
 * Page callback for taxonomy terms.
 *
 * Make sure we use it only for the terms we need.
 *
 * @param object $term
 *   The taxonomy term.
 *
 * @return array
 *   The page content.
 */
function penton_taxonomy_term_page($term) {
  // Make sure default taxonomy functions are available.
  module_load_include('inc', 'taxonomy', 'taxonomy.pages');
  $custom_vocabularies = array(
    'program',
    'categories',
  );
  $build = array();

  if (in_array($term->vocabulary_machine_name, $custom_vocabularies)) {
    $build = penton_taxonomy_categories_term_page($term);
  }

  $categories_enabled = array();
  $entity = entity_get_info('taxonomy_term');
  $bundles = (empty($entity['bundles'])) ? array() : $entity['bundles'];

  foreach ($bundles as $entity_type => $entity_info) {
    if (variable_get('metatag_enable_taxonomy_term__' . $entity_type, FALSE)) {
      $categories_enabled[] = $entity_type;
    }
  }

  if (in_array($term->vocabulary_machine_name, $categories_enabled)) {
    $default_metatags_lists = metatag_config_load_with_defaults('taxonomy_term');
    $output = array();

    if (!empty($term->metatags[LANGUAGE_NONE])) {
      $default_metatags_lists = array_merge($default_metatags_lists, $term->metatags[LANGUAGE_NONE]);
    }

    foreach ($default_metatags_lists as $name => $value) {
      $metatag_instance = metatag_get_instance($name, $value);
      $output[$name] = $metatag_instance->getElement(array(
        'entity' => $term,
        'entity_type' => 'taxonomy_term',
        'view_mode' => 'full',
        'token data' => array('term' => $term),
        'instance' => 'taxonomy_term',
      ));
    }

    metatag_page_set_metatags('taxonomy_term', $output);
  }

  if ($term->vocabulary_machine_name == 'program' && ($colors = field_get_items('taxonomy_term', $term, 'field_penton_background_colour'))) {
    $color = $colors[0]['value'];
    $color_styles = "
      .program-term-page .main-area-header, .program-term-page .r-a-header {
        border-bottom-color: $color !important;
        color: $color !important;
      }
      .program-term-page .category-header {
        border-top-color: $color !important;
      }
      .program-term-page .category-header .category-header__head {
        color: $color !important;
      }";
    drupal_add_css($color_styles, 'inline');
  }

  $type = 'taxonomy_term';
  drupal_alter(array('taxonomy_term_view', 'entity_view'), $build, $type);

  // Call context condition.
  $plugin = context_get_plugin('condition', 'taxonomy_term');
  $plugin->execute($term, 'view');

  return $build;
}

/**
 * Displays all nodes associated with a term.
 *
 * @param object $term
 *   The taxonomy term.
 *
 * @return array
 *   The page content.
 */
function penton_taxonomy_categories_term_page($term) {
  drupal_set_title($term->name);

  // Build breadcrumb based on the hierarchy of the term.
  $current = (object) array(
    'tid' => $term->tid,
  );
  $breadcrumb = array();
  // Check if current category is oot.
  $top_level_category = empty(taxonomy_get_parents($current->tid));
  while ($parents = taxonomy_get_parents($current->tid)) {
    $current = array_shift($parents);
    $breadcrumb[] = l($current->name, 'taxonomy/term/' . $current->tid);
  }

  $breadcrumb[] = l(t('Home'), NULL);
  $breadcrumb = array_reverse($breadcrumb);
  drupal_set_breadcrumb($breadcrumb);
  drupal_add_feed('taxonomy/term/' . $term->tid . '/feed', 'RSS - ' . $term->name);

  // Set the term path as the canonical URL to prevent duplicate content.
  $uri = entity_uri('taxonomy_term', $term);
  drupal_add_html_head_link(
    array(
      'rel' => 'canonical',
      'href' => url($uri['path'], $uri['options']),
    ),
    TRUE);
  // Set the non-aliased path as a default shortlink.
  drupal_add_html_head_link(
    array(
      'rel' => 'shortlink',
      'href' => url($uri['path'], array_merge($uri['options'], array('alias' => TRUE))),
    ),
    TRUE);

  // Get category node IDs.
  $tids = [$term];
  if ($top_level_category) {
    // Get parent+child category nids.
    $child_category_tids = (array) taxonomy_get_children($current->tid);
    $tids = array_merge($tids, $child_category_tids);
  }

  $pinned_nids = array();
  $pinned_nids_assoc = _penton_taxonomy_category_articles($tids, TRUE);
  uasort($pinned_nids_assoc, 'sort_nids');
  foreach ($pinned_nids_assoc as $pinned_nids_assoc_item) {
    $pinned_nids[] = $pinned_nids_assoc_item;
  }

  $nids = array();
  $nids_assoc = _penton_taxonomy_category_articles($tids);
  uasort($nids_assoc, 'sort_nids');
  foreach ($nids_assoc as $nid_item) {
    if (!empty($nid_item->nid)) {
      $nids[] = $nid_item->nid;
    }
  }

  if (!empty($pinned_nids)) {
    $nids = array_merge($pinned_nids, $nids);
  }

  if (!empty($nids)) {
    $nodes = node_load_multiple($nids);
    $build = array(
      'nodes' => array(),
    );
    $params = drupal_get_query_parameters();
    // If ajax request.
    if (is_ajax() || isset($params['page']) && is_numeric($params['page'])) {
      foreach ($nodes as &$node) {
        $node->featured_image_style = 'tax_thumbs_standard';
        $node->trim_summary = 250;
      }
      $build_nodes = node_view_multiple($nodes);
      $build['nodes'] += $build_nodes['nodes'];
      $build['wrapper_start'] = array(
        '#markup' => '<div class="js-lazy-pager-content"><div class="dfp-ad-hideempty category-banner"><div class="penton-dfp-ads" data-dfp-position="infinitescroll"></div></div>',
        '#weight' => -100,
      );
      $build['wrapper_end'] = array(
        '#markup' => '</div>',
        '#weight' => 100,
      );
    }
    else {
      $build['wrapper_start'] = array(
        '#markup' => '<div class="js-lazy-pager-wrapper">',
        '#weight' => -100,
      );
      $build['wrapper_end'] = array(
        '#markup' => '</div>',
        '#weight' => 100,
      );

      if (!empty($nodes)) {
        $node1 = reset($nodes);
        $node1->article_classes = array('tax-page-teasers__top-main', 'article-teaser__overlayed');
        $node1->featured_image_style = 'tax_top_story_main_standard';
        $node1->trim_summary = 140;

        $nodes23 = array_slice($nodes, 1, 2, TRUE);
        foreach ($nodes23 as &$node) {
          $node->featured_image_style = 'tax_top_stories_2_3_standard';
          $node->article_classes = array('tax-page-teasers__top-sub');
          $node->trim_summary = 115;
        }
        $nodes13 = array($node1->nid => $node1) + $nodes23;
        $build13 = node_view_multiple($nodes13);
        drupal_add_region_content('main_col_first',
          '<div class="main-area-header">' . t('Highlights') . '</div>' .
          render($build13)
        );
      }
      if (count($nodes) > 3) {
        $nodes47 = array_slice($nodes, 3, 4, TRUE);
        foreach ($nodes47 as &$node) {
          $node->featured_image_style = 'tax_thumbs_standard';
          $node->trim_summary = 250;
        }
        $build47 = node_view_multiple($nodes47);
        $build['nodes'] += $build47['nodes'];
        if (count($nodes) > 7) {
          $nodes811 = array_slice($nodes, 7, 3, TRUE);
          foreach ($nodes811 as &$node) {
            $node->featured_image_style = 'tax_three_stories_standard';
            $node->trim_summary = 130;
            $node->article_classes = array('tax-page-teasers__in-three-row', 'article-teaser__overlayed');
          }
          $build811 = node_view_multiple($nodes811);
          $build['nodes'][] = array(
            '#markup' => '<div class="teasers__three-row"><div class="teasers__three-row__inner">',
          );
          $build['nodes'] = array_merge($build['nodes'], $build811['nodes']);
          $build['nodes'][] = array(
            '#markup' => '</div></div>',
          );
        }
        if (count($nodes) > 10) {
          $nodes10p = array_slice($nodes, 10, NULL, TRUE);
          foreach ($nodes10p as &$node) {
            $node->featured_image_style = 'tax_thumbs_standard';
            $node->trim_summary = 250;
          }
          $build10p = node_view_multiple($nodes10p);
          $build['nodes'] += $build10p['nodes'];
        }
      }
    }
    $build['nodes']['pager'] = array(
      '#theme' => 'pager',
      '#weight' => 5,
      '#lazy' => TRUE,
    );
  }
  else {
    $build['no_content'] = array(
      '#prefix' => '<p>',
      '#markup' => t('There is currently no content classified with this term.'),
      '#suffix' => '</p>',
    );
  }

  return $build;
}

/**
 * List of pinned and associated Articles.
 *
 * @return array
 *   returns array of node objects.
 */
function _penton_taxonomy_category_articles($terms, $pinned_elements_only = FALSE) {
  $tids = array();
  foreach ($terms as $term) {
    $tids[] = $term->tid;
  }

  $count_query = db_select('taxonomy_index', 't');
  $count_query->join('field_data_field_penton_published_datetime', 'f', 'f.entity_id = t.nid');
  $count_query->addTag('node_access');
  $count_query->condition('t.tid', $tids, 'IN');
  $count_query->addExpression('COUNT(t.nid)');
  $total = $count_query->execute()->fetchField();
  $page = pager_default_initialize($total - 3, 10);
  $offset = 10 * $page;
  $count = 10;

  $pinned_all = array();
  if (!empty($terms[0]->field_penton_pinned_elements[LANGUAGE_NONE])) {
    foreach ($terms[0]->field_penton_pinned_elements[LANGUAGE_NONE] as $pin) {
      $pinned_all[] = $pin['target_id'];
    }
  }

  $count = ($page == 0) ? $count + 3 : $count;
  $offset = ($page == 0) ? $offset : $offset + 3;
  $pinned_already = array_slice($pinned_all, 0, $offset);
  $pinned_to_page = array_slice($pinned_all, $offset, $count);
  $articles_query = db_select('taxonomy_index', 't');
  $articles_query->leftJoin('field_data_field_penton_published_datetime', 'f', 'f.entity_id = t.nid');
  $articles_query->leftJoin('field_data_field_penton_promote_on_site', 'p', 'p.entity_id = t.nid');
  $articles_query->join('node', 'n', 'n.nid = t.nid');
  $articles_query->addTag('node_access');
  $articles_query->condition('t.tid', $tids, 'IN');
  $articles_query->condition('p.field_penton_promote_on_site_value', '1');
  $articles_query->addField('t', 'nid');
  $articles_query->addField('f', 'field_penton_published_datetime_value');
  if (!empty($pinned_all)) {
    $articles_query->condition('t.nid', $pinned_all, 'NOT IN');
  };
  $articles_query->range($offset - count($pinned_already), $count - count($pinned_to_page))
    ->orderBy('f.field_penton_published_datetime_value', "DESC")
    ->orderBy('n.changed', "DESC");
  $articles_nids = $articles_query->execute()
    ->fetchAll();

  if ($pinned_elements_only) {
    return $pinned_to_page;
  }
  return array_merge($pinned_to_page, $articles_nids);
}

/**
 * Category information render array.
 *
 * @return array
 *   returns a renderable array of block content.
 */
function penton_taxonomy_term_info($term) {

  if ($term->vocabulary_machine_name == 'categories') {
    // Block output in HTML with div wrapper.
    $block = array(
      '#prefix' => '<section class="category-header">',
      '#suffix' => '</section>',
      'header' => array(
        '#prefix' => '<div class="category-header__inner">',
        '#suffix' => '</div>',
      ),
    );

    $parent = FALSE;
    $parents = taxonomy_get_parents($term->tid);
    if (!empty($parents)) {
      $parent = array_pop($parents);
      $block['header']['parent_category'] = array(
        '#type' => 'link',
        '#title' => '<i class="fa fa-chevron-left"></i> ' . $parent->name,
        '#href' => drupal_get_path_alias('taxonomy/term/' . $parent->tid),
        '#options' => array(
          'html' => TRUE,
          'attributes' => array('class' => array('prev-acticle')),
        ),
      );
    };

    $block['header']['category_title'] = array(
      '#prefix' => '<h1 class="category-header__head">',
      '#suffix' => '</h1>',
      'title' => array(
        '#markup' => $term->name,
      ),
    );

    $block['header']['category_logo'] = array(
      '#markup' => '<div class="category-logo dfp-ad-hideempty hidden"><div class="category-logo-before-text">BROUGHT TO YOU BY</div><div data-dfp-position="sponsored_logo"></div></div>',
    );

    if (!empty($term->field_penton_content_summary[LANGUAGE_NONE][0]['value'])) {
      $block['header']['category_slogan'] = array(
        '#prefix' => '<h4 class="category-header__slogan">',
        '#suffix' => '</h4>',
        'slogan' => array(
          '#markup' => $term->field_penton_content_summary[LANGUAGE_NONE][0]['value'],
        ),
      );
    };

    $tid_for_children = $parent ? $parent->tid : $term->tid;
    if (!empty($children = taxonomy_get_children($tid_for_children))) {
      if (!empty($children[$term->tid])) {
        unset($children[$term->tid]);
        $children = array($term->tid => $term) + $children;
      }
      $items = array();
      $subitems = array();
      $i = 0;
      foreach ($children as $key => $child) {
        $i++;
        $item_classes = array('category-menu-link');
        if ($term->tid == $child->tid) {
          $item_classes[] = 'active';
        }
        $item = array(
          'data' => l(
              '<span class="js-menumore-item-text">' . $child->name . '</span>',
              drupal_get_path_alias('taxonomy/term/' . $child->tid),
              array(
                'attributes' => array('class' => $item_classes),
                'html' => TRUE,
              )
          ),
          'id' => 'taxonomy-' . $key,
          'class' => array('category-menu-list__item'),
        );
        // If >8 add to "More".
        if ($i <= 8) {
          $items[] = $item;
        }
        else {
          $subitems[] = $item;
        }
      };
      if (!empty($subitems)) {
        $submenu = array(
          '#theme' => 'item_list',
          '#items' => $subitems,
          '#attributes' => array('class' => array('category-list-submenu', 'js-menumore-sub')),
        );
        $items[] = array(
          'data' => '<a href="#" class="category-menu-link">More<i class="fa fa-chevron-down"></i></a>' . drupal_render($submenu),
          'class' => array('category-menu-list__item', 'js-menumore-more-item'),
        );
      };
      $block['category_menu'] = array(
        '#theme' => 'item_list',
        '#items' => $items,
        '#attributes' => array(
          'class' => array(
            'category-menu-list',
            'js-toggle-menu',
            'js-menumore',
          ),
        ),
        '#prefix' => '<div class="category-menu js-menu-toggler"><a href="#" class="drop-cat-menu js-menu-toggler-link"><i class="fa fa-bars"></i>Subcategories</a>',
        '#suffix' => '</div>',
      );
    };

    return $block;
  }
  elseif ($term->vocabulary_machine_name == 'program') {
    $header_content = $term->name;

    $term_meta = entity_metadata_wrapper('taxonomy_term', $term);
    if (!empty($term_meta->value()->field_penton_media_image)) {
      $media_image = $term_meta->field_penton_media_image->value();
      if (!empty($media_image)) {
        $image_url = file_create_url($media_image['uri']);
        $header_content = theme_image(array(
          'path' => $image_url,
          'attributes' => array('width' => 320, 'height' => 100),
        ));
      }
    }

    return array(
      "#markup" => '<section class="category-header"><div class="category-header__inner"><h1 class="category-header__head">' . $header_content . '</h1>' .
      '<div class="category-logo dfp-ad-hideempty hidden"><div class="category-logo-before-text">BROUGHT TO YOU BY</div><div data-dfp-position="sponsored_logo"></div></div>' .
      '<h4 class="category-header__slogan">' . (!empty($term->field_penton_content_summary[LANGUAGE_NONE][0]['value']) ? $term->field_penton_content_summary[LANGUAGE_NONE][0]['value'] : '') . '</h4></div></section>',
    );
  }
}

/**
 * Sort array.
 */
function sort_nids($a, $b) {
  return strtotime($a->field_penton_published_datetime_value) < strtotime($b->field_penton_published_datetime_value) ? 1 : -1;
};
