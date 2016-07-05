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
?><div class="alert js-legal-comm-message <?php print (!empty($legal_comm_data['acknowled'])) ? 'alert-msg_withlinks' : ''; ?>" data-penton-legal-comm-nid="<?php echo $legal_comm_data['nid']; ?>">
  <div class="alert-inner l-content">
    <div class="alert-msg">
      <span class="js-legal-comm-text">
        <strong><?php echo $legal_comm_data['title']; ?>:&nbsp;</strong><?php echo $legal_comm_data['description']; ?>
      </span>
      <br/><br/>
    </div>
    <div class="alert-controls">
      <span class="js-legal-comm-trigger-three-dotted" style="display: none;">&nbsp;...</span>
      <a href="#" class="close-alert-btn js-legal-comm-trigger js-legal-comm-collapse" style="display: none;"><?php echo t('read more'); ?></a>
      <?php if(!empty($legal_comm_data['acknowled'])): ?>
        <a href="#" class="close-alert-btn js-legal-comm-message-agree"><?php echo t('Agree'); ?></a>
        <a href="#" class="close-alert-btn js-legal-comm-message-close"><?php echo t('Not now'); ?></a>
      <?php else: ?>
        <a href="#" class="close-alert-btn btn-close-alert js-legal-comm-message-confirm">X</a>
      <?php endif; ?>
    </div>
  </div>
</div>
