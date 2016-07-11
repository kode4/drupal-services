<?php
/**
 * @file
 * Pages callbacks for the penton_modal module.
 */

/**
 * Callback function for the register functionality.
 *
 * @param bool $js
 *   If client supports javascript.
 * @param string $advanced
 *   Advanced questions are required.
 * @param string $step
 *   It is a multi-step form, this callback will be used for each step.
 */
function penton_modal_advanced_register_wizard($js = NULL, $advanced = NULL, $step = NULL) {
  if (is_null($advanced)) {
    $advanced = 'basic';
  }
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');

    // Set the cache key in session.
    // CTools cache key defaults to session_id() which changes when user
    // registers so we need to define our own key system.
    $cache_key = penton_modal_set_cache_key();

    // Define our multi-step form. Cancel skips the registration step.
    $form_info = array(
      'id' => 'penton_modal_register',
      'path' => "penton_modal/" . ($js ? 'ajax' : 'nojs') . "/register/{$advanced}/%step",
      'show cancel' => FALSE,
      'show trail' => FALSE,
      'next text' => t('Register'),
      'finish text' => t('Return to site'),
      'next callback' => 'penton_modal_wizard_next',
      'finish callback' => 'penton_modal_wizard_finish',
      // This controls order, as well as form labels.
      'order' => array(
        'register' => t('Register for a free membership'),
        'newsletter' => t('Stay informed'),
        'tkli' => t('Third-Party Offers'),
        'thank_you' => NULL,
      ),
      // Map step to form id.
      'forms' => array(
        'register' => array(
          'form id' => 'penton_user_register_advanced_form',
          'title' => t('Register for a free membership'),
        ),
        'newsletter' => array(
          'form id' => 'penton_newsletter_manager_newsletters_subscribe_form_full',
          'title' => t('Stay informed') . '<p>' . t('Subscribe to our most popular newsletters.') . '</p>',
        ),
        'tkli' => array(
          'form id' => 'penton_tkli_form',
          'title' => t('Third-Party Offers'),
        ),
        'thank_you' => array(
          'form id' => 'penton_user_register_thank_you_form',
          'title' => t('Thank you for registering!'),
        ),
      ),
    );
    if (!penton_newsletter_manager_have_not_promoted_newsletters()) {
      unset($form_info['order']['newsletter'], $form_info['forms']['newsletter']);
    }
    if (empty(variable_get('penton_tkli_enable', TRUE))) {
      unset($form_info['order']['tkli'], $form_info['forms']['tkli']);
    }

    // We're not using any real storage here, so we're going to set our
    // object_id to 1. When using wizard forms, id management turns
    // out to be one of the hardest parts. Editing an object with an id
    // is easy, but new objects don't usually have ids until somewhere
    // in creation.
    // We skip all this here by just using an id of 1.
    $object = penton_modal_return_object($object_id = 1, $step, $cache_key);
    $form_state = array(
      'ajax' => $js,
      'object_id' => $object_id,
      'sid' => $cache_key,
      'object' => &$object,
    );
    if ($advanced == 'advanced') {
      $form_state['upgrading'] = TRUE;
    }
    ctools_include('wizard');
    $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
    $output = drupal_render($form);

    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // If form completed, reload page.
      $commands[] = ctools_ajax_command_reload();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    if (!is_null($step)) {
      if ($step == 'register') {
        penton_modal_dtm_commands_after_register($commands, 'ADVANCED_REGISTRATION_STEP_1', !empty($form_state['input']['subscribe']), 'advanced');
      }
      elseif ($step == 'newsletter') {
        $commands[] = penton_modal_dtm_commands_fire_rule('ADVANCED_REGISTRATION_STEP_2');
        if (!empty($form_state['input']['subscribe'])) {
          $newsletters = array_filter($form_state['input']['subscribe']);
          if (!empty($newsletters)) {
            $commands[] = penton_modal_dtm_commands_fire_rule('NEWSLETTER_OPTIONS_SELECTED');
          }
        }
      }
      elseif ($step == 'tkli') {
        $commands[] = penton_modal_dtm_commands_fire_rule('ADVANCED_REGISTRATION_STEP_3');
      }
      elseif ($step == 'thank_you') {
        $commands[] = penton_modal_dtm_commands_fire_rule('ADVANCED_REGISTRATION_STEP_4');
      }
    }
    else {
      $commands[] = penton_modal_dtm_commands_fire_rule('ADVANCED_REGISTRATION_INITIATED');
      $commands[] = penton_modal_dtm_commands_add_regtype_event('advanced');
    }
    print ajax_render($commands);
  }
  else {
    drupal_goto('user/register');
  }
}

/**
 * Callback function for the basic register functionality.
 *
 * @param bool $js
 *   If client supports javascript.
 * @param string $step
 *   It is a multi-step form, this callback will be used for each step.
 */
function penton_modal_basic_register_wizard($js = NULL, $step = NULL) {
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');

    // Set the cache key in session.
    // CTools cache key defaults to session_id() which changes when user
    // registers so we need to define our own key system.
    $cache_key = penton_modal_set_cache_key();

    // Define our multi-step form. Cancel skips the registration step.
    $form_info = array(
      'id' => 'penton_modal_basic_register',
      'path' => "penton_modal/" . ($js ? 'ajax' : 'nojs') . "/basic_register/%step",
      'show cancel' => FALSE,
      'show trail' => FALSE,
      'next text' => t('Register'),
      'finish text' => t('Return to site'),
      'finish callback' => 'penton_modal_wizard_finish',
      // This controls order, as well as form labels.
      'order' => array(
        'register' => t('Register now'),
        'thank_you' => NULL,
      ),
      // Map step to form id.
      'forms' => array(
        'register' => array(
          'form id' => 'penton_user_register_basic_form',
          'title' => t('Register now'),
        ),
        'thank_you' => array(
          'form id' => 'penton_user_register_thank_you_form',
          'title' => t('Thank you for registering!'),
        ),
      ),
    );

    // We're not using any real storage here, so we're going to set our
    // object_id to 1. When using wizard forms, id management turns
    // out to be one of the hardest parts. Editing an object with an id
    // is easy, but new objects don't usually have ids until somewhere
    // in creation.
    // We skip all this here by just using an id of 1.
    $object = penton_modal_return_object($object_id = 1, $step, $cache_key);
    $form_state = array(
      'ajax' => $js,
      'object_id' => $object_id,
      'sid' => $cache_key,
      'object' => &$object,
    );
    ctools_include('wizard');
    $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
    $output = drupal_render($form);

    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // If form completed, reload page.
      $commands[] = ctools_ajax_command_reload();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    if (!is_null($step) && $step == 'register') {
      penton_modal_dtm_commands_after_register($commands, 'BASIC_REGISTRATION_STEP_1', !empty($form_state['input']['subscribe']));
    }
    elseif (is_null($step)) {
      $commands[] = penton_modal_dtm_commands_fire_rule('BASIC_REGISTRATION_INITIATED');
      $commands[] = penton_modal_dtm_commands_add_regtype_event();
    }
    print ajax_render($commands);
  }
  else {
    drupal_goto('user/register');
  }
}


/**
 * Callback function for the forward functionality with optional registration.
 *
 * @param bool $js
 *   If client supports javascript.
 * @param int $nid
 *   The node id of the page about to be forwarded.
 * @param string $step
 *   It is a multi-step form, this callback will be used for each step.
 *
 * @return string
 *   Returns the string to be rendered either via a modal or a page.
 */
function penton_modal_forward_wizard($js = NULL, $nid = NULL, $reload = NULL, $step = NULL) {
  if (is_null($reload)) {
    $reload = 0;
  }
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');
  }
  // Set the cache key in session.
  // CTools cache key defaults to session_id() which changes when user registers
  // so we need to define our own key system.
  $cache_key = penton_modal_set_cache_key();
  // Define our multi-step form. Cancel skips the registration step.
  $form_info = array(
    'id' => 'penton_modal_forward',
    'path' => "penton_modal/" . ($js ? 'ajax' : 'nojs') . "/forward/{$nid}/{$reload}/%step",
    'show cancel' => FALSE,
    'show trail' => FALSE,
    'next text' => t('Register and send'),
    'next callback' => 'penton_modal_wizard_next',
    'finish callback' => 'penton_modal_wizard_finish',
    // This controls order, as well as form labels.
    'order' => array(
      'register'   => t('Email this article'),
      'thank_you'  => NULL,
    ),
    // Map step to form id.
    'forms' => array(
      'register' => array(
        'form id' => 'penton_user_register_email_this_form',
        'title' => t('Email this article'),
      ),
      'thank_you' => array(
        'form id' => 'penton_user_register_email_thank_you_form',
        'title' => t('Your message has been sent'),
      ),
    ),
  );
  // Cache for the forward functionality only.
  $object = penton_modal_return_object($object_id = 'forward', $step, $cache_key);
  $form_state = array(
    'ajax' => $js,
    'object_id' => $object_id,
    'sid' => $cache_key,
    'object' => &$object,
    'forward_nid' => $nid,
  );
  if (!empty($reload)) {
    $form_state['reload_after_close'] = TRUE;
  }
  ctools_include('wizard');
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
  $output = drupal_render($form);
  $confirmation = t('Thank you.');
  if ($output === FALSE || !empty($form_state['complete'])) {
    // Prepare confirmation message.
    $messages = drupal_get_messages('status');
    if (!empty($messages['status'])) {
      $confirmation = reset($messages['status']);
    }
  }
  if ($js) {
    // If javascript is active, we have to use a render array.
    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // Print confirmation message.
      $commands[] = ajax_command_html('#modal-content', $confirmation);
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    if (!is_null($step) && $step == 'register' && isset($form_state['input']['mail'])) {
      penton_modal_dtm_commands_after_register($commands, 'BASIC_REGISTRATION_STEP_1', !empty($form_state['input']['subscribe']));
    }
    elseif (is_null($step)) {
      $commands[] = penton_modal_dtm_commands_fire_rule('BASIC_REGISTRATION_INITIATED');
      $commands[] = penton_modal_dtm_commands_add_regtype_event();
    }
    print ajax_render($commands);
    exit;
  }
  else {
    if ($output === FALSE || !empty($form_state['complete'])) {
      return $confirmation;
    }
    else {
      return $output;
    }
  }
}

/**
 * Callback function for the print functionality with optional registration.
 *
 * @param bool $js
 *   If client supports javascript.
 * @param int $nid
 *   The node id of the page about to be printed.
 * @param string $step
 *   It is a multi-step form, this callback will be used for each step.
 *
 * @return string
 *   Returns the string to be rendered either via a modal or a page.
 */
function penton_modal_print_wizard($js = NULL, $nid = NULL, $step = NULL) {
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');
    ctools_add_js('ajax-responder');
  }
  // Set the cache key in session.
  // CTools cache key defaults to session_id() which changes when user registers
  // so we need to define our own key system.
  $cache_key = penton_modal_set_cache_key();
  // Define our multistep form. Cancel skips the registration step.
  $form_info = array(
    'id' => 'penton_modal_print',
    'path' => "penton_modal/" . ($js ? 'ajax' : 'nojs') . "/print/{$nid}/%step",
    'show cancel' => FALSE,
    'show trail' => FALSE,
    'next text' => t('Register and print'),
    'finish text' => t('Print article now'),
    'next callback' => 'penton_modal_wizard_next',
    'finish callback' => 'penton_modal_wizard_finish',
    // This controls order, as well as form labels.
    'order' => array(
      'register' => t('Print this article'),
      'thank_you' => NULL,
    ),
    // Map step to form id.
    'forms' => array(
      'register' => array(
        'form id' => 'penton_user_register_basic_form',
        'title' => t('Print this article'),
      ),
      'thank_you' => array(
        'form id' => 'penton_user_register_thank_you_form',
        'title' => t('Thank you for registering!'),
      ),
    ),
  );
  // Cache for the print functionality only.
  $object = penton_modal_return_object($object_id = 'print', $step, $cache_key);
  if ($object == new stdClass()) {
    // Populate our object if it's empty. All we need is the print path.
    // Defaults to homepage redirect if print path can't be found.
    $object->path = $nid ? 'print/' . $nid : 'node';
    penton_modal_cache_set($object_id, $object, $cache_key);
  }
  $form_state = array(
    'ajax' => $js,
    'object_id' => $object_id,
    'sid' => $cache_key,
    'object' => &$object,
    'action' => 'print',
    'print_nid' => $nid,
    'hide_edit_profile_link' => TRUE,
  );
  ctools_include('wizard');
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
  $output = drupal_render($form);
  if ($js) {
    // If javascript is active, we have to use a render array.
    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // Go to the print version of page.
      $commands[] = ctools_modal_command_dismiss();
      $commands[] = ctools_ajax_command_redirect($object->path);
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    if (!is_null($step) && $step == 'register') {
      penton_modal_dtm_commands_after_register($commands, 'BASIC_REGISTRATION_STEP_1', !empty($form_state['input']['subscribe']));
    }
    elseif (is_null($step)) {
      $commands[] = penton_modal_dtm_commands_fire_rule('BASIC_REGISTRATION_INITIATED');
      $commands[] = penton_modal_dtm_commands_add_regtype_event();
    }
    print ajax_render($commands);
    exit;
  }
  else {
    if ($output === FALSE || !empty($form_state['complete'])) {
      drupal_goto($object->path);
    }
    else {
      return $output;
    }
  }
}

/**
 * A modal user login callback.
 *
 * @param bool $js
 *   If client supports javascript.
 *
 * @return string
 *   Returns the string to be rendered either via a modal or a page.
 */
function penton_modal_login($js = NULL, $reload = FALSE) {
  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('user_login');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'ajax' => TRUE,
  );
  $options = drupal_parse_url($_GET['destination']);
  if (user_is_logged_in()) {
    $output[] = ctools_ajax_command_redirect($options['path'], $options);
    print ajax_render($output);
    return;
  }
  if (!empty($reload)) {
    $form_state['reload_after_close'] = TRUE;
  }

  $output = ctools_modal_form_wrapper('user_login', $form_state);
  if (!empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    $output = array();
    ctools_add_js('ajax-responder');
    $output[] = penton_modal_dtm_commands_fire_rule('USER_LOGIN');
    $output[] = ctools_modal_command_dismiss(t('Login success'));
    if (isset($_GET['destination'])) {
      $output[] = ctools_ajax_command_redirect($options['path'], $options);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  print ajax_render($output);
}

/**
 * A modal user password callback.
 *
 * @param bool $js
 *   If client supports javascript.
 *
 * @return string
 *   Returns the string to be rendered either via a modal or a page.
 */
function penton_modal_password($js = NULL) {
  module_load_include('inc', 'user', 'user.pages');

  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('user_pass');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state = array(
    'ajax' => TRUE,
  );
  $output = ctools_modal_form_wrapper('user_pass', $form_state);
  if (!empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    $output = array();
    ctools_add_js('ajax-responder');
    if (isset($_GET['destination'])) {
      $options = drupal_parse_url($_GET['destination']);
      $output[] = ctools_ajax_command_redirect($options['path'], $options);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  print ajax_render($output);
}

/**
 * A modal newsletter list callback.
 *
 * @param bool $js
 *   If client supports javascript.
 *
 * @return string
 *   Returns the string to be rendered either via a modal or a page.
 */
function penton_modal_newsletter_list($js = NULL) {
  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('penton_newsletter_manager_newsletters_subscribe_form_full');
  }

  ctools_include('modal');
  ctools_include('ajax');
  $form_state['ajax'] = TRUE;
  $form_state['single_list'] = TRUE;

  $output = ctools_modal_form_wrapper(
    'penton_newsletter_manager_newsletters_subscribe_form_full',
    $form_state
  );
  if (!penton_newsletter_manager_have_not_promoted_newsletters() || !empty($form_state['executed'])) {
    // We'll just overwrite the form output if it was successful.
    ctools_add_js('ajax-responder');
    $output = _penton_modal_nl_list_finished_commands();
    $output[] = penton_modal_dtm_commands_fire_rule('SUBSCRIBE_NEWSLETTER_STEP_2');
    if (!empty($form_state['values']['subscribe'])) {
      $newsletters = array_filter($form_state['values']['subscribe']);
      if (!empty($newsletters)) {
        $output[] = penton_modal_dtm_commands_fire_rule('NEWSLETTER_OPTIONS_SELECTED');
      }
    }
  }
  else {
    $output[] = penton_modal_dtm_commands_fire_rule('SUBSCRIBE_NEWSLETTER_STEP_1');
  }
  print ajax_render($output);
  drupal_exit();
}

/**
 * A modal user advanced questions callback.
 *
 * @param bool $js
 *   If client supports javascript.
 *
 * @return string
 *   Returns the string to be rendered either via a modal or a page.
 */
function penton_modal_advanced_questions($js = NULL, $type = 'article') {
  // Fall back if $js is not set.
  if (!$js) {
    return drupal_get_form('penton_user_register_advanced_questions_form');
  }

  ctools_include('modal');
  ctools_include('ajax');

  global $user;
  if ($type == 'newsletters' && empty($user->uid)) {
    ctools_add_js('ajax-responder');
    if (penton_newsletter_manager_have_not_promoted_newsletters()) {
      $output[] = ajax_command_invoke(NULL, 'nl_signup_open_nl_list_modal');
    }
    else {
      $output = _penton_modal_nl_list_finished_commands();
    }
  }
  else {
    $form_state = array(
      'ajax' => TRUE,
      'single_list' => TRUE,
      'advanced_type' => $type,
    );
    $output = ctools_modal_form_wrapper('penton_user_register_advanced_questions_form', $form_state);
    if (!empty($form_state['executed'])) {
      // We'll just overwrite the form output if it was successful.
      $output = array();
      ctools_add_js('ajax-responder');
      if ($type == 'newsletters') {
        if (penton_newsletter_manager_have_not_promoted_newsletters()) {
          $output[] = ajax_command_invoke(NULL, 'nl_signup_open_nl_list_modal');
        }
        else {
          $output = _penton_modal_nl_list_finished_commands();
        }
      }
      else {
        if (isset($_GET['destination'])) {
          $options = drupal_parse_url($_GET['destination']);
          $output[] = ctools_ajax_command_redirect($options['path'], $options);
        }
        else {
          $output[] = ctools_ajax_command_reload();
        }
      }
    }
  }
  print ajax_render($output);
}

/**
 * Form for account validation prompt.
 *
 * @param bool $js
 *   If client supports javascript.
 * @param string $step
 *   It is a multi-step form, this callback will be used for each step.
 * @param string $type
 *   Type of validation window (e.x. comment).
 */
function penton_modal_validation_wizard($js = NULL, $step = NULL, $type = NULL) {
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');

    // Set the cache key in session.
    // CTools cache key defaults to session_id() which changes when user
    // registers so we need to define our own key system.
    $cache_key = penton_modal_set_cache_key();

    // Define our multi-step form. Cancel skips the registration step.
    $form_info = array(
      'id' => 'penton_modal_validate',
      'path' => "penton_modal/" . ($js ? 'ajax' : 'nojs') . "/validation/%step",
      'show cancel' => FALSE,
      'show trail' => FALSE,
      'finish text' => NULL,
      'next callback' => 'penton_modal_wizard_next',
      'finish callback' => 'penton_modal_wizard_finish',
      // This controls order, as well as form labels.
      'order' => array(
        'prompt' => NULL,
        'thank_you' => NULL,
      ),
      // Map step to form id.
      'forms' => array(
        'prompt' => array(
          'form id' => 'penton_user_permissions_validation_prompt_form',
          'title' => NULL,
        ),
        'thank_you' => array(
          'form id' => 'penton_user_permissions_validation_thank_you_form',
          'title' => NULL,
        ),
      ),
    );

    // We're not using any real storage here, so we're going to set our
    // object_id to 1. When using wizard forms, id management turns
    // out to be one of the hardest parts. Editing an object with an id
    // is easy, but new objects don't usually have ids until somewhere
    // in creation.
    // We skip all this here by just using an id of 1.
    $object = penton_modal_return_object($object_id = 1, $step, $cache_key);
    $form_state = array(
      'ajax' => $js,
      'object_id' => $object_id,
      'sid' => $cache_key,
      'object' => &$object,
      'type' => $type,
    );
    ctools_include('wizard');
    $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
    $output = drupal_render($form);

    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // If form completed, reload page.
      $commands[] = ctools_ajax_command_reload();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }

    // TODO: send validation email here.
    print ajax_render($commands);
  }
}

/**
 * Set cache key to ensure cache even with changing sessions.
 *
 * @return string
 *   Returns the cache key, expected by ctools caching functions.
 */
function penton_modal_set_cache_key() {
  $cache_key = isset($_COOKIE['Drupal_visitor_penton_modal_cache_key']) ? $_COOKIE['Drupal_visitor_penton_modal_cache_key'] : drupal_random_key();
  if (!isset($_COOKIE['Drupal_visitor_penton_modal_cache_key'])) {
    user_cookie_save(array('penton_modal_cache_key' => $cache_key));
  }
  return $cache_key;
}

/**
 * Clears the wizard cache.
 *
 * @param int $id
 *   Object's cache id.
 * @param string $sid
 *   Cache key.
 */
function penton_modal_cache_clear($id, $sid) {
  ctools_include('object-cache');
  ctools_object_cache_clear('penton_modal', $id, $sid);
}

/**
 * Get the current object from the cache, or default.
 *
 * @param int $id
 *   Object's cache id.
 * @param string $sid
 *   The cache key.
 *
 * @return object
 *   The object stored in cache.
 */
function penton_modal_cache_get($id, $sid) {
  ctools_include('object-cache');
  $object = ctools_object_cache_get('penton_modal', $id, FALSE, $sid);
  if (!$object) {
    // Create a default object and cache it.
    $object = new stdClass();
  }
  return $object;
}

/**
 * Set cache for our wizard.
 *
 * @param int $id
 *   Object's cache id.
 * @param object $object
 *   The object to store in cache.
 * @param string $sid
 *   Cache key.
 */
function penton_modal_cache_set($id, $object, $sid) {
  ctools_include('object-cache');
  ctools_object_cache_set('penton_modal', $id, $object, $sid);
}

/**
 * Handle the 'next' click on the add/edit pane form wizard.
 *
 * All we need to do is store the updated pane in the cache.
 *
 * @param array $form_state
 *   Form's current state.
 */
function penton_modal_wizard_next(&$form_state) {
  penton_modal_cache_set($form_state['object_id'], $form_state['object'], $form_state['sid']);
}

/**
 * Handle the 'finish' click on the add/edit pane form wizard.
 *
 * All we need to do is set a flag so the return can handle adding
 * the pane.
 *
 * @param array $form_state
 *   Form's current state.
 */
function penton_modal_wizard_finish(&$form_state) {
  $form_state['complete'] = TRUE;
  user_cookie_delete('penton_modal_cache_key');
}

/**
 * Function to get modal form object.
 *
 * @param int $object_id
 *   Object id.
 * @param string $step
 *   Step identification.
 * @param string $cache_key
 *   Cache key string.
 *
 * @return object
 *   Returns modal form object.
 */
function penton_modal_return_object($object_id, $step, $cache_key) {
  if (empty($step)) {
    // We reset the form when $step is NULL because that means they have
    // for whatever reason started over.
    penton_modal_cache_clear($object_id, $cache_key);
  }
  // This automatically gets defaults if there wasn't anything saved.
  $object = penton_modal_cache_get($object_id, $cache_key);
  return $object;
}

/**
 * Returns AJAX commands to execute after register passed.
 */
function penton_modal_dtm_commands_after_register(&$commands, $action, $subscribe = FALSE, $type = 'basic') {
  global $user;
  if ($user->uid) {
    $arguments = array(
      'uid' => $user->uid,
      'reg_type' => $type,
      'event' => 'register',
      'login_status' => 'logged_in',
      'permission' => _penton_adobe_dtm_get_user_permission_level($user) . '|' . (user_has_role(PENTON_USER_UNVERIFIED_RID, $user) ? 'unverified' : 'verified'),
      'flagship' => $subscribe,
      'action' => $action,
    );
    $commands[] = ajax_command_invoke(NULL, 'dtm_reg_first_step_passed', array($arguments));
  }
}

/**
 * Returns AJAX commands to execute after register passed.
 */
function penton_modal_dtm_commands_fire_rule($action) {
  return ajax_command_invoke(NULL, 'dtm_reg_fire_direct_rule', array(
    array(
      'action' => $action,
    ),
  ));
}

/**
 * Returns AJAX commands for adding event to execute when register initiated.
 */
function penton_modal_dtm_commands_add_regtype_event($reg_type = 'basic') {
  return ajax_command_invoke(NULL, 'dtm_reg_push_regtype_event', array(
    array(
      'regType' => $reg_type,
    ),
  ));
}

/**
 * Returns AJAX commands to execute after newsletter signup passed.
 */
function _penton_modal_nl_list_finished_commands() {
  $output = array();
  global $user;
  if ($user->uid == 0) {
    $block = block_load('penton_blocks', 'penton_newsletter_signup');
    $block = _block_get_renderable_array(_block_render_blocks(array($block)));
    $out = drupal_render($block);

    $output[] = ajax_command_replace('.newsletter-signup', $out);
    $output[] = ajax_command_css('.newsletter-signup', array('display' => 'block'));
    $output[] = ctools_modal_command_dismiss();
  }
  else {
    if (isset($_GET['destination'])) {
      $options = drupal_parse_url($_GET['destination']);
      $output[] = ctools_ajax_command_redirect($options['path'], $options);
    }
    else {
      $output[] = ctools_ajax_command_reload();
    }
  }
  return $output;
}
