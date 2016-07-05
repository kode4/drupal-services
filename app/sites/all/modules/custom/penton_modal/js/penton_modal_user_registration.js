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
