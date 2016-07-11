<?php
/**
 * @file
 * Realizes Eloqua custom object class.
 */

/**
 * Class for Eloqua custom object.
 */
class EloquaCustomObject {
  public $type = 'CustomObject';
  public $id;
  public $name;
  public $fields;

  /**
   * Constructor.
   */
  private function __construct($raw_custom_object) {
    foreach ($raw_custom_object as $key => $value) {
      $this->$key = $value;
    }

    $this->setCachedFields();

  }

  /**
   * Sets cached data.
   */
  public function setCachedFields() {
    EloquaEntity::setCachedData('fields', $this->fields);
  }

  /**
   * Fetches cusom object.
   */
  public static function fetch($name) {
    $id = self::getCustomObjectId($name);

    $raw_custom_object = EloquaEntity::apiClient()->get('assets/customObject/' . $id);

    if (EloquaEntity::checkForErrors() || empty($raw_custom_object)) {
      throw new Exception('There is no Custom Data Object with given id: ' . $id . ' in Eloqua');
    }

    return new EloquaCustomObject($raw_custom_object);
  }

  /**
   * Returns custom object id by specified name.
   */
  private static function getCustomObjectId($name) {
    $search_result = EloquaEntity::apiClient()->get('assets/customObjects', array('search' => 'name="' . $name . '"'));
    if (empty($search_result->elements)) {
      throw new Exception('There is no Custom Data Object with given name: ' . $name . ' in Eloqua');
    }

    return $search_result->elements[0]->id;
  }

}
