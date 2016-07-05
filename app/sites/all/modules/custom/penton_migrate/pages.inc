<?php
/**
 * @file
 * Pages migration.
 */

/**
 * Class PentonPageToPageMigration.
 */
class PentonPageToPageMigration extends DrupalNode6Migration {

  /**
   * Machine name of the migration for the category terms.
   *
   * @var string
   */
  protected $categoriesMigration = 'Categories';

  /**
   * Machine name of the migration for the program terms.
   *
   * @var string
   */
  protected $programMigration = 'Program';

  /**
   * Class constructor.
   *
   * @param array $arguments
   *   Arguments set in the penton_migrate.migrate.inc.
   *
   * @see penton_migrate.migrate.inc
   */
  public function __construct(array $arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);

    // Set dependencies.
    $this->setDependencies($arguments);

    $this->setHighwaterField(array(
      'name' => 'changed',
      'type' => 'int',
      'alias' => 'n',
    ));

    // Retain legacy id.
    // In this case the legacy id will not be the uid, but the node id.
    $this->addFieldMapping('field_penton_legacy_id', 'nid')
      ->description('We have a common field to save the D6 nid.');

    // Categories are taxonomy terms in the legacy system.
    $this->addFieldMapping('field_penton_secondary_category', variable_get('penton_migrate_categories_vid', ''))
      ->sourceMigration($this->categoriesMigration)
      ->description('Migrate the categories attached to the page.');
    $this->addFieldMapping('field_penton_secondary_category:source_type')
      ->defaultValue('tid');

    // Programs are nodes in the legacy system.
    $this->addFieldMapping('field_penton_program', 'field_content_source')
      ->sourceMigration($this->programMigration)
      ->description('Migrate the programs attached to the page.');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Map the publication date to last update. Not in content model, but this
    // field is required.
    $this->addFieldMapping('field_penton_published_datetime', 'changed');
    $this->addFieldMapping('field_penton_published_datetime:timezone')
      ->defaultValue('America/New_York');

    // Set UUID.
    $this->addFieldMapping('uuid', 'uuid')
      ->defaultValue('uuid');

    // Set meta Data.
    $this->addFieldMapping('metatag_canonical', 'metadata_canonical');
    $this->addFieldMapping('metatag_description', 'metadata_description');
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
    $query->orderBy('n.changed');
    return $query;
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
    drush_print_r("Migrating Legacy Page node " . $row->nid);
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        drush_print_r("Unexpected Program removed.");
        unset($row->field_content_source);
      }
    }

    // Set metadata.
    $metadata = $this->metaData($row->nid);
    if ($metadata['canonical']) {
      $row->metadata_canonical = $metadata['canonical'];
    }
    if ($metadata['description']) {
      $row->metadata_description = $metadata['description'];
    }
  }

  /**
   * Return the canonical and description metadata.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $source_nid
   *   Legacy nid.
   *
   * @return metadata
   *   An array of metadata.
   */
  protected function metaData($source_nid) {
    $sourcedb = Database::getConnection('default', 'pisces');
    $query = $sourcedb
      ->select('nodewords', 'n')
      ->fields('n', array('content'))
      ->condition('n.id', $source_nid, '=')
      ->condition('n.name', 'description', '=')
      ->condition('n.content', '%' . db_like(';s:0:') . '%', 'NOT LIKE');
    $q = $query->execute();
    $description = $q->fetchAll();

    $query = $sourcedb
      ->select('nodewords', 'n')
      ->fields('n', array('content'))
      ->condition('n.id', $source_nid, '=')
      ->condition('n.name', 'canonical', '=')
      ->condition('n.content', '%' . db_like(';s:0:') . '%', 'NOT LIKE');
    $q = $query->execute();
    $canonical = $q->fetchAll();

    $metadata = array();
    foreach ($description as $desc) {
      $mdescription = unserialize($desc->content);
      $metadata['description'] = $mdescription['value'];
    }
    foreach ($canonical as $can) {
      $mcanonical = unserialize($can->content);
      $metadata['canonical'] = $mcanonical['value'];
    }
    drush_print_r($metadata['canonical']);

    return $metadata;
  }

  /**
   * Ensure source node id corresponds to a term in destination.
   *
   * @param int $source_nid
   *   Node id in source db.
   *
   * @return bool
   *   Returns TRUE if the node is mapped, FALSE otherwise.
   */
  public function nodeIsMapped($source_nid) {
    $count = db_select('migrate_map_program', 'map')
      ->fields('map', array('sourceid1'))
      ->condition('sourceid1', $source_nid, '=')
      ->countQuery()
      ->execute()
      ->fetchField();

    return $count > 0 ? TRUE : FALSE;
  }

  /**
   * Set dependencies for the current migration class.
   *
   * @param array $arguments
   *   Arguments set in the penton_migrate.migrate.inc or in previous calls.
   */
  protected function setDependencies(array $arguments) {
    // Categories and Programs have to be migrated first.
    if (!empty($arguments['categories_migration'])) {
      $this->categoriesMigration = $arguments['categories_migration'];
    }
    $this->dependencies[] = $this->categoriesMigration;

    if (!empty($arguments['program_migration'])) {
      $this->programMigration = $arguments['program_migration'];
    }
    $this->dependencies[] = $this->programMigration;
  }

}

/**
 * Class PentonZmagToPageMigration.
 */
class PentonZmagToPageMigration extends DrupalNode6Migration {

  /**
   * Machine name of the migration for the program terms.
   *
   * @var string
   */
  protected $programMigration = 'Program';

  /**
   * Class constructor.
   *
   * @param array $arguments
   *   Arguments set in the penton_migrate.migrate.inc.
   *
   * @see penton_migrate.migrate.inc
   */
  public function __construct(array $arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);

    $this->setHighwaterField(array(
      'name' => 'changed',
      'type' => 'int',
      'alias' => 'n',
    ));

    // Retain legacy id.
    // In this case the legacy id will not be the uid, but the node id.
    $this->addFieldMapping('field_penton_legacy_id', 'nid')
      ->description('We have a common field to save the D6 nid.');
    $this->addFieldMapping('field_penton_pzid', 'field_pzid')
      ->description('Publication ID');

    // Set default page type to newly created pages.
    $this->addFieldMapping('field_penton_page_type')
      ->defaultValue('zmag');

    // Programs are nodes in the legacy system.
    $this->dependencies[] = $this->programMigration;
    $this->addFieldMapping('field_penton_program', 'field_content_source')
      ->sourceMigration($this->programMigration)
      ->description('Migrate the programs attached to the page.');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Set UUID.
    $this->addFieldMapping('uuid', 'uuid')
      ->defaultValue('uuid');

    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone')
      ->defaultValue('America/New_York');

    // Set meta Data.
    $this->addFieldMapping('metatag_canonical', 'metadata_canonical');
    $this->addFieldMapping('metatag_description', 'metadata_description');
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
    $query->orderBy('n.changed');
    return $query;
  }

  /**
   * Set UUID.
   *
   * @param object $row
   *   Source data.
   *
   * @return bool
   *   Returns any changes to source data.
   */
  public function prepareRow($row) {
    drush_print_r("Migrating Legacy Zmag node " . $row->nid);
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    $row->uuid = PentonArticleMigration::migrateUUID($row->nid, Database::getConnection('default', $this->sourceConnection));

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        unset($row->field_content_source);
      }
    }

    // Set metadata.
    $metadata = $this->metaData($row->nid);
    if ($metadata['canonical']) {
      $row->metadata_canonical = $metadata['canonical'];
    }
    if ($metadata['description']) {
      $row->metadata_description = $metadata['description'];
    }
  }

  /**
   * Ensure source node id corresponds to a term in destination.
   *
   * @param int $source_nid
   *   Node id in source db.
   *
   * @return bool
   *   Returns TRUE if the node is mapped, FALSE otherwise.
   */
  public function nodeIsMapped($source_nid) {
    $count = db_select('migrate_map_program', 'map')
      ->fields('map', array('sourceid1'))
      ->condition('sourceid1', $source_nid, '=')
      ->countQuery()
      ->execute()
      ->fetchField();

    return $count > 0 ? TRUE : FALSE;
  }

  /**
   * Return the canonical and description metadata.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param int $source_nid
   *   Legacy nid.
   *
   * @return metadata
   *   An array of metadata.
   */
  protected function metaData($source_nid) {
    $sourcedb = Database::getConnection('default', 'pisces');
    $query = $sourcedb
      ->select('nodewords', 'n')
      ->fields('n', array('content'))
      ->condition('n.id', $source_nid, '=')
      ->condition('n.name', 'description', '=')
      ->condition('n.content', '%' . db_like(';s:0:') . '%', 'NOT LIKE');
    $q = $query->execute();
    $description = $q->fetchAll();

    $query = $sourcedb
      ->select('nodewords', 'n')
      ->fields('n', array('content'))
      ->condition('n.id', $source_nid, '=')
      ->condition('n.name', 'canonical', '=')
      ->condition('n.content', '%' . db_like(';s:0:') . '%', 'NOT LIKE');
    $q = $query->execute();
    $canonical = $q->fetchAll();

    $metadata = array();
    foreach ($description as $desc) {
      $mdescription = unserialize($desc->content);
      $metadata['description'] = $mdescription['value'];
    }
    foreach ($canonical as $can) {
      $mcanonical = unserialize($can->content);
      $metadata['canonical'] = $mcanonical['value'];
    }
    drush_print_r($metadata['canonical']);

    return $metadata;
  }

}
