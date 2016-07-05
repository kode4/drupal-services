<?php
/**
 * @file
 * User migration.
 */

/**
 * Class UserMigration.
 *
 * Migrate legacy users into Drupal 7.
 */
class PentonUserMigration extends DrupalUser6Migration {
  /**
   * Map fields.
   *
   * More mappings can be found in the prepare method because they are related
   * to data in the $user->data field, serialized, and now becomes as real
   * fields.
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

    $this->setHighwaterField(array(
      'name' => 'access',
      'type' => 'int',
    ));

    // Retain legacy id.
    $this->addFieldMapping('field_penton_legacy_id', 'uid')
      ->description('We have a common field to save the D6 uid');

    // Map all other fields as per content model.
    // Related to address.
    $this->addFieldMapping('field_penton_profile', 'profile_country')
      ->defaultValue('US')
      ->description('Country');
    $this->addFieldMapping('field_penton_profile:first_name', 'profile_fname')
      ->description('First name');
    $this->addFieldMapping('field_penton_profile:last_name', 'profile_lname')
      ->description('Last name');
    $this->addFieldMapping('field_penton_profile:organisation_name', 'profile_company')
      ->description('Company');
    $this->addFieldMapping('field_penton_profile:postal_code', 'profile_zip')
      ->description('Zip code');
    $this->addFieldMapping('field_penton_job_title', 'profile_title')
      ->description('Job title');
    $this->addFieldMapping('field_penton_display_profile', 'profile_display_public')
      ->description('Display profile publicly')
      ->defaultValue(1);
    $this->addFieldMapping('field_penton_degree_credential', 'profile_degree_one')
      ->description('Degree or Credential');
    $this->addFieldMapping('field_penton_university', 'profile_university_one')
      ->description('University or Issuing Authority');
    $this->addFieldMapping('field_penton_additional_degree', 'profile_university_two')
      ->description('Additional Degree / Certification');
    $this->addFieldMapping('field_penton_additional_school', 'profile_degree_two')
      ->description('Additional school / institution');
    $this->addFieldMapping('field_penton_summary', 'profile_summary')
      ->description('Summary');
    $this->addFieldMapping('field_penton_summary:format')->defaultValue('filtered_html');
    $this->addFieldMapping('field_penton_primary_job_role', 'profile_primary_role')
      ->description('Primary Job role');
    $this->addFieldMapping('field_penton_secondary_job_role', 'profile_secondary_role')
      ->description('Secondary Job role');
    $this->addFieldMapping('field_penton_specialities', 'profile_specialties')
      ->description('Specialities');
    $this->addFieldMapping('field_penton_skills', 'profile_skills')
      ->description('Skills');
    $this->addFieldMapping('field_penton_legacy_node_access', 'profile_node_access')
      ->description('Serialized array migrated as is');

    // Map the fields on user specific per site.
    $specific_user_fields = array(
      // Waste360.
      'profile_data1' => 'field_penton_question1',
      'profile_data2' => 'field_penton_question2',
      // Newhope360.
      'profile_primary_business_type' => 'field_penton_question1',
      'profile_content_interested' => 'field_penton_question2',
      // Wealthmanagement.
      'profile_firm_type' => 'field_penton_question1',
      'profile_assets_under_management' => 'field_penton_question2',
      'profile_job_function' => 'field_penton_job_function',
      'profile_retirement_plans' => 'field_penton_retirement_plans',
      'profile_primary_compensation_method' => 'field_penton_primary_comp',
      'profile_years_in_finance' => 'field_penton_years_in_finance',
      'profile_gross_annual_production' => 'field_penton_gross_annual_prod',
      'profile_recommend_products' => 'field_penton_recommend_products',
      'profile_estate_planning' => 'field_penton_estate_planning',
    );
    foreach ($specific_user_fields as $source_field => $destination_field) {
      if (array_key_exists($source_field, $this->sourceFields)) {
        $this->addFieldMapping($destination_field, $source_field);
      }
    }
  }

  /**
   * Define our own query for users.
   *
   * We want it sorted by last access to use this field as highwater.
   * There is no "last update" field, so that's the closest we can get. User
   * might not have updated its profile, but if he didn't login there is no
   * chance he did.
   *
   * @return QueryConditionInterface
   *   Return query.
   */
  protected function query() {
    // Do not attempt to migrate the anonymous and admin user rows.
    $query = Database::getConnection('default', $this->sourceConnection)
      ->select('users', 'u')
      ->fields('u')
      ->condition('u.uid', 1, '>')
      ->orderBy('access');
    return $query;
  }

  /**
   * Prepare data for migration.
   *
   * @param object $row
   *   Data provided by the source.
   *
   * @return bool
   *   False if the $row doesn't exist.
   */
  public function prepareRow($row) {
    drush_print_r("Migrating Legacy user " . $row->uid);
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    if (isset($row->profile_content_interested)) {
      if (unserialize($row->profile_content_interested) != FALSE) {
        $row->profile_content_interested = unserialize($row->profile_content_interested);
      }
    }

    if (isset($row->profile_recommend_products)) {
      if (unserialize($row->profile_recommend_products) != FALSE) {
        $row->profile_recommend_products = unserialize($row->profile_recommend_products);
      }
    }

    if (isset($row->profile_country)) {
      // Source countries are not keyed by ISO codes, let's map this properly.
      require_once DRUPAL_ROOT . '/includes/locale.inc';
      $countries = country_get_list();
      $row->profile_country = array_search($row->profile_country, $countries);
      if ($row->profile_country === FALSE) {
        // Default to US in case no match is found.
        $row->profile_country = 'US';
      }
    }
  }

  /**
   * Manipulate user object before it is saved in the database.
   *
   * @param object $account
   *   The user account about to be saved.
   * @param object $row
   *   The source object after it's been totally prepared.
   */
  public function prepare($account, $row) {
    // Map advantage id.
    // $account->data has been prepared by parent (unseralized).
    if (isset($account->data['advantage_cust_id'])) {
      $account->field_penton_advantage_id[LANGUAGE_NONE][0]['value'] = $account->data['advantage_cust_id'];
    }

    // Get zipcode from $account->data if it exists.
    if (!empty($account->data['zipcode'])) {
      $account->field_penton_profile[LANGUAGE_NONE][0]['postal_code'] = $account->data['zipcode'];
    }

    // Map the secondary email from $account->data if it exists.
    if (!empty($account->data['secondmail']) && !filter_var($account->data['secondmail'], FILTER_VALIDATE_EMAIL) === FALSE) {
      $account->field_penton_secondary_email[LANGUAGE_NONE][0]['email'] = $account->data['secondmail'];
    }
  }

  /**
   * Create a stub for a user if it hasn't been created yet.
   *
   * @param array $migration
   *   The migration definition.
   *
   * @return array|bool
   *   Return the new user ID.
   *
   * @throws \Exception
   *   Exception from parent class.
   *
   * @author James Linnell james.linnell@ixxus.com
   */
  public function createStub(Migration $migration, array $source_id) {
    // Create a new object.
    $rand = mt_rand(1000, 2000000);
    // Just make sure this user doesn't exist.
    while (user_load_by_name('StubUser_' . $rand) != FALSE) {
      $rand = mt_rand(1000, 2000000);
    }
    $user = new stdClass();
    $user->name = 'StubUser_' . $rand;
    $user->mail = 'stubuser_' . $rand . '@penton-stub.com';
    $user->roles[DRUPAL_AUTHENTICATED_RID] = 'authenticated user';

    // Save our Stub.
    user_save($user);
    if (isset($user->uid)) {
      return array($user->uid);
    }
    else {
      return FALSE;
    }
  }

}

/**
 * Migrate user pictures from D6 to D7.
 *
 * Class PentonUserPictureMigration.
 */
class PentonUserPictureMigration extends DrupalPicture6Migration {

  /**
   * Nothing special to do here, just call the base class.
   *
   * Parent class already set a highwater field.
   *
   * @param array $arguments
   *   Defined arguments in migration setup.
   */
  public function __construct(array $arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);
  }

}

/**
 * Class PentonUserRoleMigration.
 */
class PentonUserRoleMigration extends DrupalRole6Migration {

  /**
   * Define role mapping.
   *
   * @param array $arguments
   *   Defined arguments in migration setup.
   */
  public function __construct(array $arguments) {
    // Set connection to legacy.
    include 'connection.inc';
    parent::__construct($arguments);

    $this->roleMappings = array(
      'ESP Web Services' => 'paid premium',
      'ESP Web Services (TE)' => 'paid premium',
      'ESP Web Services (TE|C)' => 'paid premium',
      'ESP Web Services (TE|W)' => 'paid premium',
      'NBJ Subscriber' => 'paid premium',
      'unverified user' => 'unverified',
    );
  }

  /**
   * Ignore deprecated roles.
   *
   * All roles but the mapped ones.
   *
   * @param object $row
   *   The role being migrated.
   *
   * @return bool
   *   Returns FALSE to ignore role.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    if (!empty($row->name) && !array_key_exists($row->name, $this->roleMappings)) {
      return FALSE;
    }
  }

}
