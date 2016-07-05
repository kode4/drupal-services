<?php
/**
 * @file
 * CategoriesMigration class file.
 */

/**
 * Class CategoriesMigration
 *
 * Migrate legacy categories into Drupal 7.
 */
class CategoriesMigration extends DrupalTerm6Migration {

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
    $this->addFieldMapping('field_penton_legacy_id', 'tid')
      ->description('Retain legacy term id.');
    $this->addFieldMapping('field_penton_content_summary', 'description')
      ->description('Retain legacy term description, if any.');
  }

  /**
   * Prepare the row.
   *
   * @param object $row
   *   The row.
   *
   * @return bool
   *   Return boolean.
   */
  public function prepareRow($row) {
    drush_print_r("Migrating Legacy term " . $row->tid);
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    if (!$this->termExists($row->parent[0])) {
      unset($row->parent);
    }
  }

  /**
   * Implementation of Migration::createStub().
   *
   * @param object $migration
   *   The migration object.
   *
   * @return array|bool
   *   The source ID.
   */
  protected function createStub($migration, $source_key) {
    // Ignore an attempt to create a stub if legacy does not exist.
    if (!$this->termExists($source_key[0])) {
      return FALSE;
    }
  }

  /**
   * Check if the legacy term exists.
   *
   * @param int $tid
   *   The legacy term id.
   *
   * @return bool
   *   Return TRUE or FALSE.
   */
  public function termExists($tid) {
    $count = Database::getConnection('default', $this->sourceConnection)
      ->select('term_data', 'td')
      ->fields('td', array('tid'))
      ->condition('tid', $tid, '=')
      ->countQuery()
      ->execute()
      ->fetchField();

    return $count > 0 ? TRUE : FALSE;
  }

}
