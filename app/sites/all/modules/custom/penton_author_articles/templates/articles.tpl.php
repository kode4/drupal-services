<?php
/**
 * @file
 * Author articles template implementation.
 */
?>
<?php if ($is_ajax) : ?>
<div class="js-lazy-pager-content">
  <div class="dfp-ad-hideempty">
    <div data-dfp-position="infinitescroll"></div>
  </div>
<?php endif; ?>
  <?php foreach ($author_articles as $article): ?>
    <?php
      $n = node_view($article, 'teaser');
      print drupal_render($n);
      ?>
  <?php endforeach; ?>
  <?php print theme('pager', array('lazy' => TRUE)); ?>
<?php if ($is_ajax) : ?>
  </div>
<?php endif; ?>
