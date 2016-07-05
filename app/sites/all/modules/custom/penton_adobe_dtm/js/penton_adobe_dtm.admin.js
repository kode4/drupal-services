/**
 * @file
 * JS for Penton Adobe DTM config page
 */

jQuery(document).ready(function($) {
  // Code that uses jQuery's $ can follow here.
  $('#edit-adobe-dtm-id').bind('input', function (e) {
    var value = $(this).val();
    value = value.length ? value : '{ID}';
    $('.dtm-complete-path .dtm-id b').html(value);
  });

  $('#edit-adobe-dtm-site-hash').bind('input', function (e) {
    var value = $(this).val();
    value = value.length ? value : '{SITE-HASH}';
    $('.dtm-complete-path .dtm-site-hash b').html(value);
  });

  $('#edit-adobe-dtm-environment').bind('input', function (e) {
    var value = $(this).val();
    value = value == 'staging' ? '-staging' : '';
    $('.dtm-complete-path .dtm-environment').html(value);
  });
});
