<?php
/**
 * @file
 * Penton datasheet insertion/deletion of data in tables or nodes.
 */

/**
 * Create the data table detail node.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param int $pid
 *   The parent ID
 * @param string $title
 *   The title.
 *
 * @return int
 *   The created node ID.
 */
function _penton_datasheet_create_data_table_detail_node($pid, $title) {
  $parent = node_load($pid);
  global $user;

  $node = new stdClass();
  // Node title, tag striping and length reduction introduced due to migration
  // bugs.
  $node->title = substr(strip_tags($title), 0, 511);
  $node->type = 'data_table_detail';
  node_object_prepare($node);
  $node->uid = $user->uid;
  // (1 or 0): published or not.
  $node->status = 1;
  // (1 or 0): promoted to front page.
  $node->promote = 0;
  // 0 = comments disabled, 1 = read only, 2 = read/write.
  $node->comment = 2;
  // Or e.g. 'en' if locale is enabled.
  $node->language = LANGUAGE_NONE;
  $node->book['bid'] = isset($parent->book['bid']) ? $parent->book['bid'] : NULL;
  $node->book['plid'] = isset($parent->book['mlid']) ? $parent->book['mlid'] : NULL;
  $node->book['menu_name'] = isset($parent->book['menu_name']) ? $parent->book['menu_name'] : NULL;
  // Prepare node for saving.
  $node = node_submit($node);
  node_save($node);
  return $node->nid;
}

/**
 * Create the entry into the database.
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param int $pid
 *   The parent ID.
 * @param int $nid
 *   The node ID.
 * @param object $header
 *   The header elements.
 * @param object $data
 *   The table elements.
 *
 * @return bool
 *   Return a boolean.
 */
function _penton_datasheet_create_penton_data_table_entry($pid, $nid, $header, $data) {
  // Insert into the database.
  db_insert('penton_data_table')
    ->fields(array(
      'nid' => $nid,
      'pid' => $pid,
      'header_data' => serialize($header),
      'array_data' => serialize(array($data)),
    ))
    ->execute();
  return TRUE;
}

/**
 * Delete all records before starting but retain parent node..
 *
 * @author James Linnell james.linnell@ixxus.com
 *
 * @param int $pid
 *   The parent ID.
 */
function _penton_datasheet_delete_all($pid) {

  // Get all node IDs including parentID.
  $result = db_select('penton_data_table', 'pdt')
    ->fields('pdt', array('nid'))
    ->condition('pid', $pid, '=')
    ->execute()
    ->fetchAll();

  // Delete from database;
  $delete = db_delete('penton_data_table')
    ->condition('pid', $pid)
    ->execute();

  // Delete all child nodes.
  foreach ($result as $key => $node) {
    if ($node->nid != $pid) {
      node_delete($node->nid);
      $replacements = array('!nid' => $node->nid);
      watchdog("Penton Datasheet", "Node !nid has been deleted.", $replacements, WATCHDOG_INFO);
    }
  }
}
