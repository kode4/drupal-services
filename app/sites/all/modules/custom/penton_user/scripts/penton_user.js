/**
 * @file
 *   JavaScript file for jQueryUI animation.
 *
 */

(function($) {
  "use strict";
  $(function() {
    $( ".tooltip" ).tooltip({
      position: { my: "left+15 center", at: "right center" }
    });
   $("#account-tabs").tabs( { hide: 'fadeOut', show: 'fadeIn' } );
  });
})(jQuery);
