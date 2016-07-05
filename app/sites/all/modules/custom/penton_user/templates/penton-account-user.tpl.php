<?php
/**
 * @file
 * Public user profile template implementation.
 */
?>
<div class="profile-logo">
  <img class="profile-img" src="<?php print $picture_url; ?>" alt="<?php print $alt; ?>">
</div>
<div class="profile-heading">
  <?php if ($user_nick_name): ?>
    <h1><?php print $user_nick_name; ?></h1>
  <?php endif; ?>
  <?php if ($user_name): ?>
    <h3><?php print $user_name; ?></h3>
  <?php endif; ?>
  <?php if (!empty($user_data)): ?>
    <h4><?php print $user_data; ?></h4>
  <?php endif; ?>
</div>
<div class="profile-summary">
  <?php if ($field_penton_summary): ?>
    <?php print check_markup($field_penton_summary[0]['value'], $field_penton_summary[0]['format']); ?>
  <?php endif; ?>
  <ul class="skill-set-list">
    <div class="current-roles-set">
      <?php if ($current_roles): ?>
        <li class="skill-set-list__item">
          <h4><?php print t('Current role(s)'); ?></h4>
          <p><?php print $current_roles; ?></p>
        </li>
      <?php endif; ?>
    </div>
    <div class="education-set">
      <?php if ($education): ?>
        <li class="skill-set-list__item">
          <h4><?php print t('Education'); ?></h4>
          <p><?php print $education; ?></p>
        </li>
      <?php endif; ?>
    </div>
    <div class="certification-set">
      <?php if ($certification): ?>
        <li class="skill-set-list__item">
          <h4><?php print t('Certification'); ?></h4>
          <p><?php print $certification; ?></p>
        </li>
      <?php endif; ?>
    </div>
  </ul>
</div>
