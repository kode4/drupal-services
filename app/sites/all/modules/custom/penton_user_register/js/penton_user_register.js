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
