<?php
/**
 * @file
 * Article migration.
 * The naming  is concerned with legacy Article migration into new Articles.
 * This is not one class for migrating all content into new Article
 * content-types.
 */

/**
 * Class PiscesArticleMigration
 *
 * Migrate legacy Articles into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesArticleMigration extends PentonArticleMigration {

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

    // Set dependencies.
    if (!empty($arguments['author_migration'])) {
      $this->authorMigration = $arguments['author_migration'];
      $this->dependencies[] = $this->authorMigration;
    }

    // Set Author ID.
    $this->addFieldMapping('field_penton_author', 'field_author')
      ->sourceMigration('Authors');

    // Article intro.
    // If no article intro exists then the deck field will be used.
    $this->addFieldMapping('field_penton_content_summary', 'intro_content');
    $this->addFieldMapping('field_penton_content_summary:format')->defaultValue('filtered_html');

    // Program mapping.
    $this->addFieldMapping('field_penton_program', 'field_content_source')
      ->sourceMigration('Program');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Publication date.
    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone')
      ->defaultValue('America/New_York');

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

    // Exclude from lists.
    $this->addFieldMapping('field_penton_allow_in_rss_feed', 'rssFlag');

    // Gallery mapping.
    $this->addFieldMapping('field_penton_link_image_gallery', 'galleryAssets');
    $this->addFieldMapping('field_penton_link_image_gallery:source_type')
      ->defaultValue('nid');

    // Image mapping.
    $this->addFieldMapping('field_penton_link_media_feat_img', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_media_feat_img:source_type')
      ->defaultValue('nid');

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // Gating level.
    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

    // Insert Byline if it exists.
    $this->addFieldMapping('field_penton_byline', 'field_byline');

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

    // Article Type.
    $row->articleTypes = $this->articleType("Article");

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);

    // Exclude from lists.
    if (isset($row->field_exclude_from_lists)) {
      $row->rssFlag = $this->includeInRSS($row->field_exclude_from_lists);
    }
    else {
      // Well there is no value so this is like saying it's set to zero and in
      // that case needs to be converted to 1.
      $row->rssFlag = 1;
    }

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        unset($row->field_content_source);
      }
    }

    // Create media asset from image promo.
    if (isset($row->field_image_promo)) {
      $credits = "";
      if (isset($row->field_image_promo_credits)) {
        $credits = $row->field_image_promo_credits;
      }
      $row->mediaAssets = $this->imagePromoMigration($row->nid, $row->field_image_promo, self::IMAGE_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $credits, $row->created);
    }
  }
}
