<?php
/**
 * @file
 * Implements registration record.
 */

/**
 * Registration record.
 */
class ContentPillarRegistrationRecord {

  public $uniqueID;
  public $emailAddress;
  public $subscriptionSource;
  public $subscriptionName;
  public $subscriptionLongName;
  public $optInDateOriginal;
  public $optInDateMostRecent;
  public $thirdPartyMostRecentDate;

  /**
   * Constructor.
   */
  public function __construct($unique_id, $email_address, $subscription_source, $subscription_name, $subscription_long_name, $opt_in_date_original) {
    $this->uniqueID = $unique_id;
    $this->emailAddress = $email_address;
    $this->subscriptionSource = $subscription_source;
    $this->subscriptionName = $subscription_name;
    $this->subscriptionLongName = $subscription_long_name;
    $this->optInDateOriginal = $opt_in_date_original;
    $this->optInDateMostRecent = $opt_in_date_original;
  }

  /**
   * Returns mapping.
   */
  public static function getMapping() {
    return array(
      'Unique ID' => 'uniqueID',
      'Email Address' => 'emailAddress',
      'Subscription Source' => 'subscriptionSource',
      'Subscription Name (Code)' => 'subscriptionName',
      'Subscription Long Name (Optional)' => 'subscriptionLongName',
      'Opt-In Date - Original' => 'optInDateOriginal',
      'Opt-In Date - Most Recent' => 'optInDateMostRecent',
      '3rd Party Most Recent Date' => 'thirdPartyMostRecentDate',
    );
  }

  /**
   * Returns unique ID field name.
   */
  public static function getUniqueIdFieldName() {
    return 'Unique ID';
  }

  /**
   * Returns most recent field name.
   */
  public static function getOptInDateMostRecentFieldName() {
    return 'Opt-In Date - Most Recent';
  }

}
