<?php
/**
 * @file
 * Public author profile template implementation.
 */
?>
<div class="profile-logo" itemscope itemtype="https://schema.org/ImageObject" itemprop="image">
  <img class="profile-img" src="<?php print $picture_url; ?>" alt="<?php print $alt; ?>">
  <meta itemprop="url" content="<?php print $picture_url; ?>">
  <?php if (!empty($picture_url_size)): ?>
    <meta itemprop="width" content="<?php print $picture_url_size['width']; ?>">
    <meta itemprop="height" content="<?php print $picture_url_size['height']; ?>">
  <?php endif; ?>

  <?php if (isset($program)): ?>
    <div class="profile-program">
      <?php print $program; ?>
    </div>
  <?php endif; ?>
</div>
<div class="profile-heading">
  <?php if ($user_data): ?>
    <h1 itemprop="name"><?php print $user_data; ?></h1>
  <?php endif; ?>
  <?php if (!empty($user_organisation)): ?>
    <h3><?php print $user_organisation; ?></h3>
  <?php endif; ?>
</div>
<div class="profile-summary">
  <?php if ($field_penton_summary): ?>
    <?php print check_markup($field_penton_summary[0]['value'], $field_penton_summary[0]['format']); ?>
  <?php endif; ?>
  <p>
    <?php if ($field_penton_twitter_account): ?>
      <a href="<?php print check_plain($field_penton_twitter_account[0]['value']); ?>"><?php print check_plain($field_penton_twitter_account[0]['value']); ?></a>
    <?php endif; ?>
    <?php if ($field_penton_secondary_email): ?>
      <a href="mailto:<?php print check_plain($field_penton_secondary_email[0]['email']); ?>" itemprop="email"><?php print check_plain($field_penton_secondary_email[0]['email']); ?></a>
    <?php endif; ?>
    <?php if ($field_penton_site_link): ?>
      <?php foreach ($field_penton_site_link as $link): ?>
        <a href="<?php print check_plain($link['url']); ?>"><?php print check_plain($link['title']); ?></a>
      <?php endforeach; ?>
    <?php endif; ?>
  </p>
  <?php if ($field_penton_marketing_tagline): ?>
    <p><?php print check_plain($field_penton_marketing_tagline[0]['value']); ?></p>
  <?php endif; ?>
</div>
<?php if (isset($author_articles)): ?>
  <div class="profile-recent-activity">
    <?php if ($field_penton_profile[0]['first_name']): ?>
      <h4 class="heading-underline"><?php print check_plain($field_penton_profile[0]['first_name']) . t('’s Recent activity'); ?></h4>
    <?php endif; ?>
    <div class="activity-container">
      <div class="profile-second-article clearfix">
        <div class="profile-second-article__child">
          <?php
            $first_articles = array_splice($author_articles, 0, 2);
            foreach ($first_articles as $article):
                $n = node_view($article, 'teaser');
                print drupal_render($n);
            endforeach;
          ?>
        </div>
        <div class="dfp-ad-hideempty profile-banner">
          <div class="profile-banner-inner" data-dfp-position="jumbotron"></div>
        </div>
      </div>

      <div class="js-lazy-pager-wrapper">
        <?php print theme('penton_author_articles', array('author_articles' => $author_articles)); ?>
      </div>
    </div>
  </div>
<?php endif; ?>
