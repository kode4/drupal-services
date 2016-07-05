<?php
/**
 * @file
 * Press Release migration.
 * The naming  is concerned with legacy Press Release migration into new
 * Articles.
 * This is not one class for migrating all content into new Article
 * content-types.
 */

/**
 * Class PiscesPressReleaseMigration
 *
 * Migrate legacy PressReleases into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesPressReleaseMigration extends PentonArticleMigration {
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
    $this->dependencies[] = 'Links';

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
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone');

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

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // PDF mapping.
    $this->addFieldMapping('field_penton_link_media_entity', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_media_entity:source_type')
      ->defaultValue('nid');

    // Press Release boolean.
    $this->addFieldMapping('field_penton_press_release_flag', 'pressrelease');

    // Set the asset migration fields.
    $this->createFileMigrateDirectory(self::IMAGE_DEST_DIR);
    $this->createFileMigrateDirectory(self::FILES_DEST_DIR);
  }

  /**
   * Prepare the migration.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $entity
   *   The entity.
   * @param \stdClass $row
   *   The row.
   */
  public function prepare($entity, stdClass $row) {
    $language = isset($entity->language) ? $entity->language : LANGUAGE_NONE;
    $entity->metatags[$language]['robots']['value']['noindex'] = 'noindex';
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

    $row->pressrelease = 1;
    $row->noindex = 1;

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
    $row->articleTypes = $this->articleType("Articles");

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        unset($row->field_content_source);
      }
    }

    // PDF mapping.
    if (!empty($row->field_pdf)) {
      $pdfs = array();
      array_push($pdfs, $row->field_pdf);
      $row->mediaAssets = $this->pdfMigration($pdfs, self::FILES_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $row->created);
    }
  }
}
