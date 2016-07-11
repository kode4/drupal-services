<?php

/**
 * @file
 * Theme implementation to present profile categories (groups of
 * profile items).
 *
 * Categories are defined when configuring user profile fields for the site.
 * It can also be defined by modules. All profile items for a category will be
 * output through the $profile_items variable.
 *
 * @see penton-account-field.tpl.php
 *      where each profile item is rendered. It is implemented as a definition
 *      list.
 * @see user-profile.tpl.php
 *      where all items and categories are collected and printed out.
 *
 * Available variables:
 * - $title: Category title for the group of items.
 * - $caption: Caption for category
 *   penton-account-field.tpl.php.
 * - $user_profile: Array of profile fields.
 *
 * @see template_preprocess_penton_account_category()
 */

?>

<div class="user-account-category">
  <h3 class="a-s-info-head">
    <?php print $title; ?>
    <?php if (!penton_user_permissions_edit_account_access()) : ?>
      <a href="/penton_modal/ajax/validation/prompt" class="ctools-use-modal ctools-modal-modal-popup-validation-prompt" id="js-acc-sett-my-info-btn-public" rel="nofollow">EDIT</a>
    <?php else : ?>
      <a id="js-acc-sett-my-info-btn-public">EDIT</a>
    <?php endif; ?>
  </h3>
  <p class="edit-note">
    <?php print $caption; ?>
  </p>
  <?php foreach ($fields as $field) : ?>
    <?php if (isset($user_profile[$field])) : ?>
      <?php print theme('penton_account_field', array('user_profile' => $user_profile[$field])); ?>
    <?php else : ?>
      <?php print theme('penton_account_field', array('user_profile' => $field)); ?>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
