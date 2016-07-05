<?php
/**
 * @file
 * penton_dfp.default_dfp_tags.inc
 */

/**
 * Implements hook_default_dfp_tag().
 */
function penton_dfp_default_dfp_tag() {
  $export = array();

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_300_x_lft';
  $tag->slot = '[article] Left rail 300_x_lft';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'left_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_lft',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '779x0',
        'ad_sizes' => '300x250',
      ),
    ),
  );
  $export['article_300_x_lft'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_300_x_rht_jumbotron';
  $tag->slot = '[article] Rectangle Inline and Jumbotron';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '300x250,300x600';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'jumbotron',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_rht',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '300x250',
      ),
      1 => array(
        'browser_size' => '639x0',
        'ad_sizes' => '300x250,300x600',
      ),
    ),
  );
  $export['article_300_x_rht_jumbotron'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_728_1_a';
  $tag->slot = '[article] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
      7 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['article_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_728_footer';
  $tag->slot = '[article] Leaderboard 728_10_a';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'bottom_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_10_a',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['article_728_footer'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_canopy';
  $tag->slot = '[article] Canopy';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'adhesion',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['article_canopy'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_footnote_floor';
  $tag->slot = '[article] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['article_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_in_article_video_ad';
  $tag->slot = '[article] In-Article Video Ad';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'inarticlevideo_1_a',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['article_in_article_video_ad'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_interscroller_728_x_a';
  $tag->slot = '[article] Interscroller/Leaderboard 2';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'infinitescroll',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a,interscroller',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
      7 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['article_interscroller_728_x_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_interstitial';
  $tag->slot = '[article] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['article_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_oop';
  $tag->slot = '[article] Out of Page';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '0x0';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 1,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'oop_a',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['article_oop'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_pagewrap';
  $tag->slot = '[article] PageWrap';
  $tag->adunit = '[dfp_tag:site_id]/article/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 1,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'wrap',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      3 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
      4 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      5 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      6 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
      7 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['article_pagewrap'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'article_sponsored_logo';
  $tag->slot = '[article] Sponsored Logo';
  $tag->adunit = '';
  $tag->size = '160x65,125x125,90x90';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'article',
    'position' => 'sponsored_logo',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'sponsoredlogo',
      ),
      1 => array(
        'target' => 'program',
        'value' => '[node:field_penton_program]',
      ),
      2 => array(
        'target' => 'pterm',
        'value' => '[node:field_penton_primary_category]',
      ),
      3 => array(
        'target' => 'sterm',
        'value' => '[node:field_penton_secondary_category]',
      ),
      4 => array(
        'target' => 'author',
        'value' => '[node:field_penton_author]',
      ),
      5 => array(
        'target' => 'ptype',
        'value' => '[node:field_penton_article_type]',
      ),
      6 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['article_sponsored_logo'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_728_1_a';
  $tag->slot = '[author] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
      3 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['author_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_footnote_floor';
  $tag->slot = '[author] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['author_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_interstitial';
  $tag->slot = '[author] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['author_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_300_x_lft';
  $tag->slot = '[author] Left rail 300_x_lft';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'left_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_lft',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '779x0',
        'ad_sizes' => '300x250',
      ),
    ),
  );
  $export['author_300_x_lft'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_300_2_rht_jumbotron';
  $tag->slot = '[author] Rectangle Inline and Jumbotron';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '300x250,300x600';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'jumbotron',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_rht',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '300x250',
      ),
      1 => array(
        'browser_size' => '639x0',
        'ad_sizes' => '300x250,300x600',
      ),
    ),
  );
  $export['author_300_2_rht_jumbotron'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_interscroller_728_x_a';
  $tag->slot = '[author] Interscroller/Leaderboard 2';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'infinitescroll',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_2_a,interscroller',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['author_interscroller_728_x_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'author_728_footer';
  $tag->slot = '[author] Leaderboard 728_10_a';
  $tag->adunit = '[dfp_tag:site_id]/author';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'author',
    'position' => 'bottom_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_10_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'author',
      ),
      2 => array(
        'target' => 'author',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['author_728_footer'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'gallery_300_2_rht';
  $tag->slot = '[gallery] Right Ad';
  $tag->adunit = '[dfp_tag:site_id]/gallery/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'gallery',
    'position' => 'right_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'gallery_300_right',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'gallery',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['gallery_300_2_rht'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'gallery_728_1_a';
  $tag->slot = '[gallery] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/gallery/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'gallery',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'gallery_728_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'gallery',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['gallery_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'gallery_interstitial';
  $tag->slot = '[gallery] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/gallery/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '300x250,470x440';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'gallery',
    'position' => 'interstitial',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'gallery_interstitial',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'gallery',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['gallery_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'gallery_interstitial_a';
  $tag->slot = '[gallery] Interstitial a';
  $tag->adunit = '[dfp_tag:site_id]/gallery/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'gallery',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'gallery',
      ),
      2 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['gallery_interstitial_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'gallery_footnote_floor';
  $tag->slot = '[gallery] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/gallery/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'gallery',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'gallery',
      ),
      2 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['gallery_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'gallery_sponsored_logo';
  $tag->slot = '[gallery] Sponsored Logo';
  $tag->adunit = '[dfp_tag:site_id]/gallery/[node:field_penton_primary_category:parents:join:/]';
  $tag->size = '160x65,125x125,90x90';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'gallery',
    'position' => 'sponsored_logo',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'sponsoredlogo',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'gallery',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['gallery_sponsored_logo'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_300_1_lft';
  $tag->slot = '[homepage] Left rail 300_1_lft';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'left_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_lft',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '779x0',
        'ad_sizes' => '300x250',
      ),
    ),
  );
  $export['homepage_300_1_lft'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_300_2_rht_jumbotron_mobile';
  $tag->slot = '[homepage] Rectangle and Jumbotron mobile';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'right_col_jumbotron',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_rht',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '300x250',
      ),
      1 => array(
        'browser_size' => '639x0',
        'ad_sizes' => 'x',
      ),
    ),
  );
  $export['homepage_300_2_rht_jumbotron_mobile'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_300_2_rht_jumbotron';
  $tag->slot = '[homepage] Rectangle and Jumbotron';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '300x250,300x600';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'third_cat_jumbotron',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_rht',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '0x0',
        'ad_sizes' => 'x',
      ),
      1 => array(
        'browser_size' => '639x0',
        'ad_sizes' => '300x250,300x600',
      ),
    ),
  );
  $export['homepage_300_2_rht_jumbotron'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_728_1_a';
  $tag->slot = '[homepage] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
      2 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['homepage_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_728_2_a';
  $tag->slot = '[homepage] Leaderboard 728_2_a';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '728x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'bottom_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_2_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      1 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['homepage_728_2_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_canopy';
  $tag->slot = '[homepage] Canopy';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'adhesion',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['homepage_canopy'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_footnote_floor';
  $tag->slot = '[homepage] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['homepage_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_interstitial';
  $tag->slot = '[homepage] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['homepage_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_oop';
  $tag->slot = '[homepage] Out of Page';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '0x0';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 1,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'oop_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['homepage_oop'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_pagewrap';
  $tag->slot = '[homepage] PageWrap';
  $tag->adunit = '[dfp_tag:site_id]/homepage';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 1,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'wrap',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
      2 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['homepage_pagewrap'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'homepage_sponsored_logo';
  $tag->slot = '[homepage] Sponsored Logo';
  $tag->adunit = '';
  $tag->size = '160x65,125x125,90x90';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'homepage',
    'position' => 'sponsored_logo',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'sponsoredlogo',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'homepage',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['homepage_sponsored_logo'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'page_728_1_a';
  $tag->slot = '[page] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/page';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'page',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'page',
      ),
      2 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['page_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'page_footnote_floor';
  $tag->slot = '[page] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/page';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'page',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['page_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'page_interstitial';
  $tag->slot = '[page] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/page';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'page',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'page',
      ),
      2 => array(
        'target' => 'nid',
        'value' => '[node:nid]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['page_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_300_x_lft';
  $tag->slot = '[taxonomy] Left rail 300_x_lft';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'left_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_lft',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '779x0',
        'ad_sizes' => '300x250',
      ),
    ),
  );
  $export['term_300_x_lft'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_300_2_rht_jumbotron';
  $tag->slot = '[taxonomy] Rectangle Inline and Jumbotron';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '300x250,300x600';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'right_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_rht',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '300x250',
      ),
      1 => array(
        'browser_size' => '639x0',
        'ad_sizes' => '300x250,300x600',
      ),
    ),
  );
  $export['term_300_2_rht_jumbotron'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_728_1_a';
  $tag->slot = '[taxonomy] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
      2 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['term_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_canopy';
  $tag->slot = '[taxonomy] Canopy';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'adhesion',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['term_canopy'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_footnote_floor';
  $tag->slot = '[taxonomy] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['term_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_interscroller_728_x_a';
  $tag->slot = '[taxonomy] Interscroller/Leaderboard 2';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'infinitescroll',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_2_a,interscroller',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['term_interscroller_728_x_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_interstitial';
  $tag->slot = '[taxonomy] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['term_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_oop';
  $tag->slot = '[taxonomy] Out of Page';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '0x0';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 1,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'oop_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['term_oop'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_pagewrap';
  $tag->slot = '[taxonomy] PageWrap';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 1,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'wrap',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
      2 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['term_pagewrap'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_sponsored_logo';
  $tag->slot = '[taxonomy] Sponsored Logo';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '160x65,125x125,90x90';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'sponsored_logo',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'sponsoredlogo',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['term_sponsored_logo'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'term_728_footer';
  $tag->slot = '[taxonomy] Leaderboard 728_10_a';
  $tag->adunit = '[dfp_tag:site_id]/[term:vocabulary:machine-name]/[term:name_lowercase_without_spaces_specialchars]';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'taxonomy',
    'position' => 'bottom_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_10_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => '[term:vocabulary:machine-name]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['term_728_footer'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'user_728_1_a';
  $tag->slot = '[user] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/user';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'user',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'user',
      ),
      2 => array(
        'target' => 'user',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
      3 => array(
        'target' => 'combo',
        'value' => 'wrap',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['user_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'user_footnote_floor';
  $tag->slot = '[user] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/user';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'user',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'user',
      ),
      2 => array(
        'target' => 'user',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['user_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'user_interstitial';
  $tag->slot = '[user] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/user';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'user',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'user',
      ),
      2 => array(
        'target' => 'user',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['user_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'user_300_1_lft';
  $tag->slot = '[user] Left rail 300_1_lft';
  $tag->adunit = '[dfp_tag:site_id]/user';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'user',
    'position' => 'left_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_lft',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'user',
      ),
      2 => array(
        'target' => 'user',
        'value' => '[user:full_username_depend_of_profile_page]',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '779x0',
        'ad_sizes' => '300x250',
      ),
    ),
  );
  $export['user_300_1_lft'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'search_728_1_a';
  $tag->slot = '[search] Leaderboard 728_1_a';
  $tag->adunit = '[dfp_tag:site_id]/search';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'search',
    'position' => 'top_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_1_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'search',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['search_728_1_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'search_footnote_floor';
  $tag->slot = '[search] Footnote_Floor';
  $tag->adunit = '[dfp_tag:site_id]/search';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'search',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'footnote,floor',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'search',
      ),
    ),
    'breakpoints' => array(
    ),
  );
  $export['search_footnote_floor'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'search_interstitial';
  $tag->slot = '[search] Interstitial';
  $tag->adunit = '[dfp_tag:site_id]/search';
  $tag->size = '1x1';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'search',
    'position' => 'hidden',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => 'interstitial_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'search',
      ),
    ),
    'breakpoints' => array(),
  );
  $export['search_interstitial'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'search_300_x_lft';
  $tag->slot = '[search] Left rail 300_x_lft';
  $tag->adunit = '[dfp_tag:site_id]/search';
  $tag->size = '300x250';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'search',
    'position' => 'left_rail_rect',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '300_1_lft',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'search',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '779x0',
        'ad_sizes' => '300x250',
      ),
    ),
  );
  $export['search_300_x_lft'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'search_interscroller_728_x_a';
  $tag->slot = '[search] Interscroller/Leaderboard 2';
  $tag->adunit = '[dfp_tag:site_id]/search';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'search',
    'position' => 'infinitescroll',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_2_a,interscroller',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'search',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['search_interscroller_728_x_a'] = $tag;

  $tag = new stdClass();
  $tag->disabled = FALSE; /* Edit this to true to make a default tag disabled initially */
  $tag->api_version = 1;
  $tag->machinename = 'search_728_10_a';
  $tag->slot = '[search] Leaderboard 728_10_a';
  $tag->adunit = '[dfp_tag:site_id]/search';
  $tag->size = '728x90,970x90,320x50';
  $tag->block = 0;
  $tag->settings = array(
    'out_of_page' => 0,
    'slug' => '',
    'short_tag' => 0,
    'location' => 'search',
    'position' => 'bottom_banner',
    'adsense_ad_types' => '',
    'adsense_channel_ids' => '',
    'adsense_colors' => array(
      'background' => '',
      'border' => '',
      'link' => '',
      'text' => '',
      'url' => '',
    ),
    'targeting' => array(
      0 => array(
        'target' => 'pos',
        'value' => '728_10_a',
      ),
      1 => array(
        'target' => 'ptype',
        'value' => 'search',
      ),
    ),
    'breakpoints' => array(
      0 => array(
        'browser_size' => '1119x0',
        'ad_sizes' => '970x90,728x90',
      ),
      1 => array(
        'browser_size' => '728x0',
        'ad_sizes' => '728x90',
      ),
      2 => array(
        'browser_size' => '0x0',
        'ad_sizes' => '320x50',
      ),
    ),
  );
  $export['search_728_10_a'] = $tag;

  return $export;
}
