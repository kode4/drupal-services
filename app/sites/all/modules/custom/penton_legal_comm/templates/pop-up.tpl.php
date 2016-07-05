<?php
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $legal_comm_data with array legal communication message
 *
 * @ingroup templates
 */
?><div class="alert js-legal-comm-message-pop-up" style="display: none;" data-penton-legal-comm-nid="<?php echo $legal_comm_data['nid']; ?>">
  <div class="js-legal-comm-message-title">
    <?php echo $legal_comm_data['title']; ?>
  </div>
  <div class="js-legal-comm-message-description">
    <div class="legal-comm-message-description">
      <?php echo $legal_comm_data['description']; ?>
    </div>
    <a href="#" class="legal-comm-btn close-alert-btn js-legal-comm-message-agree"><?php echo t('Agree'); ?></a>
  </div>
</div>
