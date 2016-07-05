<?php
/**
 * @file
 * Realizes Eloqua form field class.
 */

/**
 * Class for Eloqua field data.
 */
class EloquaFormField {

  private $type = 'FormField';
  private $id;
  private $name;
  private $dataType;
  private $displayType;
  private $htmlName;
  private $createdFromContactFieldId;
  private $contactFieldInternalName;

  /**
   * Constructor.
   */
  public function __construct($id, $name, $data_type, $display_type, $html_name, $created_from_contact_field_id = 0) {
    $this->id = $id;
    $this->name = $name;
    $this->dataType = $data_type;
    $this->displayType = $display_type;
    $this->htmlName = $html_name;
    $this->createdFromContactFieldId = $created_from_contact_field_id;
  }

  /**
   * Returns form contact field ID.
   */
  public function getCreatedFromContactFieldId() {
    return $this->createdFromContactFieldId;
  }

  /**
   * Returns form field data type.
   */
  public function getDataType() {
    return $this->dataType;
  }

  /**
   * Returns form field display type.
   */
  public function getDisplayType() {
    return $this->displayType;
  }

  /**
   * Returns form field HTML name.
   */
  public function getHtmlName() {
    return $this->htmlName;
  }

  /**
   * Returns form field ID.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Returns form field name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns form field type.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Returns contact field inernal name.
   */
  public function getContactFieldInternalName() {
    if (empty($this->createdFromContactFieldId)) {
      return $this->htmlName;
    }

    if (isset($this->contactFieldInternalName)) {
      return $this->contactFieldInternalName;
    }

    $this->contactFieldInternalName = EloquaContactField::fetchInternalNameByFieldId($this->createdFromContactFieldId);
    return $this->contactFieldInternalName;
  }

}
