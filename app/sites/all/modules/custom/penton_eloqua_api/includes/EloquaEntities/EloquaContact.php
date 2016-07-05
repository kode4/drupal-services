<?php
/**
 * @file
 * Realizes Eloqua contact class.
 */

/**
 * Class for Eloqua contact.
 */
class EloquaContact {

  public $emailAddress;
  public $id = '-500002';
  public $type = 'Contact';

  /**
   * Constructor.
   */
  public function __construct($raw_contact) {
    foreach ($raw_contact as $key => $value) {
      $this->$key = $value;
    }
  }

  /**
   * Returns contact id with specified email.
   */
  public static function fetchContactIdByEmail($email_address) {
    $cached_contact_id = EloquaEntity::getCachedData('contactId');
    if ($cached_contact_id && EloquaEntity::getCachedData('emailAddress') == $email_address) {
      return $cached_contact_id;
    }

    $raw_contact_data = EloquaEntity::apiClient()->get('data/contacts', array('search' => 'emailAddress="' . $email_address . '"'));

    $contact_id = FALSE;
    if (isset($raw_contact_data->elements[0]->id)) {
      $contact_id = $raw_contact_data->elements[0]->id;

      EloquaEntity::setCachedData('contactId', $contact_id);
      EloquaEntity::setCachedData('emailAddress', $email_address);
    }

    return $contact_id;
  }

  /**
   * Uploads contact to Eloqua.
   */
  public function upload() {
    $contact = EloquaEntity::apiClient()->post('data/contact', $this);
    if (EloquaEntity::checkForErrors() ||  empty($contact->id)) {
      throw new Exception("Some problems occured while uploading new contact with '" . $this->emailAddress . "' email address to Eloqua");
    }

    EloquaEntity::setCachedData('contactId', $contact->id);
    EloquaEntity::setCachedData('emailAddress', $contact->emailAddress);

    return new EloquaContact($contact);
  }

  /**
   * Returns contact id.
   */
  public function getId() {
    return $this->id;
  }

}
