/**
 * @file
 * Js for modal registration process.
 */

(function($, win) {
  Drupal.behaviors.penton_modal = {
    attach: function(context, settings) {
      var display = false, wrapper;

      var form = $('form', context);
      if (form.hasClass('penton_modal_submit_on_close')) {
        // This event fires before click from our module, so we need to unbind it.
        $('div div.close-reg-btn.close', context).unbind('click');
      }

      if (window.location.pathname.indexOf('penton_ur_thank_you') !== -1
        && window.location.href.indexOf('notkli=1') === -1
        && typeof _satellite !== 'undefined') {
        // Direct call rules.
        _satellite.track('ADVANCED_REGISTRATION_STEP_3');
      }
      $('button.thank-you-reload', context).click(function () {
        if (typeof _satellite !== 'undefined') {
          // Direct call rules.
          _satellite.track('ADVANCED_REGISTRATION_STEP_4');
        }
        reload_modal_window();
      });
      $('div.close-reg-btn', context).click(function () {
        if (form.hasClass('penton_modal_reload_after_close')) {
          reload_modal_window();
        } else if (form.hasClass('penton_modal_submit_on_close')) {
          form.find('input[type=checkbox]').attr('checked', false);
          form.find('button.form-submit').trigger('click');
        }
      });
      function reload_modal_window() {
        // Delete user cookie set during ctools modal wizard process.
        $.cookie('Drupal.visitor.penton_modal_cache_key', null, { path: '/' });
        window.top.location.reload(true);
      }

      function break_points() {
        wrapper = $('.ctools-modal-wrapper', context);

        var height = wrapper.find('.ctools-modal__inner').outerHeight();

        if($(win).width() <= 400 && $(win).height() <= height) {
          wrapper.addClass('ctools-modal-wrapper__fixed');
          display = 'mobile';
        } else if($(win).height() <= height) {
          wrapper.addClass('ctools-modal-wrapper__fixed');
          display = 'table';
        } else {
          display = false;
          wrapper.removeClass('ctools-modal-wrapper__fixed');
        }
      }
      function reset_left_indent() {
        if(display === 'mobile') {
          $(context).css({
            'left': '0',
            'margin-left': 0
          });
        } else if(display !== 'mobile') {
          $(context).css({
            'left': '50%',
            'margin-left': -($('.ctools-modal-wrapper', context).width() / 2)
          });
        }
      }

      if( typeof $('.ctools-modal-wrapper', context).areaScroll === 'function') {
        var wrapper_scroll = $('.ctools-modal-wrapper', context).areaScroll(reset_left_indent);
        var newsletters_scroll = $('.newsletters-list', context).areaScroll();

        $('.close', context).on('click', function() {
          wrapper_scroll.detachEvents().destroy();
          newsletters_scroll.detachEvents().destroy();
          $(this).off();
        });
      }

      break_points();
      reset_left_indent();

      $(win).resize(function() {
        break_points();
        reset_left_indent();
      });
    }
  };
})(jQuery, window);
;
/**
 * @file
 * Penton user register related js.
 *
 */

(function ($) {
  $.fn.success_newsletter_signup = function (val) {
    $('.newsletter-signup').hide();
    $('a.nl_href_link').click();
  };
  $.fn.nl_signup_open_nl_list_modal = function (val) {
    $('.newsletter-signup').hide();
    var nl_list_url = '/penton_modal/nojs/nl_list';
    var $link = $("<a></a>").attr('href', nl_list_url)
      .addClass('ctools-use-modal-processed ctools-modal-modal-popup-medium')
      .click(Drupal.CTools.Modal.clickAjaxLink);

    Drupal.ajax[nl_list_url] = new Drupal.ajax(nl_list_url, $link.get(0), {
      url: nl_list_url,
      event: 'click',
      progress: { type: 'throbber' }
    });
    $link.click();
  }
}(jQuery));

(function($) {
  Drupal.behaviors.penton_newsletter_signup = {
    attach: function(context, settings) {
      if ($('.newsletter-signup-form', context).length) {
        $('.newsletter-signup-form select.country', context).on('change', function () {
          penton_newsletter_signup_show_right_terms($(this).val());
        });
        penton_newsletter_signup_show_right_terms($('.newsletter-signup-form select.country', context).val());
      }

      function penton_newsletter_signup_show_right_terms(country) {
        var $reg_terms_wrapper = $('.reg-terms-of-service-wrapper .form-item-terms', context);
        $reg_terms_wrapper.toggle(country == 'CA');
        $reg_terms_wrapper.find('input[name="terms"]').attr('checked', country != 'CA');
      }
    }
  };
})(jQuery);
;
/**
 * @file
 * Modifies the file selection and download access expiration interfaces.
 */

var uc_file_list = {};

/**
 * Adds files to delete to the list.
 */
function _uc_file_delete_list_populate() {
  jQuery('.affected-file-name').empty().append(uc_file_list[jQuery('#edit-recurse-directories').attr('checked')]);
}

jQuery(document).ready(
  function() {
    _uc_file_delete_list_populate();
  }
);

// When you (un)check the recursion option on the file deletion form.
Drupal.behaviors.ucFileDeleteList = {
  attach: function(context, settings) {
    jQuery('#edit-recurse-directories:not(.ucFileDeleteList-processed)', context).addClass('ucFileDeleteList-processed').change(
      function() {
        _uc_file_delete_list_populate()
      }
    );
  }
}

/**
 * Give visual feedback to the user about download numbers.
 *
 * TODO: would be to use AJAX to get the new download key and
 * insert it into the link if the user hasn't exceeded download limits.
 * I dunno if that's technically feasible though.
 */
function uc_file_update_download(id, accessed, limit) {
  if (accessed < limit || limit == -1) {

    // Handle the max download number as well.
    var downloads = '';
    downloads += accessed + 1;
    downloads += '/';
    downloads += limit == -1 ? 'Unlimited' : limit;
    jQuery('td#download-' + id).html(downloads);
    jQuery('td#download-' + id).attr("onclick", "");
  }
}
;
