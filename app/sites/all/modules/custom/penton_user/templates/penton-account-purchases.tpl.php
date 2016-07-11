<?php

/**
 * @file
 * Theme implementation to present profile purchases.
 */

?>
<div class="purchased-products">
  <div class="purchases-caption">Your purchases:</div>
  <table class="purchases-table">
    <?php foreach($purchases as $key => $line_item) : ?>
      <tr class="purchased-line">
        <td class="purchased-item">
          <?php print $line_item['link']; ?>
        </td>
        <td class="purchased-date">
          <?php print 'Date Purchased: ' . date("m/d/y", $line_item['granted']); ?>
        </td>
      </tr>
    <?php endforeach; ?>
  </table>
</div>
