<?php
/**
 * @file
 * Link migration.
 * The naming  is concerned with legacy Link migration into new Articles.
 */

/**
 * Class PiscesLinkMigration
 *
 * Migrate legacy Links into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesLinkMigration extends PentonArticleMigration {

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
    $this->dependencies[] = 'Blogs';
    $this->dependencies[] = 'Datasheets';
    $this->dependencies[] = 'DataTables';
    $this->dependencies[] = 'Galleries';

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // Gating level.
    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

    // Publication date.
    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone')
      ->defaultValue('America/New_York');

    // Image mapping.
    $this->addFieldMapping('field_penton_link_media_feat_img', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_media_feat_img:source_type')
      ->defaultValue('nid');

    // Link mapping.
    $this->addFieldMapping('field_penton_link', 'field_link_url');

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

    // Article Type.
    $row->articleTypes = $this->articleType("Link");

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);

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
