<?php
/**
 * @file
 * Realizes Eloqua field class.
 */

/**
 * Class for Eloqua field.
 */
class EloquaCustomField {
  public $type = "FieldValue";
  public $id;
  public $value;
  private $name;
  private $internalName;

  /**
   * Constructor.
   */
  public function __construct($id, $value, $name = NULL, $internal_name = NULL) {
    $this->id = $id;
    $this->value = $value;
    $this->name = $name;
    $this->internalName = $internal_name;
  }

  /**
   * Returns name of field.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns internal name of field.
   */
  public function getInternalName() {
    return $this->internalName;
  }

  /**
   * Returns ID of field.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Returns type of field.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Returns value of field.
   */
  public function getValue() {
    return $this->value;
  }

}
