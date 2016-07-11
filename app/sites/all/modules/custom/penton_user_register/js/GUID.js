(function($) {
  Drupal.behaviors.penton_user_register = {
    attach: function (context, settings) {
      var form = $('form', context);
      if (!form.length) {
        return;
      }
      getEloquaCustomerGUIDinput(function(input) {
        form.append(input);
      });
    }
  }
})(jQuery);
