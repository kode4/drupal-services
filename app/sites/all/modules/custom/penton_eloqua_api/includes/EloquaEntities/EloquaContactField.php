<?php
/**
 * @file
 * Realizes Eloqua contact field class.
 */

/**
 * Class for Eloqua contact field.
 */
class EloquaContactField {

  private $type = 'ContactField';
  private $id;
  private $name;
  private $dataType;
  private $displayType;
  private $internalName;
  private $isReadOnly;

  /**
   * Constructor.
   */
  public function __construct($id, $name, $data_type, $display_type, $internal_name, $is_read_only) {
    $this->id = $id;
    $this->name = $name;
    $this->dataType = $data_type;
    $this->displayType = $display_type;
    $this->internalName = $internal_name;
    $this->isReadOnly = $is_read_only;
  }

  /**
   * Returns field ID.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Returns field name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns field data type.
   */
  public function getDataType() {
    return $this->dataType;
  }

  /**
   * Returns field display type.
   */
  public function getDisplayType() {
    return $this->displayType;
  }

  /**
   * Returns field internal name.
   */
  public function getInternalName() {
    return $this->internalName;
  }

  /**
   * Returns true if field is read only.
   */
  public function isReadOnly() {
    return $this->isReadOnly == 'true';
  }

  /**
   * Fetches internal name by specified field id.
   */
  public static function fetchInternalNameByFieldId($id) {
    $url = '/assets/contact/field/' . $id;
    $raw_field = EloquaEntity::apiClient()->get($url, array('depth' => 'partial'));

    if (EloquaEntity::checkForErrors() || empty($raw_field)) {
      throw new Exception('There is no Contact Field with given id: ' . $id . ' in Eloqua');
    }

    return $raw_field->internalName;
  }

  /**
   * Fetches contact's fields.
   */
  public static function fetchContactFields() {
    $url = '/assets/contact/fields';
    $raw_fields = EloquaEntity::apiClient()->get($url, array('depth' => 'partial'));

    if (EloquaEntity::checkForErrors() || empty($raw_fields)) {
      throw new Exception('There are no Contact Fields in Eloqua');
    }

    $fields = array();
    foreach ($raw_fields->elements as $field) {
      $fields[$field->id] = new EloquaContactField(
        $field->id,
        $field->name,
        $field->dataType,
        $field->displayType,
        $field->internalName,
        $field->isReadOnly
      );
    }
    return $fields;
  }

}
