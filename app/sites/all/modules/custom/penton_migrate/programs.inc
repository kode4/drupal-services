<?php
/**
 * @file
 * Program migration.
 */

/**
 * Class ProgramMigration
 *
 * Migrate several node types into Program terms in Drupal 7.
 * So, let's derivate from DrupalNode6Migration and change the destination.
 *
 * @see DrupalNode6Migration
 */
class ProgramMigration extends DrupalNode6Migration {

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
    // CHange destination on the fly.
    $this->destination = new MigrateDestinationTerm('program');
    $this->setHighwaterField(array(
      'name' => 'changed',
      'alias' => 'n',
      'type' => 'int',
    ));
    // Map fields.
    $this->addFieldMapping('name', 'title');
    // Retain legacy id.
    $this->addFieldMapping('field_penton_legacy_id', 'nid')
      ->description('We have a common field to save the D6 nid');

    // Set UUID.
    $this->addFieldMapping('uuid', 'uuid')
      ->defaultValue('uuid');
  }

  /**
   * Extend the base D6 migration query.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @return \QueryConditionInterface
   *   The updated query.
   */
  protected function query() {
    // Get the default query.
    $query = parent::query();
    // Join the penton_UUID table.
    $query->innerJoin('penton_uuid', 'pu', 'n.nid=pu.id');
    $query->fields('pu', array('uuid'));
    $query->orderBy($this->newOnly ? 'n.nid' : 'n.changed');
    return $query;
  }

  /**
   * Prepare source data.
   *
   * @param object $row
   *   The source data as retrieved from the source database.
   *
   * @return bool
   *   Returns FALSE to skip row.
   */
  public function prepareRow($row) {
    drush_print_r("Migrating Legacy term " . $row->tid);
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    return TRUE;
  }

}
