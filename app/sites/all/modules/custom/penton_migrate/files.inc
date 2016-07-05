<?php
/**
 * @file
 * Files migration.
 */

/**
 * Class PentonAuthorFileMigration.
 *
 * Migrate author pictures from node to user. This is also valid for blogger
 * profiles.
 */
class PentonAuthorFileMigration extends DrupalFile6Migration {

  /**
   * Map fields.
   *
   * @param array $arguments
   *   Array from migration setup.
   */
  public function __construct($arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);

    $this->addFieldMapping('picture', 'field_pm_author_image');
    // Keep files on rollback.
    $this->addFieldMapping('picture:preserve_files')
      ->defaultValue(TRUE);
    $this->addFieldMapping('picture:language')
      ->defaultValue(LANGUAGE_NONE);
  }

  /**
   * Implement our own query.
   *
   * As we need only the files related to Authors and blogger profiles.
   */
  protected function query() {
    $query = Database::getConnection('default', $this->sourceConnection)
      ->select('files', 'f')
      ->fields('f')
      ->orderBy($this->newOnly ? 'f.fid' : 'f.timestamp');
    $query->innerJoin('content_field_pm_author_image', 'ai', 'ai.field_pm_author_image_fid=f.fid');
    $query->groupBy('ai.field_pm_author_image_fid');
    return $query;
  }

}
