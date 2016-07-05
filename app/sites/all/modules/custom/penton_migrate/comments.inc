<?php
/**
 * @file
 * Comment migration.
 */

/**
 * Class PentonCommentMigration.
 *
 * Migrate legacy comments into Drupal 7.
 */
class PentonCommentMigration extends DrupalComment6Migration {
  /**
   * Map fields.
   *
   * @param array $arguments
   *   The migration definition.
   *
   * @see prepare()
   */
  public function __construct(array $arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);
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
    if ($row->uid == 1) {
      // This is admin, we don't want it, set it to 0.
      $row->uid = 0;
    }

    $source_uid = (int) $row->uid;
    if ($row->uid != 0) {
      if (!$this->userIsMapped($source_uid)) {
        drush_print_r($row->uid);
        $row->uid = 0;
      }
    }
  }

  /**
   * Ensure source user id corresponds to a term in destination.
   *
   * @param int $source_uid
   *   User id in source db.
   *
   * @return bool
   *   Returns TRUE if the node is mapped, FALSE otherwise.
   */
  public function userIsMapped($source_uid) {
    $count = db_select('migrate_map_users', 'map')
      ->fields('map', array('sourceid1'))
      ->condition('sourceid1', $source_uid, '=')
      ->countQuery()
      ->execute()
      ->fetchField();

    return $count > 0 ? TRUE : FALSE;
  }
}
