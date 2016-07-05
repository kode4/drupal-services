<?php

/**
 * @file
 * Theme implementation to present profile items (values from user
 * account profile fields or modules).
 *
 * This template is used to loop through and render each field configured
 * for the user's account. It can also be the data from modules. The output is
 * grouped by categories.
 *
 * @see penton_account_fields_category.tpl.php
 *      for the parent markup. Implemented as a definition list by default.
 * @see user-profile.tpl.php
 *      where all items and categories are collected and printed out.
 *
 * Available variables:
 * - $user_profile: Array with field attributes prepared for rendering.
 *
 * @see template_preprocess_penton_account_field()
 */

?>

<div class="a-s-form-nedit">
  <?php if (is_array($user_profile)) : ?>
    <?php if ($user_profile['#field_type'] == 'addressfield') : ?>

    <?php endif; ?>
    <?php print render($user_profile); ?>
  <?php else : ?>
    <?php if (isset(field_info_instance('user', $user_profile, 'user')['label'])) : ?>
      <h3 class="field-label">
        <?php print field_info_instance('user', $user_profile, 'user')['label']; ?>
      </h3>
      <div class="a-s-form-nedit__text">
        <?php print '—'; ?>
      </div>
    <?php endif; ?>
  <?php endif; ?>
</div>
