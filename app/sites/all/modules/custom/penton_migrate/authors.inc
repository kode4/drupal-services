<?php
/**
 * @file
 * Author migration.
 */

/**
 * Class PentonAuthorMigration.
 *
 * Migrate legacy authors into Drupal 7.
 */
class PentonAuthorMigration extends DrupalNode6Migration {

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

    // Set dependencies.
    if (!empty($arguments['picture_migration'])) {
      $this->pictureMigration = $arguments['picture_migration'];
      $this->dependencies[] = $this->pictureMigration;
    }
    if (!empty($arguments['role_migration'])) {
      $this->roleMigration = $arguments['role_migration'];
      $this->dependencies[] = $this->roleMigration;
    }
    if (!empty($arguments['user_migration'])) {
      $this->userMigration = $arguments['user_migration'];
      $this->dependencies[] = $this->userMigration;
    }

    // Set highwater mark.
    // Authors are nodes in legacy, we can then use "changed" field.
    $this->setHighwaterField(array(
      'name' => 'changed',
      'type' => 'int',
      'alias' => 'n',
    ));

    // Set destination to be users.
    $this->destination = new DrupalDestinationUser(array('md5_passwords' => TRUE));

    // Keep track of migrations thanks to link:
    // Source node id, Destination user id.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'Source node ID',
          'alias' => 'n',
        ),
      ),
      DrupalDestinationUser::getKeySchema()
    );

    // Remove all mappings set by default node migration parent classes.
    $this->removeNodeFieldMapping();
    // Remove all mappings set by default user migration destination.
    $this->removeUserFieldMapping();

    // Retain legacy id.
    // In this case the legacy id will not be the uid, but the node id.
    $this->addFieldMapping('field_penton_legacy_id', 'nid')
      ->description('We have a common field to save the D6 nid');

    // Map fields.
    $this->addFieldMapping('name', 'title')
      ->description('Author name');
    // Set all fields for personal information. Country is required as addresses
    // are keyed by country code.
    $this->addFieldMapping('field_penton_profile')
      ->defaultValue('US')
      ->description('Country');
    $this->addFieldMapping('field_penton_profile:first_name', 'field_pm_author_first_name')
      ->description('First name');
    $this->addFieldMapping('field_penton_profile:middle_name', 'field_pm_author_middle_name')
      ->description('Middle name');
    $this->addFieldMapping('field_penton_profile:last_name', 'field_pm_author_last_name')
      ->description('Last name');
    $this->addFieldMapping('field_penton_profile:organisation_name', 'field_pm_author_company')
      ->description('Company');
    $this->addFieldMapping('field_penton_secondary_email', 'field_pm_author_email')
      ->description('Author email');
    $this->addFieldMapping('field_penton_job_title', 'field_pm_author_title')
      ->description('Job title');
    $this->addFieldMapping('field_penton_salutation', 'field_pm_author_salutation')
      ->description('Salutation');
    $this->addFieldMapping('picture', 'field_pm_author_image')
      ->sourceMigration('AuthorPictures')
      ->description('Author pictures migration.');
    $this->addFieldMapping('field_penton_twitter_account', 'field_twitter_username')
      ->description('Twitter account');
    $this->addFieldMapping('field_penton_site_link', 'field_pm_author_website')
      ->description('Site links');
    $this->addFieldMapping('field_penton_site_link:title', 'field_pm_author_website:title');
    $this->addFieldMapping('field_penton_site_link:attributes', 'field_pm_author_website:attributes');
    $this->addFieldMapping('field_penton_site_link:language')
      ->defaultValue(LANGUAGE_NONE);
    $this->addFieldMapping('field_penton_summary', 'body')
      ->description('Bio');
    $this->addFieldMapping('field_penton_summary:format')->defaultValue('filtered_html');
    // Make sure author profiles are displayed.
    $this->addFieldMapping('field_penton_display_profile')
      ->defaultValue(1);

    // Add role fields.
    $this->sourceFields['roles'] = t('Roles');
    $this->addFieldMapping('roles', 'roles');

    // Now set some virtual mappings for users.
    $this->addFieldMapping('mail', 'mail')
      ->description('Email field computed from legacy node id.');
    $this->addFieldMapping('pass', 'pass')
      ->description('Password generated randomly');

    // Set UUID.
    $this->addFieldMapping('uuid', 'uuid')
      ->defaultValue('uuid');

    // Set Meta Data.
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
   * Prepare source data.
   *
   * @param object $row
   *   The source data as retrieved from the source database.
   *
   * @return bool
   *   Returns FALSE to skip row.
   */
  public function prepareRow($row) {
    drush_print_r("Migrating Legacy Author node " . $row->nid);
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    // As these are nodes being turned into users the title may exist more than
    // once, but only 1 user can be created. Lets do a quick check to see if
    // the user already exists and if so append a number to his name.
    $row->title = $this->checkUserExists($row->title);
    // Set a dummy email address based on node id.
    $row->mail = $this->setEmail($row);
    // Set a random password.
    $row->pass = user_password();
    // Set the author role.
    $row->roles[] = PENTON_AUTHOR_RID;
    // Set the metadata.

    // Set metadata.
    $metadata = $this->metaData($row->nid);
    if ($metadata['canonical']) {
      $row->metadata_canonical = $metadata['canonical'];
    }
    if ($metadata['description']) {
      $row->metadata_description = $metadata['description'];
    }
    return TRUE;
  }

  /**
   * Middle name is stored serialized and then needs some special processing.
   *
   * @param object $account
   *   The user account about to be saved.
   * @param object $row
   *   The source data.
   *
   * @see penton_user_field_attach_presave()
   */
  public function prepare($account, $row) {
    if (isset($row->field_pm_author_middle_name)) {
      $account->field_penton_profile[LANGUAGE_NONE][0]['middle_name'] = $row->field_pm_author_middle_name[0];
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

    return $metadata;
  }

  /**
   * Compute the author's email in the new system.
   *
   * He doesn't have any in the source.
   *
   * @param object $row
   *   The source data as retrieved from the source database.
   *
   * @return string
   *   Computed email address.
   */
  public function setEmail($row) {
    return 'author' . $row->nid . '@penton.invalid';
  }

  /**
   * Check if the user exists already and if so append a number to his name.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param string $name
   *   The legacy user name.
   *
   * @return string
   *   The name, changed or not.
   */
  protected function checkUserExists($name) {
    if (user_load_by_name($name) != FALSE) {
      // So the user already exists.
      // Lets give it another name.
      drupal_set_message(check_plain(t("Duplicate Author found")) . ' ' . $name, 'status');
      $i = 1;
      while (user_load_by_name($name . ' ' . $i) != FALSE) {
        $i++;
      }
      $name = $name . ' ' . $i;
    }
    return $name;
  }

  /**
   * Remove the mapping done by parent node classes.
   */
  public function removeNodeFieldMapping() {
    // Remove uid mapping set by the node source migration.
    $this->removeFieldMapping('uid', 'uid');
    // Unmap other unused fields set by node migration.
    $this->removeFieldMapping('changed', 'changed');
    $this->removeFieldMapping('comment', 'comment');
    $this->removeFieldMapping('promote', 'promote');
    $this->removeFieldMapping('sticky', 'sticky');
    $this->removeFieldMapping('title', 'title');
    $this->removeFieldMapping('tnid', 'tnid');
    $this->removeFieldMapping('translate', 'translate');
    $no_destination_fields = array(
      'log',
      'pathauto',
      'revision',
      'revision_uid',
    );
    foreach ($no_destination_fields as $source_field) {
      if (isset($this->sourceFields[$source_field])) {
        unset($this->sourceFields[$source_field]);
      }
      if (isset($this->codedFieldMappings[$source_field])) {
        unset($this->codedFieldMappings[$source_field]);
      }
    }
  }

  /**
   * Remove the mapping done by destination user.
   */
  public function removeUserFieldMapping() {
    $this->removeFieldMapping('mail');
    $this->removeFieldMapping('pass');
  }

  /**
   * Make sure we don't create stubs for authors.
   *
   * @param \Migration $migration
   *   Migration calling this method.
   * @param array $source_key
   *   Source id of the object claiming for a stub creation.
   *
   * @return bool
   *   Returns FALSE in our case to skip wrongly addressed stubs.
   *
   * @see Migration::createStubWrapper()
   */
  protected function createStub(Migration $migration, array $source_key) {
    if ($migration->getMachineName() != 'Authors') {
      return FALSE;
    }
  }

}

/**
 * Class PentonBloggerProfileMigration.
 *
 * Please note that this migration does not create entities. They have been
 * migrated by the Users migration, declared as dependency, and will 'only'
 * update the basic fields set by this Users migration with what is included
 * in the attached blogger_profile on legacy.
 */
class PentonBloggerProfileMigration extends PentonAuthorMigration {

  /**
   * Field mapping.
   *
   * @param array $arguments
   *   Array from migration setup.
   */
  public function __construct($arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);

    // In this case the password is already in D7 format.
    $this->destination = new DrupalDestinationUser();

    // Remove some mappings set by parent.
    $this->removeFieldMapping('field_penton_legacy_id', 'nid');

    // Map Node author id to User uid.
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('Users');
  }

  /**
   * Do not override the email and password.
   *
   * @param object $row
   *   The source data as retrieved from the source database.
   *
   * @return bool
   *   Returns FALSE to skip row.
   *
   * @see complete()
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Implementation of Migration::prepare().
   *
   * Make sure we don't override email and password.
   *
   * @param object $account
   *   The user object about to be saved.
   * @param object $row
   *   The source object as prepared during migration.
   *
   * @see complete()
   */
  public function prepare($account, $row) {
    parent::prepare($account, $row);
    $old_account = user_load($account->uid, TRUE);
    // Store pass in $row, for further use in complete().
    $row->pass = $old_account->pass;
    $account->mail = $old_account->mail;
  }

  /**
   * Implementation of Migration::complete().
   *
   * @param object $account
   *   The user account just saved.
   * @param object $row
   *   The source object as prepared during the migration.
   */
  public function complete($account, $row) {
    // The incoming password was encrypted - user_save added an extra round of
    // encryption, we need to replace that with the original encrypted value.
    $account->pass = $row->pass;
    db_update('users')
      ->fields(array('pass' => $account->pass))
      ->condition('uid', $account->uid)
      ->execute();
  }

}
