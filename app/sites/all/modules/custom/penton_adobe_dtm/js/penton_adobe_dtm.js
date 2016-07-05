/**
 * @file
 * Js for Adobe DTM tracking.
 */

var digitalData = Drupal.settings.penton_adobe_dtm;
if (typeof(digitalData.event) === 'undefined') {
  digitalData.event = [
    {
      eventName: '',
      attributes: {
        regType: '',
        commentID: ''
      }
    }
  ];
}

(function($) {
   if (typeof _satellite !== 'undefined' && typeof Drupal.settings.penton_adobe_dtm_events !== 'undefined') {
    for (var i = 0; i < Drupal.settings.penton_adobe_dtm_events.length; i++) {
      if (Drupal.settings.penton_adobe_dtm_events[i].length) {
        _satellite.track(Drupal.settings.penton_adobe_dtm_events[i]);
      }
    }
   }

  function dtm_push_new_event(eventName, regType, commentID) {
    eventName = typeof eventName === 'undefined' ? '' : eventName;
    regType = typeof regType === 'undefined' ? '' : regType;
    commentID = typeof commentID === 'undefined' ? '' : commentID;

    if (typeof digitalData.event === 'undefined') {
      digitalData.event = [];
    }
    digitalData.event.push({
      eventName: eventName,
      attributes: {
        regType: regType,
        commentID: commentID
      }
    });
  }

  function dtm_set_new_user_variables(vars) {
    if (typeof digitalData !== 'undefined') {
      // Update digital data layer.
      digitalData.user.profile.profileInfo.profileID = vars.uid;
      digitalData.user.segment.loginStatus = vars.login_status;
      digitalData.user.segment.permission = vars.permission;
      dtm_push_new_event(vars.event, vars.reg_type);
    }

    // Set _satellite vars.
    _satellite.setVar('dtm_user_uid', vars.uid);
    _satellite.setVar('dtm_reg_type', vars.reg_type);
    _satellite.setVar('dtm_event', vars.event);
    _satellite.setVar('dtm_login_status', vars.login_status);
    _satellite.setVar('dtm_user_permission', vars.permission);
  }

  $.fn.dtm_reg_first_step_passed = function (vars) {
    if (typeof _satellite !== 'undefined') {
      dtm_set_new_user_variables(vars);

      // Direct call rules.
      if (vars.action) {
        _satellite.track(vars.action);
      }
      if (vars.flagship === true) {
        _satellite.track('REGISTRATION_STEP_1_FLAGSHIP');
      }
    }
  };
  $.fn.dtm_reg_nl_signup_box = function (vars) {
    if (typeof _satellite !== 'undefined') {
      dtm_set_new_user_variables(vars);
    }
  };
  $.fn.dtm_reg_fire_direct_rule = function (vars) {
    if (typeof _satellite !== 'undefined' && typeof vars.action !== 'undefined') {
      // Direct call rules.
      _satellite.track(vars.action);
    }
  };
  $.fn.dtm_reg_push_regtype_event = function (vars) {
    if (typeof _satellite !== 'undefined' && typeof vars.regType !== 'undefined') {
      dtm_push_new_event('', vars.regType);
    }
  };
  $.fn.dtm_direct_call_comment_add = function(vals) {
    if (typeof(_satellite) !== 'undefined') {
      _satellite.setVar('dtm_comment_id', vals.dtm_comment_id);
      _satellite.setVar('dtm_event', vals.dtm_event);

      if (typeof(digitalData) !== 'undefined') {
        dtm_push_new_event(vals.dtm_event, '', vals.dtm_comment_id);
      }

      // Direct rule call.
      _satellite.track('COMMENT POSTED');
    }
  };

  Drupal.behaviors.penton_adobe_dtm = {
    attach: function(context, settings) {
      // Update digital data variables here.
    }
  };
})(jQuery);
