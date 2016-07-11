<?php
/**
 * @file
 * Handler for Penton user profile address.
 */

$plugin = array(
  'title' => t('Penton user profile addressfield'),
  'format callback' => 'addressfield_format_address_penton_user',
  'type' => 'address',
  'weight' => 100,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_address_penton_user(&$format, $address, $context = array()) {
  if ($context['mode'] == 'form') {
    // Get rid of City and eventually administrative area.
    if (isset($format['locality_block'])) {
      $format['locality_block']['dependent_locality']['#access'] = FALSE;
      $format['locality_block']['locality']['#access'] = FALSE;
      $format['locality_block']['administrative_area']['#access'] = FALSE;
      $format['locality_block']['postal_code']['#access'] = TRUE;
    }
    // Unset AJAX.
    unset($format['country']['#ajax']);
  }
}
