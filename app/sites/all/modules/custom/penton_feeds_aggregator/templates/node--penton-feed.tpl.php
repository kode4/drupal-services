<?php
/**
 * @file
 * Feed aggregator node preview template.
 */
?>
  <div class="feed-note">
    Use tabs or link below to import/delete items <br/>

    <?php print l(t('Import'), 'node/' . $node->nid . '/import'); ?> &nbsp;
    <?php print l(t('Delete Items'), 'node/' . $node->nid . '/delete-items'); ?>
  </div>


<?php if (!empty($imported_items_count)) : ?>
  <div class="feed-items-count">
    <?php print $imported_items_count; ?>
  </div>
<?php endif; ?>
<?php if (!empty($imported_items)) : ?>
  <div class="feed-items-table">
    <?php print $imported_items; ?>
  </div>
<?php endif; ?>
<?php if (!empty($imported_items_pager)) : ?>
  <div class="feed-items-pager">
    <?php print $imported_items_pager; ?>
  </div>
<?php endif; ?>
