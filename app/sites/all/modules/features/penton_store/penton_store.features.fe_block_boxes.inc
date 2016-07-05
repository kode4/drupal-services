<?php
/**
 * @file
 * penton_store.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function penton_store_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Customer Service Info Block';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'info_block';
  $fe_block_boxes->body = '<h3>Have a question?</h3>
<p>If you have any inquiries about <strong>Asset Protection Trusts for Businesses</strong>, please inquire our FAQ section. For additional questions, feel free to call us at 1-800-123-456-7890 or email us at email@domain.com</p>';

  $export['info_block'] = $fe_block_boxes;

  return $export;
}
