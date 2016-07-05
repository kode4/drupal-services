<?php

/**
 * @file
 * Theme implementation to present ESP Web Servicesprofile.
 *
 * @see user-profile.tpl.php
 *      where all items and categories are collected and printed out.
 *
 * Available variables:
 * - $esp_has_access: If user has access to Premium content.
 * - $esp_status: Status returned by ESP.
 * - $esp_account_number: Account's ESP account number.
 * - $esp_zip code: Account's ESP zip code.
 * - $esp_expire_date: Account's ESP expire date.
 *
 * @see template_preprocess_penton_account_category()
 */

?>

<div class="user-account-category">
  <h3 class="a-s-info-head">
    <?php print t('Link your !pubName subscription to <a href="!websiteURL" class="a-s-info-head__esp">!websiteName</a> for Premium Access.',
      array(
        '!pubName' => variable_get('esp_web_services_label', 'ESP Web Services'),
        '!websiteURL' => url(),
        '!websiteName' => variable_get('site_name', 'Penton'),
      )); ?>
    <a id="js-acc-sett-esp-btn-public">EDIT</a>
  </h3>
  <div class="a-s-form-nedit">
    <h3 class="field-label">
      <?php print t('Status:'); ?>
    </h3>
    <div class="a-s-form-nedit__text">
      <?php print !empty($esp_status) ? $esp_status : '-'; ?>
    </div>
  </div>
  <div class="a-s-form-nedit">
    <h3 class="field-label">
      <?php print t('Account number:'); ?>
    </h3>
    <div class="a-s-form-nedit__text">
      <?php print !empty($esp_account_number) ? $esp_account_number : '-'; ?>
    </div>
  </div>
  <div class="a-s-form-nedit">
    <h3 class="field-label">
      <?php print t('Zip code:'); ?>
    </h3>
    <div class="a-s-form-nedit__text">
      <?php print !empty($esp_zip_code) ? $esp_zip_code : '-'; ?>
    </div>
  </div>
  <?php if (!empty($esp_has_access)) : ?>
    <div class="a-s-form-nedit">
      <h3 class="field-label">
        <?php print t('Expire date:'); ?>
      </h3>
      <div class="a-s-form-nedit__text">
        <?php print !empty($esp_expire_date) ? $esp_expire_date : '-'; ?>
      </div>
    </div>
  <?php endif; ?>
</div>
