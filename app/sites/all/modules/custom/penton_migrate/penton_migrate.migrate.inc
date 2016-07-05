<?php
/**
 * @file
 * Because the name of this file is the module name plus '.migrate.inc', when
 * hook_migrate_api is invoked by the Migrate module this file is automatically
 * loaded - thus, you don't need to implement your hook in the .module file.
 */

/*
 * You must implement hook_migrate_api(), setting the API level to 2, if you are
 * implementing any migration classes. If your migration application is static -
 * that is, you know at implementation time exactly what migrations must be
 * instantiated - then you should register your migrations here. If your
 * application is more dynamic (for example, if selections in the UI determine
 * exactly what migrations need to be instantiated), then you would register
 * your migrations using registerMigration() - see migrate_example_baseball for
 * more information.
 */

/**
 * Implements hook_migrate_api().
 */
function penton_migrate_migrate_api() {
  // Define global API settings.
  $api = array(
    'api' => 2,
    'groups' => array(
      'penton_legacy_users' => array(
        'title' => t('Penton legacy User migration'),
      ),
      'penton_legacy_nodes' => array(
        'title' => t('Penton legacy Node migration'),
      ),
      'penton_legacy_taxonomy_terms' => array(
        'title' => t('Penton legacy Taxonomy terms migrations'),
      ),
      'penton_legacy_comments' => array(
        'title' => t('Penton legacy comment migration'),
      ),
    ),
    'destination handlers' => array(
      'PentonMigrateUuidHandler',
      'PentonMigrateUuidNodeHandler',
    ),
  );

  // Each migration being registered takes an array of arguments, some required
  // and some optional. Start with the common arguments required by all - the
  // source_connection (connection key, set up in settings.php, pointing to
  // the Drupal 6 database), source_version (major version of Drupal), and
  // group_name (a.k.a. import job).

  // We're using the D2D support for a migration D6 to D7.
  // See connection.inc for details about source connection.
  $common_arguments = array(
    'source_version' => 6,
    'source_connection' => 'pisces',
  );

  // Register the migrations.
  // Users.
  $api['migrations']['Users'] = $common_arguments + array(
    'description' => t('Migration of users from Pisces Environments'),
    'class_name' => 'PentonUserMigration',
    'group_name' => 'penton_legacy_users',
    'picture_migration' => 'Pictures',
    'role_migration' => 'Roles',
  );

  // User pictures.
  $api['migrations']['Pictures'] = $common_arguments + array(
    'description' => t('Migration of user pictures from Pisces Environments'),
    'default_uid' => 1,
    'class_name' => 'PentonUserPictureMigration',
    'group_name' => 'penton_legacy_users',
    'source_dir' => variable_get('penton_migrate_picture_host', 'http://waste360.legacy.penton.vm'),
    'destination_dir' => 'public://',
  );

  $api['migrations']['Roles'] = $common_arguments + array(
    'description' => t('Migration of user roles from Pisces Environments'),
    'class_name' => 'PentonUserRoleMigration',
    'group_name' => 'penton_legacy_users',
  );

  // Categories.
  $api['migrations']['Categories'] = $common_arguments + array(
    'description' => t('Migration of category terms from Drupal 6'),
    'group_name' => 'penton_legacy_taxonomy_terms',
    'class_name' => 'CategoriesMigration',
    // D6 Vocabulary ID.
    // Note that in D6, vocabularies didn't have machine names, so we need to
    // use the vocabulary id. Since it might be different across environments,
    // let's add this to the variables.
    'source_vocabulary' => variable_get('penton_migrate_categories_vid', ''),
    'destination_vocabulary' => 'categories',
  );

  // Program.
  // Program terms in destination are composed from nodes in source.
  $api['migrations']['Program'] = $common_arguments + array(
    'description' => t('Migration D6 Blog HP nodes into Program terms in D7.'),
    'group_name' => 'penton_legacy_taxonomy_terms',
    'class_name' => 'ProgramMigration',
    'source_type' => array('content_source', 'blog_hp'),
    // destination_type will be changed in the class. But for the parent to
    // construct it, it is required.
    'destination_type' => 'article',
  );

  $api['migrations']['Articles'] = $common_arguments + array(
    'description' => t('Migration of Articles from Pisces Environments'),
    'class_name' => 'PiscesArticleMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'article',
    'destination_type' => 'article',
    'author_migration' => 'Authors',
    'user_migration' => 'Users',
  );

  $api['migrations']['Galleries'] = $common_arguments + array(
    'description' => t('Migration of Galleries from Pisces Environments'),
    'class_name' => 'PiscesGalleryMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'gallery',
    'destination_type' => 'article',
    'author_migration' => 'Authors',
    'user_migration' => 'Users',
  );

  // Authors.
  // Authors are users in D7 but a node bundle in D6.
  $api['migrations']['Authors'] = $common_arguments + array(
    'description' => t('Migration D6 Author profile nodes into Author users in D7.'),
    'group_name' => 'penton_legacy_users',
    'class_name' => 'PentonAuthorMigration',
    'source_type' => 'author',
    // Destination_type will be changed in the class. But for the parent to
    // construct it, it is required.
    'destination_type' => 'user',
    'role_migration' => 'Roles',
    'picture_migration' => 'AuthorPictures',
    'user_migration' => 'Users',
  );

  // Blogger profiles are nodes, but they are associated with a user in legacy,
  // in D7 it's all user.
  $api['migrations']['BloggerProfiles'] = $common_arguments + array(
    'description' => t('Migration D6 Blogger profile nodes into Author users in D7.'),
    'group_name' => 'penton_legacy_users',
    'class_name' => 'PentonBloggerProfileMigration',
    'source_type' => 'blogger_profile',
    'destination_type' => 'user',
    'role_migration' => 'Roles',
    'picture_migration' => 'AuthorPictures',
    'user_migration' => 'Users',
  );

  $api['migrations']['AuthorPictures'] = $common_arguments + array(
    'description' => t('Migration D6 Author profile pictures into Author users in D7.'),
    'group_name' => 'penton_legacy_users',
    'class_name' => 'PentonAuthorFileMigration',
    'default_uid' => 1,
    'source_dir' => variable_get('penton_migrate_picture_host', 'http://waste360.legacy.penton.vm'),
    'destination_dir' => 'public://',
  );

  $api['migrations']['DataTables'] = $common_arguments + array(
    'description' => t('Migration of Data Tables from Pisces Environments'),
    'class_name' => 'PiscesDataTableMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'data_table',
    'destination_type' => 'article',
    'user_migration' => 'Users',
  );

  $api['migrations']['Blogs'] = $common_arguments + array(
    'description' => t('Migration of Blog entries from Pisces Environments'),
    'class_name' => 'PiscesBlogMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'blog',
    'destination_type' => 'article',
    'user_migration' => 'Users',
  );

  $api['migrations']['Videos'] = $common_arguments + array(
    'description' => t('Migration of Video entries from Pisces Environments'),
    'class_name' => 'PiscesVideoMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'video',
    'destination_type' => 'article',
    'author_migration' => 'Authors',
    'user_migration' => 'Users',
  );

  $api['migrations']['PressReleases'] = $common_arguments + array(
    'description' => t('Migration of Press Releases from Pisces Environments'),
    'class_name' => 'PiscesPressReleaseMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'press_release',
    'destination_type' => 'article',
    'user_migration' => 'Users',
  );

  $api['migrations']['Datasheets'] = $common_arguments + array(
    'description' => t('Migration of Datasheets from Pisces Environments'),
    'class_name' => 'PiscesDataSheetMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'datasheet',
    'destination_type' => 'article',
    'user_migration' => 'Users',
  );

  $api['migrations']['PageToPage'] = $common_arguments + array(
    'description' => t('Migration of D6 Pages into Pages in D7.'),
    'class_name' => 'PentonPageToPageMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'page',
    'destination_type' => 'page',
  );

  $api['migrations']['ZmagToPage'] = $common_arguments + array(
    'description' => t('Migration of D6 Zmag issues into Pages in D7.'),
    'class_name' => 'PentonZmagToPageMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'penton_zmag',
    'destination_type' => 'page',
  );

  $api['migrations']['Links'] = $common_arguments + array(
    'description' => t('Migration of Links from Pisces Environments'),
    'class_name' => 'PiscesLinkMigration',
    'group_name' => 'penton_legacy_nodes',
    'source_type' => 'link',
    'destination_type' => 'article',
    'user_migration' => 'Users',
  );

  $api['migrations']['ArticleComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Articles'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'article',
    'destination_type' => 'article',
    'node_migration' => 'Articles',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['BlogComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Blogs'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'blog',
    'destination_type' => 'article',
    'node_migration' => 'Blogs',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['DatasheetComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces DataSheets'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'datasheet',
    'destination_type' => 'article',
    'node_migration' => 'Datasheets',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['DataTableComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces DataTables'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'data_table',
    'destination_type' => 'article',
    'node_migration' => 'DataTables',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['GalleryComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Galleries'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'gallery',
    'destination_type' => 'article',
    'node_migration' => 'Galleries',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['LinkComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Links'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'link',
    'destination_type' => 'article',
    'node_migration' => 'Links',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['PageComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Pages'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'page',
    'destination_type' => 'page',
    'node_migration' => 'PageToPage',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['PressReleaseComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Press Releases'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'press_release',
    'destination_type' => 'article',
    'node_migration' => 'PressReleases',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['VideoComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Videos'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'video',
    'destination_type' => 'article',
    'node_migration' => 'Videos',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  $api['migrations']['ZmagComments'] = $common_arguments + array(
    'description' => t('Migration of Comments from Pisces Zmags'),
    'class_name' => 'PentonCommentMigration',
    'group_name' => 'penton_legacy_comments',
    'source_type' => 'penton_zmag',
    'destination_type' => 'page',
    'node_migration' => 'ZmagToPage',
    'user_migration' => 'Users',
    'default_uid' => 0,
  );

  return $api;
}
