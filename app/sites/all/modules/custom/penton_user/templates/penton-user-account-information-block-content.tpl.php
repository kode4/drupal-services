<?php
/**
 * @file
 * Template for private user account page.
 */
?>
<div id="ajax-forms-messages"></div>
<div class="account-sidebar">
  <article id="js-acc-sett-aside" class="account-set-aside">
    <div class="account-sett-avatar">
      <img src="<?php print $avatar; ?>"/>
    </div>
    <div class="account-sett-div">
      <div class="account-sidebar__col">
        <p class="account-form-label">Username:</p>
        <p class="account-sett-div-p2">
          <?php if (!empty($account->name)) : ?>
            <?php print $account->name; ?>
          <?php endif; ?>
        </p>
        <p class="account-form-label">Email address:</p>
        <p class="account-sett-div-p2">
          <?php if (!empty($account->mail)) : ?>
            <?php print $account->mail; ?>
          <?php endif; ?>
        </p>
      </div>
      <div class="account-sidebar__col">
        <?php if (!empty($account->field_penton_secondary_email[LANGUAGE_NONE])) : ?>
          <p class="account-form-label">Secondary Email:</p>
          <p class="account-sett-div-p2">
            <?php print $account->field_penton_secondary_email[LANGUAGE_NONE][0]['email']; ?>
          </p>
        <?php endif; ?>
        <p class="account-form-label">Password:</p>
        <p class="account-sett-div-p2">******</p>
      </div>
      <div class="account-sidebar__col">
        <?php if (!empty($account->field_penton_profile[LANGUAGE_NONE])) : ?>
          <p class="account-form-label">Zip code:</p>
          <p class="account-sett-div-p2">
            <?php if (!empty($account->field_penton_profile[LANGUAGE_NONE][0]['postal_code'])) : ?>
              <?php print $account->field_penton_profile[LANGUAGE_NONE][0]['postal_code']; ?>
            <?php else: ?>
              <?php print '-'; ?>
            <?php endif; ?>
          </p>
        <?php endif; ?>
        <p class="account-form-label">Country:</p>
        <p class="account-sett-div-p2">
          <?php if (!empty($account->field_penton_profile[LANGUAGE_NONE][0]['country'])) : ?>
            <?php print $account->field_penton_profile[LANGUAGE_NONE][0]['country']; ?>
          <?php else : ?>
            <?php print '-'; ?>
          <?php endif; ?>
        </p>
      </div>
      <button id="js-acc-sett-aside-btn"><img
          src="<?php print url(drupal_get_path('theme', 'penton_core_theme')) . '/images/account-setting-aside-icon-btn.png'; ?>"
          alt="">
        <span><?php print t('edit account'); ?></span>
      </button>
  </article>
  <article id="js-acc-sett-aside-no-edit" class="account-set-aside account-settings-d-n">
    <?php print render($user_profile); ?>
  </article>
</div>
