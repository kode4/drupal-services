<?php
/**
 * @file
 * Datasheet migration.
 * The naming is concerned with legacy Datasheet migration into new Articles.
 * Not to be confused with Data Tables. Datasheets are white papers.
 */

/**
 * Class PiscesDataSheetMigration
 *
 * Migrate legacy Datasheets into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesDataSheetMigration extends PentonArticleMigration {

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

    // Program mapping.
    $this->addFieldMapping('field_penton_program', 'field_content_source')
      ->sourceMigration('Program');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Publication date.
    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone');

    // Exclude from lists.
    $this->addFieldMapping('field_penton_allow_in_rss_feed', 'rssFlag');

    // Related Galleries.
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

    // Gating.
    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // White paper mapping.
    $this->addFieldMapping('field_penton_link_media_entity', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_media_entity:source_type')
      ->defaultValue('nid');

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

    // Exclude from lists.
    if (isset($row->field_exclude_from_lists)) {
      $row->rssFlag = $this->includeInRSS($row->field_exclude_from_lists);
    }
    else {
      // Well there is no value so this is like saying it's set to zero and in
      // that case needs to be converted to 1.
      $row->rssFlag = 1;
    }

    // Related Galleries.
    if (isset($row->field_gallery_related_media)) {
      $row->relatedContent = $row->field_gallery_related_media;
    }

    // Create media asset from white paper.
    // PDF mapping.
    if (!empty($row->field_datasheet_upload)) {
      $pdfs = array();
      array_push($pdfs, $row->field_datasheet_upload);
      $row->mediaAssets = $this->pdfMigration($pdfs, self::FILES_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $row->created);
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

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);

    // Article Type.
    $row->articleTypes = $this->articleType("White Paper");
  }

}
