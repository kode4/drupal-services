/**
 * @file
 * Penton user register Terms field switcher.
 *
 */

(function ($) {
  Drupal.behaviors.penton_user_register_terms = {
    attach: function (context, settings) {
      $('select.country', context).on('change', function () {
        penton_user_show_right_terms($(this).val());
      });
      penton_user_show_right_terms($('select.country', context).val());

      function penton_user_show_right_terms(country) {
        if (country == 'CA') {
          $('.reg-terms-of-service-canadian', context).parent().show();
          $('.reg-terms-of-service-default', context).hide();
          $('input[name="terms_canadians"]', context).attr('checked', false);
        }
        else {
          $('.reg-terms-of-service-canadian', context).parent().hide();
          $('.reg-terms-of-service-default', context).show();
          $('input[name="terms_canadians"]', context).attr('checked', true);
        }
      }
    }
  };
})(jQuery);
