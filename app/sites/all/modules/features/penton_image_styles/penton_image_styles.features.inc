<?php
/**
 * @file
 * penton_image_styles.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function penton_image_styles_image_default_styles() {
  $styles = array();

  // Exported image style: article_featured_retina.
  $styles['article_featured_retina'] = array(
    'label' => 'article_featured_retina',
    'effects' => array(
      31 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1540,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      32 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1540,
          'height' => 800,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: article_featured_standard.
  $styles['article_featured_standard'] = array(
    'label' => 'article_featured_standard',
    'effects' => array(
      33 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 770,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      34 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 770,
          'height' => 400,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: article_featured_wide.
  $styles['article_featured_wide'] = array(
    'label' => 'article_featured_wide',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 400,
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: article_featured_wide_retina.
  $styles['article_featured_wide_retina'] = array(
    'label' => 'article_featured_wide_retina',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 2400,
          'height' => 800,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: article_related_thumb_retina.
  $styles['article_related_thumb_retina'] = array(
    'label' => 'article_related_thumb_retina',
    'effects' => array(
      35 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 180,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      36 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 180,
          'height' => 166,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: article_related_thumb_standard.
  $styles['article_related_thumb_standard'] = array(
    'label' => 'article_related_thumb_standard',
    'effects' => array(
      37 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 90,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      38 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 90,
          'height' => 83,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: gal_landscape_main_1_retina.
  $styles['gal_landscape_main_1_retina'] = array(
    'label' => 'gal_landscape_main_1_retina',
    'effects' => array(
      55 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 2000,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      56 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 2000,
          'height' => 1040,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: gal_landscape_main_1_standard.
  $styles['gal_landscape_main_1_standard'] = array(
    'label' => 'gal_landscape_main_1_standard',
    'effects' => array(
      57 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1000,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      58 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1000,
          'height' => 520,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: gal_thumbs_retina.
  $styles['gal_thumbs_retina'] = array(
    'label' => 'gal_thumbs_retina',
    'effects' => array(
      59 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 300,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      60 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 300,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: gal_thumbs_standard.
  $styles['gal_thumbs_standard'] = array(
    'label' => 'gal_thumbs_standard',
    'effects' => array(
      61 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 150,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      62 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 150,
          'height' => 150,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_categories_1_2_main_retina.
  $styles['hp_categories_1_2_main_retina'] = array(
    'label' => 'hp_categories_1_2_main_retina',
    'effects' => array(
      11 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 750,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      12 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 750,
          'height' => 390,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_categories_1_2_main_standard.
  $styles['hp_categories_1_2_main_standard'] = array(
    'label' => 'hp_categories_1_2_main_standard',
    'effects' => array(
      13 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 375,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      14 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 375,
          'height' => 195,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_categories_3_main_retina.
  $styles['hp_categories_3_main_retina'] = array(
    'label' => 'hp_categories_3_main_retina',
    'effects' => array(
      15 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      16 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 466,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_categories_3_main_standard.
  $styles['hp_categories_3_main_standard'] = array(
    'label' => 'hp_categories_3_main_standard',
    'effects' => array(
      17 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 450,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      18 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 233,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_categories_secondary_thumb_retina.
  $styles['hp_categories_secondary_thumb_retina'] = array(
    'label' => 'hp_categories_secondary_thumb_retina',
    'effects' => array(
      19 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 176,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      20 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 176,
          'height' => 116,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_categories_secondary_thumb_standard.
  $styles['hp_categories_secondary_thumb_standard'] = array(
    'label' => 'hp_categories_secondary_thumb_standard',
    'effects' => array(
      21 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 88,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      22 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 88,
          'height' => 58,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_featured_media_retina.
  $styles['hp_featured_media_retina'] = array(
    'label' => 'hp_featured_media_retina',
    'effects' => array(
      27 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1620,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      28 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1620,
          'height' => 842,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_featured_media_standard.
  $styles['hp_featured_media_standard'] = array(
    'label' => 'hp_featured_media_standard',
    'effects' => array(
      29 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 810,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      30 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 810,
          'height' => 421,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_program_retina.
  $styles['hp_program_retina'] = array(
    'label' => 'hp_program_retina',
    'effects' => array(
      23 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 750,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      24 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 750,
          'height' => 390,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_program_standard.
  $styles['hp_program_standard'] = array(
    'label' => 'hp_program_standard',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 375,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 375,
          'height' => 195,
        ),
        'weight' => 2,
      ),
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 375,
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: hp_top_stories_main_retina.
  $styles['hp_top_stories_main_retina'] = array(
    'label' => 'hp_top_stories_main_retina',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1130,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => -10,
      ),
      4 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1130,
          'height' => 584,
        ),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: hp_top_stories_main_standard.
  $styles['hp_top_stories_main_standard'] = array(
    'label' => 'hp_top_stories_main_standard',
    'effects' => array(
      9 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 565,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      10 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 565,
          'height' => 292,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_top_stories_secondary_retina.
  $styles['hp_top_stories_secondary_retina'] = array(
    'label' => 'hp_top_stories_secondary_retina',
    'effects' => array(
      5 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 526,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      6 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 526,
          'height' => 272,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: hp_top_stories_secondary_standard.
  $styles['hp_top_stories_secondary_standard'] = array(
    'label' => 'hp_top_stories_secondary_standard',
    'effects' => array(
      7 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 263,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      8 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 263,
          'height' => 136,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_hp_user_marketing_retina.
  $styles['non_feat_hp_user_marketing_retina'] = array(
    'label' => 'non_feat_hp_user_marketing_retina',
    'effects' => array(
      63 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 306,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      64 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 306,
          'height' => 280,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_hp_user_marketing_standard.
  $styles['non_feat_hp_user_marketing_standard'] = array(
    'label' => 'non_feat_hp_user_marketing_standard',
    'effects' => array(
      65 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 153,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: non_feat_tax_user_marketing_retina.
  $styles['non_feat_tax_user_marketing_retina'] = array(
    'label' => 'non_feat_tax_user_marketing_retina',
    'effects' => array(
      67 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 470,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      68 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 470,
          'height' => 310,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_tax_user_marketing_standard.
  $styles['non_feat_tax_user_marketing_standard'] = array(
    'label' => 'non_feat_tax_user_marketing_standard',
    'effects' => array(
      69 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 235,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: non_feat_user_comment_retina.
  $styles['non_feat_user_comment_retina'] = array(
    'label' => 'non_feat_user_comment_retina',
    'effects' => array(
      75 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 110,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      76 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 110,
          'height' => 110,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_user_comment_standard.
  $styles['non_feat_user_comment_standard'] = array(
    'label' => 'non_feat_user_comment_standard',
    'effects' => array(
      77 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 55,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      78 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 55,
          'height' => 55,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_user_profile_retina.
  $styles['non_feat_user_profile_retina'] = array(
    'label' => 'non_feat_user_profile_retina',
    'effects' => array(
      71 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 374,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      72 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 374,
          'height' => 374,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: non_feat_user_profile_standard.
  $styles['non_feat_user_profile_standard'] = array(
    'label' => 'non_feat_user_profile_standard',
    'effects' => array(
      73 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 187,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      74 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 187,
          'height' => 187,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: search_results_retina.
  $styles['search_results_retina'] = array(
    'label' => 'search_results_retina',
    'effects' => array(
      79 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 176,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      80 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 176,
          'height' => 116,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: search_results_standard.
  $styles['search_results_standard'] = array(
    'label' => 'search_results_standard',
    'effects' => array(
      81 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 88,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      82 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 88,
          'height' => 58,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_three_stories_retina.
  $styles['tax_three_stories_retina'] = array(
    'label' => 'tax_three_stories_retina',
    'effects' => array(
      51 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 480,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      52 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 480,
          'height' => 250,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_three_stories_standard.
  $styles['tax_three_stories_standard'] = array(
    'label' => 'tax_three_stories_standard',
    'effects' => array(
      53 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 240,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      54 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 240,
          'height' => 125,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_thumbs_retina.
  $styles['tax_thumbs_retina'] = array(
    'label' => 'tax_thumbs_retina',
    'effects' => array(
      47 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 176,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      48 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 176,
          'height' => 116,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_thumbs_standard.
  $styles['tax_thumbs_standard'] = array(
    'label' => 'tax_thumbs_standard',
    'effects' => array(
      49 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 88,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      50 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 88,
          'height' => 58,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_top_stories_2_3_retina.
  $styles['tax_top_stories_2_3_retina'] = array(
    'label' => 'tax_top_stories_2_3_retina',
    'effects' => array(
      43 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 240,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      44 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 240,
          'height' => 158,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_top_stories_2_3_standard.
  $styles['tax_top_stories_2_3_standard'] = array(
    'label' => 'tax_top_stories_2_3_standard',
    'effects' => array(
      45 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 120,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      46 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 120,
          'height' => 79,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_top_story_main_retina.
  $styles['tax_top_story_main_retina'] = array(
    'label' => 'tax_top_story_main_retina',
    'effects' => array(
      39 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      40 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 900,
          'height' => 466,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: tax_top_story_main_standard.
  $styles['tax_top_story_main_standard'] = array(
    'label' => 'tax_top_story_main_standard',
    'effects' => array(
      41 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 450,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      42 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 233,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}
