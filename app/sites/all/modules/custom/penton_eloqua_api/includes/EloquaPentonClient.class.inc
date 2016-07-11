<?php
/**
 * @file
 * Realizes Eloqua API client.
 */

foreach (glob(drupal_get_path('module', 'penton_eloqua_api') . "/includes/*/*.php") as $file) {
  require_once $file;
}

/**
 * Client for Eloqua API interaction.
 */
class EloquaPentonClient {

  private static $apiClient;

  /**
   * Constructor.
   */
  public function __construct(EloquaCredentials $credentials) {
    if (!isset(self::$apiClient)) {
      self::$apiClient = new EloquaRESTClient(
        $credentials->getEloquaUsername(),
        $credentials->getEloquaPassword(),
        $credentials->getEloquaBaseURL()
      );

      EloquaEntity::initialize(self::$apiClient);
    }
  }

  /**
   * Subscribes user to email group.
   */
  public function subscribeUserToEmailGroup($user_email_address, $eloqua_email_group_id) {
    $eloqua_contact_id = $this->getEloquaContactId($user_email_address);
    $this->subscribeContactToEmailGroup($eloqua_contact_id, $eloqua_email_group_id);
  }

  /**
   * Subscribes contact to email group.
   */
  private function subscribeContactToEmailGroup($eloqua_contact_id, $eloqua_email_group_id) {
    $eloqua_contact_email_subscription = $this->fetchEloquaContactEmailSubscription($eloqua_contact_id, $eloqua_email_group_id);
    $eloqua_contact_email_subscription->subscribe();
  }

  /**
   * Returns contact ID.
   */
  private function getEloquaContactId($email_address) {
    $contact_id = $this->getContactIdByEmail($email_address);
    if (empty($contact_id)) {
      $contact = $this->createBasicContact($email_address);
      $contact_id = $contact->getId();
    }

    return $contact_id;
  }

  /**
   * Creates contact.
   */
  private function createBasicContact($user_email_address) {
    $contact_to_create = new EloquaContact(array('emailAddress' => $user_email_address));
    $eloqua_contact = $contact_to_create->upload();

    return $eloqua_contact;
  }

  /**
   * Returns contact id by given email.
   */
  private function getContactIdByEmail($email_address) {
    $contact_id = EloquaContact::fetchContactIdByEmail($email_address);

    if (!EloquaEntity::checkForErrors() && !empty($contact_id)) {
      return $contact_id;
    }

    return FALSE;
  }

  /**
   * Returns contact email subscription.
   */
  private function fetchEloquaContactEmailSubscription($eloqua_contact_id, $eloqua_email_group_id) {
    $eloqua_contact_email_subscription = EloquaContactEmailSubscription::fetch($eloqua_contact_id, $eloqua_email_group_id);
    return $eloqua_contact_email_subscription;
  }

  /**
   * Creates custom object.
   */
  public function uploadCustomObjectDataRecord($eloqua_custom_object_name, ContentPillarRegistrationRecord $content_pillar_reg_data) {
    $custom_object = $this->fetchCustomObject($eloqua_custom_object_name);
    $custom_object_data = $this->prepareCustomObjectDataToUpload($custom_object, $content_pillar_reg_data);
    if (!$custom_object_data->upload()) {
      $this->updateCustomObjectDataRecord($custom_object_data);
    }
  }

  /**
   * Updates custom object.
   */
  private function updateCustomObjectDataRecord(EloquaCustomObjectData $custom_object_data) {
    $instance_id = $this->getCustomInstanceIdToUpdate($custom_object_data);
    $custom_object_data = $this->prepareCustomObjectDataToUpdate($custom_object_data);
    $custom_object_data->update($instance_id);
  }

  /**
   * Returns instance id of given custom object.
   */
  private function getCustomInstanceIdToUpdate(EloquaCustomObjectData $custom_object_data) {
    $internal_unique_id_field_name = $custom_object_data->getFieldInternalName(ContentPillarRegistrationRecord::getUniqueIdFieldName());
    $unique_id_field_value = $custom_object_data->getFieldValue(ContentPillarRegistrationRecord::getUniqueIdFieldName());
    $instance_id = $custom_object_data->fetchInstanceIdByFieldValue($internal_unique_id_field_name, $unique_id_field_value);

    return $instance_id;
  }

  /**
   * Prepares custem object for update.
   */
  private function prepareCustomObjectDataToUpdate(EloquaCustomObjectData $custom_object_data) {
    $opt_in_most_recent_field_id = $custom_object_data->getFieldId(ContentPillarRegistrationRecord::getOptInDateMostRecentFieldName());
    $custom_object_data->setFieldValues(array(new EloquaCustomField($opt_in_most_recent_field_id, time())));

    return $custom_object_data;
  }

  /**
   * Returns custom object.
   */
  private function fetchCustomObject($eloqua_custom_object_name) {
    $eloqua_custom_object = $this->getCachedCustomObject($eloqua_custom_object_name);
    if (!empty($eloqua_custom_object)) {
      $eloqua_custom_object->setCachedFields();
      return $eloqua_custom_object;
    }

    $eloqua_custom_object = EloquaCustomObject::fetch($eloqua_custom_object_name);
    $this->saveCachedCustomObject($eloqua_custom_object);
    return $eloqua_custom_object;
  }

  /**
   * Caches custom object and puts it into variable.
   */
  private function saveCachedCustomObject($eloqua_custom_object) {
    $cached_fields = unserialize(variable_get('penton_eloqua_api_cached_cdo', ''));
    $eloqua_username = variable_get('penton_eloqua_api_username', '');

    $cached_fields[$eloqua_username] = $eloqua_custom_object;

    variable_set('penton_eloqua_api_cached_cdo', serialize($cached_fields));

  }

  /**
   * Returns cached custom object from variable.
   */
  private function getCachedCustomObject($eloqua_custom_object_name) {
    $cached_objects = unserialize(variable_get('penton_eloqua_api_cached_cdo', ''));
    $eloqua_username = variable_get('penton_eloqua_api_username', '');

    if (isset($cached_objects[$eloqua_username]) && $cached_objects[$eloqua_username]->name == $eloqua_custom_object_name) {
      return $cached_objects[$eloqua_username];
    }

    return array();
  }

  /**
   * Prepares custom object for upload.
   */
  private function prepareCustomObjectDataToUpload(EloquaCustomObject $custom_data_object, ContentPillarRegistrationRecord $content_pillar_registration_data) {
    $eloqua_contact_id = $this->getEloquaContactId($content_pillar_registration_data->emailAddress);
    $field_values = $this->mapCDOFieldsandPrepareData($content_pillar_registration_data, $custom_data_object);
    return new EloquaCustomObjectData($custom_data_object->id, $eloqua_contact_id, $field_values);
  }

  /**
   * Maps custom object fields and prepares it for upload.
   */
  private function mapCDOFieldsandPrepareData(ContentPillarRegistrationRecord $content_pillar_registration_data, EloquaCustomObject $custom_object) {
    $config = $content_pillar_registration_data->getMapping();

    $field_values = array();
    foreach ($custom_object->fields as $field) {
      $id = $field->id;
      $mapped_field = $config[$field->name];
      $internal_name = $field->internalName;
      $name = $field->name;
      if (!empty($content_pillar_registration_data->$mapped_field)) {
        $value = $content_pillar_registration_data->$mapped_field;
        $field_values[] = new EloquaCustomField($id, $value, $name, $internal_name);
      }
    }

    return $field_values;
  }

  /**
   * Creates register record.
   */
  public function createRegistrationRecord($user_email_address, $site_registration_source, $subscription_name, $subscription_long_name) {
    $content_pillar_registration_record = new ContentPillarRegistrationRecord(
      $user_email_address . "_" . $subscription_name,
      $user_email_address,
      $site_registration_source,
      $subscription_name,
      $subscription_long_name,
      time()
    );

    return $content_pillar_registration_record;
  }

  /**
   * Returns form with given id.
   */
  public function getEloquaFormById($id) {
    $form = EloquaForm::fetchEloquaFormById($id);
    return $form;
  }

  /**
   * Returns all Eloqua forms.
   */
  public function getAllEloquaForms() {
    $forms = EloquaForm::fetchEloquaForms();
    return $forms;
  }

  /**
   * Returns all contact fields.
   */
  public function getAllContactFields() {
    $fields = EloquaContactField::fetchContactFields();
    return $fields;
  }

  /**
   * Submit form data.
   */
  public function submitFormToEloqua($form_id, $data) {
    $form_data = new EloquaFormData($form_id, $data);
    $form_data->submit();
  }

}
