<?php
/**
 * @file
 * Realizes Eloqua form data class.
 */

/**
 * Class for Eloqua form data.
 */
class EloquaFormData {
  public $id;
  public $fieldValues;

  /**
   * Constructor.
   */
  public function __construct($id, $field_values) {
    $this->id = $id;
    $this->fieldValues = array();
    foreach ($field_values as $id => $field_value) {
      $this->fieldValues[] = new EloquaCustomField($id, $field_value);
    }
  }

  /**
   * Returns form data ID.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Returns form data values.
   */
  public function getFieldValues() {
    return $this->getFieldValues();
  }

  /**
   * Submits form.
   */
  public function submit() {
    $url = '/data/form/' . $this->id;
    EloquaEntity::apiClient()->post($url, $this);

    if (EloquaEntity::checkForErrors()) {
      throw new Exception('Error while submitting form to Eloqua');
    }
  }

}
