<?php
/**
 * @file
 * Realizes Eloqua form class.
 */

/**
 * Class for Eloqua form.
 */
class EloquaForm {

  private $id;
  private $name;
  private $fields;

  /**
   * Constructor.
   */
  public function __construct($id, $raw_form, $fields = array()) {
    $this->id = $id;
    $this->name = $raw_form->name;
    $this->html_name = $raw_form->htmlName;
    $this->fields = $fields;
  }

  /**
   * Returns form ID.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Returns form name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Returns all form fields.
   */
  public function getFields() {
    return $this->fields;
  }

  /**
   * Fetches form from Eloqua by given ID and returns it.
   */
  public static function fetchEloquaFormById($id) {
    $url = '/assets/form/' . $id;
    $raw_form = EloquaEntity::apiClient()->get($url, array('depth' => 'partial'));

    if (EloquaEntity::checkForErrors() || empty($raw_form)) {
      throw new Exception('There is no form with given id: ' . $id . ' in Eloqua');
    }

    $fields = array();
    foreach ($raw_form->elements as $field) {
      $fields[$field->id] = new EloquaFormField(
        $field->id,
        $field->name,
        $field->dataType,
        $field->displayType,
        $field->htmlName,
        isset($field->createdFromContactFieldId) ? $field->createdFromContactFieldId : 0
      );
    }

    return new EloquaForm($id, $raw_form, $fields);
  }

  /**
   * Fetches all forms from Eloqua and returns it.
   */
  public static function fetchEloquaForms() {
    $url = '/assets/forms';
    $raw_forms = EloquaEntity::apiClient()->get($url);

    if (EloquaEntity::checkForErrors() || empty($raw_forms)) {
      throw new Exception('There are no forms in Eloqua');
    }

    return $raw_forms->elements;
  }

}
