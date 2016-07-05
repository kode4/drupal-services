<?php
/**
 * @file
 * Template for private user account page.
 */
?>
<div class="account-sett-avatar">
  <?php if (isset($avatar)) : ?>
    <img src="<?php print $avatar; ?>"/>
  <?php endif; ?>
  <div class="upload-user-pic">
    <span class="choose-file">upload a new profile picture </span>
  </div>
  <?php if ($no_file) : ?>
    <span class="no-file-chosen">no file chosen</span>
  <?php endif; ?>
</div>
<div class="account-sett-form__inner">
  <div class="account-sidebar__col">
    <?php print render($form['account']['name']); ?>
    <?php print render($form['account']['mail']); ?>
  </div>
  <div class="account-sidebar__col">
    <?php print render($form['field_penton_secondary_email']); ?>
    <?php print render($form['account']['pass']); ?>
    <?php print render($form['account']['current_pass']); ?>
  </div>
  <div class="account-sidebar__col">
    <?php print render($form['field_penton_profile']); ?>
    <?php print render($form['field_penton_profile_country']) ?>
  </div>
  <?php print drupal_render_children($form); ?>
</div>
