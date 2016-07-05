<?php
/**
 * @file
 * Defines our implementation of the taxonomy resource for services module.
 */

/**
 * Create a new taxonomy term based on submitted values.
 *
 * @param array $term
 *   Array of values for the taxonomy term.
 *
 * @return object|bool
 *   Returns the term object on success (new or updated term), or failed status.
 *
 * @see taxonomy_save_term()
 * @see _taxonomy_term_resource_create()
 */
function _penton_taxonomy_term_resource_create($term) {
  // Adds backwards compatibility with regression fixed in #1083242.
  $term = _services_arg_value($term, 'term');
  $term = (object) $term;

  // Allow use of vocabulary_machine_name.
  if (isset($term->vocabulary_machine_name) && !isset($term->vid)) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
    if (!$vocabulary) {
      return services_error(t('Unknown vocabulary_machine_name @vocabulary_machine_name.', array('@vocabulary_machine_name' => $term->vocabulary_machine_name)), 406);
    }
    $term->vid = $vocabulary->vid;
  }
  $status = taxonomy_term_save($term);
  if ($status == SAVED_NEW || $status == SAVED_UPDATED) {
    return $term;
  }
  else {
    return services_error(t('Could not save term.', 406));
  }
}

/**
 * Update a taxonomy term based on submitted values.
 *
 * @param int $tid
 *   Unique identifier for the taxonomy term to update.
 * @param array $term
 *   Array of values for the taxonomy term.
 *
 * @return object|bool
 *   Status constant indicating if term was inserted or updated.
 *
 * @see taxonomy_save_term()
 */
function _penton_taxonomy_term_resource_update($tid, $term) {
  // Adds backwards compatibility with regression fixed in #1083242.
  $term = _services_arg_value($term, 'term');
  $term = (object) $term;

  // Allow use of vocabulary_machine_name.
  if (isset($term->vocabulary_machine_name) && !isset($term->vid)) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
    if (!$vocabulary) {
      return services_error(t('Unknown vocabulary_machine_name @vocabulary_machine_name.', array('@vocabulary_machine_name' => $term->vocabulary_machine_name)), 406);
    }
    $term->vid = $vocabulary->vid;
  }
  $term->tid = $tid;
  $status = taxonomy_term_save($term);
  if ($status == SAVED_NEW || $status == SAVED_UPDATED) {
    return $term;
  }
  else {
    return services_error(t('Could not save term.', 406));
  }
}

/**
 * Access callback for term creating.
 *
 * @param object $term
 *   A taxonomy term object.
 *
 * @return bool
 *   Boolean whether or not the user has access to create or edit the term.
 *
 * @see _taxonomy_resource_create_access()
 */
function _penton_taxonomy_resource_create_access($term) {
  module_load_include('inc', 'services', 'resources/taxonomy_resource');
  return _taxonomy_resource_create_access($term);
}

/**
 * Access callback for term updating.
 *
 * @param int $tid
 *   Term id.
 * @param array $term
 *   A taxonomy term object.
 *
 * @return bool|mixed
 *   Boolean whether or not the user has access to create or edit the term.
 *
 * @throws \ServicesException
 *   Throws exception if the vocabulary cound't be found.
 */
function _penton_taxonomy_resource_update_access($tid, $term) {
  // Adds backwards compatibility with regression fixed in #1083242.
  $term = _services_arg_value($term, 'term');
  $term = (object) $term;

  // Allow use of vocabulary_machine_name.
  if (isset($term->vocabulary_machine_name) && !isset($term->vid)) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($term->vocabulary_machine_name);
    if (!$vocabulary) {
      return services_error(t('Unknown vocabulary_machine_name @vocabulary_machine_name.', array('@vocabulary_machine_name' => $term->vocabulary_machine_name)), 406);
    }
    $term->vid = $vocabulary->vid;
  }

  return user_access('edit terms in ' . $term->vid) || user_access('administer taxonomy');
}
