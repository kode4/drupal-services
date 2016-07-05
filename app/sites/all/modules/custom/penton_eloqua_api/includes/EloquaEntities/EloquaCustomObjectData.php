<?php
/**
 * @file
 * Realizes Eloqua custom object data class.
 */

/**
 * Class for Eloqua custom object data.
 */
class EloquaCustomObjectData {
  public $type = 'CustomObjectData';
  public $contactId;
  public $fieldValues;

  private $objectId;

  /**
   * Constructor.
   */
  public function __construct($object_id, $contact_id, $field_values) {
    $this->objectId = $object_id;
    $this->contactId = $contact_id;
    $this->fieldValues = $field_values;
  }

  /**
   * Updates custom object with specified field values.
   */
  public function setFieldValues($field_values) {
    $this->fieldValues = $field_values;
  }

  /**
   * Returns field id with specified field value.
   */
  public function fetchInstanceIdByFieldValue($internal_field_name, $field_value) {
    $instance = EloquaEntity::apiClient()->get('data/customObject/' . $this->objectId . '/instances', array('search' => $internal_field_name . '=' . $field_value));

    if (empty($instance->elements)) {
      throw new Exception('Error occured while fetching Custom Data Object instance with ' . $internal_field_name . ' = ' . $field_value);
    }

    return $instance->elements[0]->id;

  }

  /**
   * Uploads custom object data to Eloqua.
   */
  public function upload() {
    $uploaded_data = EloquaEntity::apiClient()->post('data/customObject/' . $this->objectId . '/instance', $this);
    if ($this->isDuplicatedRecord($uploaded_data)) {
      return FALSE;
    }
    elseif (EloquaEntity::checkForErrors() || !$this->validateResponseDataObject($uploaded_data)) {
      throw new Exception('Error while populating custom data for ' . $this->contactId);
    }

    return TRUE;
  }

  /**
   * Updates custom object with specified ID by fetching Eloqua.
   */
  public function update($instance_id) {
    $updated_instance = EloquaEntity::apiClient()->put('data/customObject/' . $this->objectId . '/instance/' . $instance_id, $this);

    if (EloquaEntity::checkForErrors() || !$this->validateResponseDataObject($updated_instance)) {
      throw new Exception('Error while populating custom data for ' . $this->contactId);
    }
  }

  /**
   * Leaves only given fields.
   */
  public function passFields(array $allowed_field_ids) {
    foreach ($this->fieldValues as &$custom_field) {
      if (!in_array($custom_field->getId, $allowed_field_ids)) {
        unset($custom_field);
      }
    }
  }

  /**
   * Returns true if data object is valid.
   */
  private function validateResponseDataObject($uploaded_data) {
    if (isset($uploaded_data->type)) {
      return $uploaded_data->type == 'CustomObjectData';
    }

    return FALSE;
  }

  /**
   * Returns true if record is duplicated.
   */
  private function isDuplicatedRecord($uploaded_data) {
    if (is_array($uploaded_data) && isset($uploaded_data[0]->requirement->type)) {
      return $uploaded_data[0]->requirement->type == 'NoDuplicatesRequirement';
    }

    return FALSE;
  }

  /**
   * Returns field internal name.
   */
  public function getFieldInternalName($name) {
    foreach (EloquaEntity::getCachedData('fields') as $custom_field) {
      if ($custom_field->name == $name) {
        return $custom_field->internalName;
      }
    }

    return '';
  }

  /**
   * Returns field ID.
   */
  public function getFieldId($name) {
    foreach (EloquaEntity::getCachedData('fields') as $custom_field) {
      if ($custom_field->name == $name) {
        return $custom_field->id;
      }
    }

    return '';
  }

  /**
   * Returns field value.
   */
  public function getFieldValue($name) {
    foreach ($this->fieldValues as $custom_field) {
      if ($custom_field->getName() == $name) {
        return $custom_field->getValue();
      }
    }

    return '';
  }

}
