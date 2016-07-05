<?php
/**
 * @file
 * Blog migration.
 * The naming is concerned with legacy Blog Entry migration into new Articles.
 */

/**
 * Class PiscesBlogMigration
 *
 * Migrate legacy Blogs into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesBlogMigration extends PentonArticleMigration {

  // Where to suck the image files to.
  const IMAGE_DEST_DIR = 'public://';
  const FILES_DEST_DIR = 'public://';

  /**
   * Map fields.
   *
   * @param array $arguments
   *   Array from migration setup.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->dependencies[] = 'Articles';

    // Article intro.
    // If no article intro exists then the deck field will be used.
    $this->addFieldMapping('field_penton_content_summary', 'intro_content');
    $this->addFieldMapping('field_penton_content_summary:format')->defaultValue('filtered_html');

    // Privacy gating.
    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

    // Publication date.
    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone');

    // Exclude from lists.
    $this->addFieldMapping('field_penton_allow_in_rss_feed', 'rssFlag');

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // Image mapping.
    $this->addFieldMapping('field_penton_link_media_feat_img', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_media_feat_img:source_type')
      ->defaultValue('nid');

    // Related Media
    // and
    // Related articles.
    $this->addFieldMapping('field_penton_related_content', 'relatedContent')
      ->sourceMigration(
        array(
          'Articles',
          'Blogs',
          'Datasheets',
          'DataTables',
          'Galleries',
          'PressReleases',
          'Videos',
          'Links',
        )
      );

    // Insert Byline if it exists.
    $this->addFieldMapping('field_penton_byline', 'field_byline');


    // BlogHP mapping.
    $this->addFieldMapping('field_penton_program', 'blogHPid')
      ->sourceMigration('Program');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Add uid to author
    // Set Author ID.
    // User id.
    $default_uid = 1;
    $this->addFieldMapping('field_penton_author', 'uid')
      ->sourceMigration('Users')
      ->defaultValue($default_uid);

    // Set the asset migration fields.
    $this->createFileMigrateDirectory(self::IMAGE_DEST_DIR);
    $this->createFileMigrateDirectory(self::FILES_DEST_DIR);
  }

  /**
   * Prepare any migration is a field to field migration won't do.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $row
   *   Source data.
   *
   * @return bool
   *   Returns any changes to source data.
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Set intro.
    // If no article intro exists then the deck field will be used.
    if (isset($row->field_article_intro)) {
      $row->intro_content = $row->field_article_intro;
    }
    else {
      if (isset($row->field_deck)) {
        $row->intro_content = $row->field_deck;
      }
      else {
        $row->intro_content = "";
      }
    }

    // Exclude from lists.
    if (isset($row->field_exclude_from_lists)) {
      $row->rssFlag = $this->includeInRSS($row->field_exclude_from_lists);
    }
    else {
      // Well there is no value so this is like saying it's set to zero and in
      // that case needs to be converted to 1.
      $row->rssFlag = 1;
    }

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);

    // Article Type.
    $row->articleTypes = $this->articleType("Article");

    // Create media asset from image promo.
    if (isset($row->field_image_promo)) {
      $credits = "";
      if (isset($row->field_image_promo_credits)) {
        $credits = $row->field_image_promo_credits;
      }
      $row->mediaAssets = $this->imagePromoMigration($row->nid, $row->field_image_promo, self::IMAGE_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $credits, $row->created);
    }

    // Related Media
    // and
    // Related articles.
    $row->relatedContent = array();
    if (isset($row->field_article_related_media)) {
      $row->relatedContent = $row->field_article_related_media;
    }
    if (isset($row->field_article_related_articles)) {
      foreach ($row->field_article_related_articles as $article) {
        array_push($row->relatedContent, $article);
      }
    }

    // Blog HP
    $row->blogHPid = $this->blogHP($row->nid);
  }

  /**
   * Return the blog_hp as tid.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $source_nid
   *   Legacy nid.
   *
   * @return blog_hp
   *   Blog HP TID.
   */
  public function blogHP($source_nid) {
    $query = $this->sourceDbConnection()
      ->select('og_ancestry', 'oa')
      ->fields('oa', array('group_nid'))
      ->condition('oa.nid', $source_nid, '=');
    $q = $query->execute();
    $tids = $q->fetchAll();

    $tid = array();
    foreach ($tids as $item) {
      array_push($tid, $item->group_nid);
    }
    return $tid;
  }
}
