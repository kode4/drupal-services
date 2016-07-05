(function ($) {
  Drupal.behaviors.penton_social = {
    attach: function (context, settings) {
      var shareIcons = $('.share-icons');
      // We do not want ".on is not a function" on the admin pages.
      if (!shareIcons.length) {
        return;
      }
      shareIcons.on('click', 'a.pinterest', function() {
        $(this).siblings('span').trigger('click');
      });
    }
  }
})(jQuery);
