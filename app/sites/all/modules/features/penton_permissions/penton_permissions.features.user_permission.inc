<?php
/**
 * @file
 * penton_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function penton_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'Production User' => 'Production User',
      'comment moderator' => 'comment moderator',
      'content manager' => 'content manager',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'Production User' => 'Production User',
      'comment moderator' => 'comment moderator',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'Production User' => 'Production User',
      'comment moderator' => 'comment moderator',
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access mollom statistics'.
  $permissions['access mollom statistics'] = array(
    'name' => 'access mollom statistics',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'mollom',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'Production User' => 'Production User',
      'comment moderator' => 'comment moderator',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'system',
  );

  // Exported permission: 'add content to books'.
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'book',
  );

  // Exported permission: 'administer Adobe DTM configuration'.
  $permissions['administer Adobe DTM configuration'] = array(
    'name' => 'administer Adobe DTM configuration',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'penton_adobe_dtm',
  );

  // Exported permission: 'administer CAPTCHA settings'.
  $permissions['administer CAPTCHA settings'] = array(
    'name' => 'administer CAPTCHA settings',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'captcha',
  );

  // Exported permission: 'administer DFP'.
  $permissions['administer DFP'] = array(
    'name' => 'administer DFP',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'dfp',
  );

  // Exported permission: 'administer Eloqua settings'.
  $permissions['administer Eloqua settings'] = array(
    'name' => 'administer Eloqua settings',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'penton_eloqua_api',
  );

  // Exported permission: 'administer User Registration settings'.
  $permissions['administer User Registration settings'] = array(
    'name' => 'administer User Registration settings',
    'roles' => array(),
    'module' => 'penton_user_register',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(),
    'module' => 'block',
  );

  // Exported permission: 'administer book outlines'.
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(),
    'module' => 'book',
  );

  // Exported permission: 'administer ckeditor'.
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(),
    'module' => 'ckeditor',
  );

  // Exported permission: 'administer cloudflare'.
  $permissions['administer cloudflare'] = array(
    'name' => 'administer cloudflare',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'cloudflare',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'comment moderator' => 'comment moderator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'features',
  );

  // Exported permission: 'administer feeds'.
  $permissions['administer feeds'] = array(
    'name' => 'administer feeds',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'administer http response headers'.
  $permissions['administer http response headers'] = array(
    'name' => 'administer http response headers',
    'roles' => array(),
    'module' => 'http_response_headers',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(),
    'module' => 'image',
  );

  // Exported permission: 'administer inline form errors'.
  $permissions['administer inline form errors'] = array(
    'name' => 'administer inline form errors',
    'roles' => array(),
    'module' => 'ife',
  );

  // Exported permission: 'administer mailsystem'.
  $permissions['administer mailsystem'] = array(
    'name' => 'administer mailsystem',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'mailsystem',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer menu fields'.
  $permissions['administer menu fields'] = array(
    'name' => 'administer menu fields',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'menu_fields',
  );

  // Exported permission: 'administer meta tags'.
  $permissions['administer meta tags'] = array(
    'name' => 'administer meta tags',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer mollom'.
  $permissions['administer mollom'] = array(
    'name' => 'administer mollom',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'mollom',
  );

  // Exported permission: 'administer newsletter manager'.
  $permissions['administer newsletter manager'] = array(
    'name' => 'administer newsletter manager',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'penton_newsletter_manager',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'Production User' => 'Production User',
      'content manager' => 'content manager',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer profile types'.
  $permissions['administer profile types'] = array(
    'name' => 'administer profile types',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: 'administer profiles'.
  $permissions['administer profiles'] = array(
    'name' => 'administer profiles',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: 'administer recaptcha'.
  $permissions['administer recaptcha'] = array(
    'name' => 'administer recaptcha',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'recaptcha',
  );

  // Exported permission: 'administer redirects'.
  $permissions['administer redirects'] = array(
    'name' => 'administer redirects',
    'roles' => array(),
    'module' => 'redirect',
  );

  // Exported permission: 'administer robots.txt'.
  $permissions['administer robots.txt'] = array(
    'name' => 'administer robots.txt',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'robotstxt',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(),
    'module' => 'search',
  );

  // Exported permission: 'administer services'.
  $permissions['administer services'] = array(
    'name' => 'administer services',
    'roles' => array(),
    'module' => 'services',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer site verify'.
  $permissions['administer site verify'] = array(
    'name' => 'administer site verify',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'site_verify',
  );

  // Exported permission: 'administer smtp module'.
  $permissions['administer smtp module'] = array(
    'name' => 'administer smtp module',
    'roles' => array(),
    'module' => 'smtp',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'Production User' => 'Production User',
      'content manager' => 'content manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer uuid'.
  $permissions['administer uuid'] = array(
    'name' => 'administer uuid',
    'roles' => array(),
    'module' => 'uuid',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'administer xmlsitemap'.
  $permissions['administer xmlsitemap'] = array(
    'name' => 'administer xmlsitemap',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'xmlsitemap',
  );

  // Exported permission: 'advanced migration information'.
  $permissions['advanced migration information'] = array(
    'name' => 'advanced migration information',
    'roles' => array(),
    'module' => 'migrate',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass mollom protection'.
  $permissions['bypass mollom protection'] = array(
    'name' => 'bypass mollom protection',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'mollom',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'clear penton_feed_importer feeds'.
  $permissions['clear penton_feed_importer feeds'] = array(
    'name' => 'clear penton_feed_importer feeds',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create block_content content'.
  $permissions['create block_content content'] = array(
    'name' => 'create block_content content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create data_table_detail content'.
  $permissions['create data_table_detail content'] = array(
    'name' => 'create data_table_detail content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create display_admin content'.
  $permissions['create display_admin content'] = array(
    'name' => 'create display_admin content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create gating_copy content'.
  $permissions['create gating_copy content'] = array(
    'name' => 'create gating_copy content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create media_entity content'.
  $permissions['create media_entity content'] = array(
    'name' => 'create media_entity content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create new books'.
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'book',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create penton_feed content'.
  $permissions['create penton_feed content'] = array(
    'name' => 'create penton_feed content',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(),
    'module' => 'path',
  );

  // Exported permission: 'customize ckeditor'.
  $permissions['customize ckeditor'] = array(
    'name' => 'customize ckeditor',
    'roles' => array(),
    'module' => 'ckeditor',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any block_content content'.
  $permissions['delete any block_content content'] = array(
    'name' => 'delete any block_content content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any data_table_detail content'.
  $permissions['delete any data_table_detail content'] = array(
    'name' => 'delete any data_table_detail content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any display_admin content'.
  $permissions['delete any display_admin content'] = array(
    'name' => 'delete any display_admin content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any gating_copy content'.
  $permissions['delete any gating_copy content'] = array(
    'name' => 'delete any gating_copy content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any media_entity content'.
  $permissions['delete any media_entity content'] = array(
    'name' => 'delete any media_entity content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any penton_feed content'.
  $permissions['delete any penton_feed content'] = array(
    'name' => 'delete any penton_feed content',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own block_content content'.
  $permissions['delete own block_content content'] = array(
    'name' => 'delete own block_content content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own data_table_detail content'.
  $permissions['delete own data_table_detail content'] = array(
    'name' => 'delete own data_table_detail content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own display_admin content'.
  $permissions['delete own display_admin content'] = array(
    'name' => 'delete own display_admin content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own gating_copy content'.
  $permissions['delete own gating_copy content'] = array(
    'name' => 'delete own gating_copy content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own media_entity content'.
  $permissions['delete own media_entity content'] = array(
    'name' => 'delete own media_entity content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own penton_feed content'.
  $permissions['delete own penton_feed content'] = array(
    'name' => 'delete own penton_feed content',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in article_type'.
  $permissions['delete terms in article_type'] = array(
    'name' => 'delete terms in article_type',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in dfp_ad_categories'.
  $permissions['delete terms in dfp_ad_categories'] = array(
    'name' => 'delete terms in dfp_ad_categories',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in page_type'.
  $permissions['delete terms in page_type'] = array(
    'name' => 'delete terms in page_type',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'download file'.
  $permissions['download file'] = array(
    'name' => 'download file',
    'roles' => array('authenticated user' => 'authenticated user'),
    'module' => 'uc_file',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any block_content content'.
  $permissions['edit any block_content content'] = array(
    'name' => 'edit any block_content content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any data_table_detail content'.
  $permissions['edit any data_table_detail content'] = array(
    'name' => 'edit any data_table_detail content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any display_admin content'.
  $permissions['edit any display_admin content'] = array(
    'name' => 'edit any display_admin content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any gating_copy content'.
  $permissions['edit any gating_copy content'] = array(
    'name' => 'edit any gating_copy content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any main profile'.
  $permissions['edit any main profile'] = array(
    'name' => 'edit any main profile',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: 'edit any media_entity content'.
  $permissions['edit any media_entity content'] = array(
    'name' => 'edit any media_entity content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any penton_feed content'.
  $permissions['edit any penton_feed content'] = array(
    'name' => 'edit any penton_feed content',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit meta tags'.
  $permissions['edit meta tags'] = array(
    'name' => 'edit meta tags',
    'roles' => array(
      'Production User' => 'Production User',
      'content manager' => 'content manager',
    ),
    'module' => 'metatag',
  );

  // Exported permission: 'edit mimemail user settings'.
  $permissions['edit mimemail user settings'] = array(
    'name' => 'edit mimemail user settings',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'mimemail',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own block_content content'.
  $permissions['edit own block_content content'] = array(
    'name' => 'edit own block_content content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'edit own data_table_detail content'.
  $permissions['edit own data_table_detail content'] = array(
    'name' => 'edit own data_table_detail content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own display_admin content'.
  $permissions['edit own display_admin content'] = array(
    'name' => 'edit own display_admin content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own gating_copy content'.
  $permissions['edit own gating_copy content'] = array(
    'name' => 'edit own gating_copy content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own main profile'.
  $permissions['edit own main profile'] = array(
    'name' => 'edit own main profile',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: 'edit own media_entity content'.
  $permissions['edit own media_entity content'] = array(
    'name' => 'edit own media_entity content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own penton_feed content'.
  $permissions['edit own penton_feed content'] = array(
    'name' => 'edit own penton_feed content',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in article_type'.
  $permissions['edit terms in article_type'] = array(
    'name' => 'edit terms in article_type',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in dfp_ad_categories'.
  $permissions['edit terms in dfp_ad_categories'] = array(
    'name' => 'edit terms in dfp_ad_categories',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in page_type'.
  $permissions['edit terms in page_type'] = array(
    'name' => 'edit terms in page_type',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'Production User' => 'Production User',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'get a system variable'.
  $permissions['get a system variable'] = array(
    'name' => 'get a system variable',
    'roles' => array(),
    'module' => 'services',
  );

  // Exported permission: 'get any binary files'.
  $permissions['get any binary files'] = array(
    'name' => 'get any binary files',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'services',
  );

  // Exported permission: 'get own binary files'.
  $permissions['get own binary files'] = array(
    'name' => 'get own binary files',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'services',
  );

  // Exported permission: 'import penton_feed_importer feeds'.
  $permissions['import penton_feed_importer feeds'] = array(
    'name' => 'import penton_feed_importer feeds',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'maintain nodeblock'.
  $permissions['maintain nodeblock'] = array(
    'name' => 'maintain nodeblock',
    'roles' => array(),
    'module' => 'nodeblock',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'features',
  );

  // Exported permission: 'migration information'.
  $permissions['migration information'] = array(
    'name' => 'migration information',
    'roles' => array(),
    'module' => 'migrate',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(),
    'module' => 'pathauto',
  );

  // Exported permission: 'penton post comments'.
  $permissions['penton post comments'] = array(
    'name' => 'penton post comments',
    'roles' => array(
      'Production User' => 'Production User',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'penton_comment',
  );

  // Exported permission: 'perform unlimited index queries'.
  $permissions['perform unlimited index queries'] = array(
    'name' => 'perform unlimited index queries',
    'roles' => array(),
    'module' => 'services',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'report to mollom'.
  $permissions['report to mollom'] = array(
    'name' => 'report to mollom',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'mollom',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'save file information'.
  $permissions['save file information'] = array(
    'name' => 'save file information',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'services',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'send arbitrary files'.
  $permissions['send arbitrary files'] = array(
    'name' => 'send arbitrary files',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'mimemail',
  );

  // Exported permission: 'set a system variable'.
  $permissions['set a system variable'] = array(
    'name' => 'set a system variable',
    'roles' => array(),
    'module' => 'services',
  );

  // Exported permission: 'skip CAPTCHA'.
  $permissions['skip CAPTCHA'] = array(
    'name' => 'skip CAPTCHA',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'captcha',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'unlock penton_feed_importer feeds'.
  $permissions['unlock penton_feed_importer feeds'] = array(
    'name' => 'unlock penton_feed_importer feeds',
    'roles' => array(
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use ctools import'.
  $permissions['use ctools import'] = array(
    'name' => 'use ctools import',
    'roles' => array(),
    'module' => 'ctools',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'content manager' => 'content manager',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'content manager' => 'content manager',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view any main profile'.
  $permissions['view any main profile'] = array(
    'name' => 'view any main profile',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: 'view any unpublished article content'.
  $permissions['view any unpublished article content'] = array(
    'name' => 'view any unpublished article content',
    'roles' => array(
      'Production User' => 'Production User',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished block_content content'.
  $permissions['view any unpublished block_content content'] = array(
    'name' => 'view any unpublished block_content content',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished content'.
  $permissions['view any unpublished content'] = array(
    'name' => 'view any unpublished content',
    'roles' => array(
      'Production User' => 'Production User',
      'content preview' => 'content preview',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished data_table_detail content'.
  $permissions['view any unpublished data_table_detail content'] = array(
    'name' => 'view any unpublished data_table_detail content',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished display_admin content'.
  $permissions['view any unpublished display_admin content'] = array(
    'name' => 'view any unpublished display_admin content',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished gating_copy content'.
  $permissions['view any unpublished gating_copy content'] = array(
    'name' => 'view any unpublished gating_copy content',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished media_entity content'.
  $permissions['view any unpublished media_entity content'] = array(
    'name' => 'view any unpublished media_entity content',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished page content'.
  $permissions['view any unpublished page content'] = array(
    'name' => 'view any unpublished page content',
    'roles' => array(
      'Production User' => 'Production User',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished penton_feed content'.
  $permissions['view any unpublished penton_feed content'] = array(
    'name' => 'view any unpublished penton_feed content',
    'roles' => array(
      'Production User' => 'Production User',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view own main profile'.
  $permissions['view own main profile'] = array(
    'name' => 'view own main profile',
    'roles' => array(),
    'module' => 'profile2',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'content manager' => 'content manager',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'content manager' => 'content manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'Production User' => 'Production User',
      'comment moderator' => 'comment moderator',
      'content manager' => 'content manager',
      'feeds manager' => 'feeds manager',
    ),
    'module' => 'system',
  );

  return $permissions;
}
