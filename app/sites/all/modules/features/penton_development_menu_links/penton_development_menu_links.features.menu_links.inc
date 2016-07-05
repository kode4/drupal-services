<?php
/**
 * @file
 * penton_development_menu_links.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function penton_development_menu_links_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-dropdown-bottom-menu_about-uscontact-us:<front>.
  $menu_links['menu-dropdown-bottom-menu_about-uscontact-us:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'About Us/Contact Us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_about-uscontact-us:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-bottom-menu_advertize:<front>.
  $menu_links['menu-dropdown-bottom-menu_advertize:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Advertize',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_advertize:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-bottom-menu_newsletters:<front>.
  $menu_links['menu-dropdown-bottom-menu_newsletters:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Newsletters',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_newsletters:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-bottom-menu_privacy-policy:<front>.
  $menu_links['menu-dropdown-bottom-menu_privacy-policy:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Privacy Policy',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_privacy-policy:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-bottom-menu_standards:<front>.
  $menu_links['menu-dropdown-bottom-menu_standards:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Standards',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_standards:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-bottom-menu_subscribe:<front>.
  $menu_links['menu-dropdown-bottom-menu_subscribe:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Subscribe',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_subscribe:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-bottom-menu_terms-of-service:<front>.
  $menu_links['menu-dropdown-bottom-menu_terms-of-service:<front>'] = array(
    'menu_name' => 'menu-dropdown-bottom-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Terms of Service',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-bottom-menu_terms-of-service:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_awards:<front>.
  $menu_links['menu-dropdown-top-menu_awards:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Awards',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_awards:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_community:<front>.
  $menu_links['menu-dropdown-top-menu_community:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Community',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_community:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_investment:<front>.
  $menu_links['menu-dropdown-top-menu_investment:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Investment',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_investment:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_managment:<front>.
  $menu_links['menu-dropdown-top-menu_managment:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Managment',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_managment:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_news:<front>.
  $menu_links['menu-dropdown-top-menu_news:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'News',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_news:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_planning:<front>.
  $menu_links['menu-dropdown-top-menu_planning:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Planning',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_planning:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_research:<front>.
  $menu_links['menu-dropdown-top-menu_research:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Research',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_research:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_videos:<front>.
  $menu_links['menu-dropdown-top-menu_videos:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Videos',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_videos:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-dropdown-top-menu_wire:<front>.
  $menu_links['menu-dropdown-top-menu_wire:<front>'] = array(
    'menu_name' => 'menu-dropdown-top-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Wire',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-dropdown-top-menu_wire:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_advertise:<front>.
  $menu_links['menu-footer-menu_advertise:<front>'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Advertise',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_advertise:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 1,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_contact-us:<front>.
  $menu_links['menu-footer-menu_contact-us:<front>'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Contact Us',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_contact-us:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-pillar-navigation_directory:http://change.me/directory.
  $menu_links['menu-pillar-navigation_directory:http://change.me/directory'] = array(
    'menu_name' => 'menu-pillar-navigation',
    'link_path' => 'http://change.me/directory',
    'router_path' => '',
    'link_title' => 'Directory',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-pillar-navigation_directory:http://change.me/directory',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-pillar-navigation_events:http://change.me/events.
  $menu_links['menu-pillar-navigation_events:http://change.me/events'] = array(
    'menu_name' => 'menu-pillar-navigation',
    'link_path' => 'http://change.me/events',
    'router_path' => '',
    'link_title' => 'Events',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-pillar-navigation_events:http://change.me/events',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-pillar-navigation_forums:http://change.me/forum.
  $menu_links['menu-pillar-navigation_forums:http://change.me/forum'] = array(
    'menu_name' => 'menu-pillar-navigation',
    'link_path' => 'http://change.me/forum',
    'router_path' => '',
    'link_title' => 'Forums',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-pillar-navigation_forums:http://change.me/forum',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-pillar-navigation_home:<front>.
  $menu_links['menu-pillar-navigation_home:<front>'] = array(
    'menu_name' => 'menu-pillar-navigation',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-pillar-navigation_home:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-pillar-navigation_university:http://change.me/university.
  $menu_links['menu-pillar-navigation_university:http://change.me/university'] = array(
    'menu_name' => 'menu-pillar-navigation',
    'link_path' => 'http://change.me/university',
    'router_path' => '',
    'link_title' => 'University',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-pillar-navigation_university:http://change.me/university',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-social-links_facebook:https://facebook.com/.
  $menu_links['menu-social-links_facebook:https://facebook.com/'] = array(
    'menu_name' => 'menu-social-links',
    'link_path' => 'https://facebook.com/',
    'router_path' => '',
    'link_title' => 'Facebook',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-social-links_facebook:https://facebook.com/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-social-links_google-plus:https://plus.google.com/.
  $menu_links['menu-social-links_google-plus:https://plus.google.com/'] = array(
    'menu_name' => 'menu-social-links',
    'link_path' => 'https://plus.google.com/',
    'router_path' => '',
    'link_title' => 'Google Plus',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-social-links_google-plus:https://plus.google.com/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-social-links_linkedin:https://www.linkedin.com.
  $menu_links['menu-social-links_linkedin:https://www.linkedin.com'] = array(
    'menu_name' => 'menu-social-links',
    'link_path' => 'https://www.linkedin.com',
    'router_path' => '',
    'link_title' => 'LinkedIn',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-social-links_linkedin:https://www.linkedin.com',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-social-links_rss:<front>.
  $menu_links['menu-social-links_rss:<front>'] = array(
    'menu_name' => 'menu-social-links',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'RSS',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-social-links_rss:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-social-links_twitter:https://twitter.com/.
  $menu_links['menu-social-links_twitter:https://twitter.com/'] = array(
    'menu_name' => 'menu-social-links',
    'link_path' => 'https://twitter.com/',
    'router_path' => '',
    'link_title' => 'Twitter',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-social-links_twitter:https://twitter.com/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-social-links_youtube:https://www.youtube.com/.
  $menu_links['menu-social-links_youtube:https://www.youtube.com/'] = array(
    'menu_name' => 'menu-social-links',
    'link_path' => 'https://www.youtube.com/',
    'router_path' => '',
    'link_title' => 'YouTube',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-social-links_youtube:https://www.youtube.com/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('About Us/Contact Us');
  t('Advertise');
  t('Advertize');
  t('Awards');
  t('Community');
  t('Contact Us');
  t('Directory');
  t('Events');
  t('Facebook');
  t('Forums');
  t('Google Plus');
  t('Home');
  t('Investment');
  t('LinkedIn');
  t('Managment');
  t('News');
  t('Newsletters');
  t('Pillar navigation Test link');
  t('Planning');
  t('Privacy Policy');
  t('RSS');
  t('Research');
  t('Standards');
  t('Subscribe');
  t('Terms of Service');
  t('Twitter');
  t('University');
  t('Videos');
  t('Wire');
  t('YouTube');

  return $menu_links;
}
