/**
 * @file
 *   JavaScript file for comments animation and mapping.
 *
 */

(function($) {
  'use strict';

  function isAppleDevice() {
    if (navigator && typeof navigator.userAgent !== 'undefined') {
      var strUserAgent = navigator.userAgent.toLowerCase(),
        arrMatches = strUserAgent.match(/(iphone|ipod|ipad)/);

      if (arrMatches !== null) {
        return true;
      }
    }

    return false;
  }

  Drupal.behaviors.penton_comment = {
    attach: function(context, settings) {
      if($('.user-comment', context).length === 0) {
        return;
      }
      var contextId = settings.contextId ? settings.contextId : $('.comments-wrapper', context).attr('id');
      var commentBody = $('#' + contextId + ' textarea[name="comment_body[und][0][value]"]');
      var commentBodyId = commentBody.attr('id');

      // Recounting comments in case if page is cached
      var article = $('article.big-article', context);
      var nid = article.data('nid');
      var showComments = $(article.find('.comments--show'));
      if (nid) {
        $.ajax({
          method: 'GET',
          url: '/ajax/get-comments-count/' + nid,
          success: function(res) {
            if (res >= 0) {
              var commentsText = showComments.text().replace(/\d*/, res);
              showComments.text(commentsText);
            }
          },
          complete: function() {
            showComments
              .addClass('comments--ready')
              .removeClass('hidden');
          }
        });
      }

      // Hiding validation or registration prompt
      if ($('span.comment-error a.ctools-use-modal', context).length > 0) {
        $('span.comment-error', context).hide();
        $('span.comment-error a.ctools-use-modal').click(function() {
          $.cookie(contextId + '.pid', $('#' + contextId + ' input[type="hidden"][name="pid"]').val());
          $.cookie(contextId + '.cid', $('#' + contextId + ' input[type="hidden"][name="cid"]').val());
          if (CKEDITOR.instances[commentBodyId] === undefined) {
            $.cookie(contextId + '.cid', $('#' + contextId + ' textarea[name="comment_body[und][0][value]"]').val());
          } else {
            $.cookie(contextId + '.commentBody', CKEDITOR.instances[commentBodyId].getData());
          }
        });
      }
      // After comments publish ajax request is made, so we should re-add classes like if we already loaded coments
      $('.comments a.comments--show', context).on('forceLoadedState', function() {
        $(this).removeClass('hidden');
        $(this).addClass('comments--ready').addClass('comments--loaded');
      });
      // Show all comments behavior
      $('.comments a.comments--show', context).click(function() {
        if ($(this).hasClass('comments--ready')) {
          var commentsWrapper = $(this).parents('.comments-wrapper');
          //
          // Load comments via ajax
          if (!$(this).hasClass('comments--loaded')) {
            $.ajax({
              method: 'GET',
              url: '/ajax/get-comments/' + nid,
              data: {
                GET_COMMENTS: true
              },
              success: function(res) {
                showComments.addClass('comments--loaded');
                commentsWrapper.find('.comments-inner-container').html(res);
                showComments.trigger('click');
              }
            });
          } else {
            commentsWrapper.find('.comments-container').fadeIn(500);
            $('#' + contextId + ' .control-comments').each(function() {
              if ($(this).parents('.reply-to-message').length > 0) {
                $(this).trigger('click');
              }
            });
          }
        }
      });
      // Hide all comments behavior
      $('.comments-header span.comments--hide', context).click(function() {
        $(this).parents('.comments-container').fadeOut(500);
      });
      // Load more comments button behavior
      var showMore = $('#show-more-' + contextId, context);
      if (showMore.size() > 0) {
        new Drupal.ajax(null, showMore, {
          url: $('#show-more-' + contextId).attr('data-url'),
          settings: {},
          event: 'click tap'
        });
      }
      // Hiding/expanding comment thread behavior
      $('.comments-container', context).on('click', '.control-comments', function() {
        var controlDiv = $(this).find('div');
        var replyContainer = $(this).find('span.comment-reply-count');
        if (controlDiv.hasClass('hide-comment')) {
          var count = $(this).parent().find('.reply-to-message').length;
          $(this).parent().find('.reply-to-message').hide();
          controlDiv.removeClass('hide-comment').addClass('show');
          if (count === 1) {
            replyContainer.text(count + ' reply ');
          } else {
            replyContainer.text(count + ' replies ');
          }
        } else if (controlDiv.hasClass('show')) {
          $(this).parent().find('.reply-to-message').show();
          $(this).parent().find('.show').addClass('hide-comment').removeClass('show').find('span.comment-reply-count').text('');
          controlDiv.removeClass('show').addClass('hide-comment');
          replyContainer.text('');
        }
      });
      if ($('.comments a', context).length === 0) {
        // hide replies to all loaded more threads
        $('.control-comments', context).each(function() {
          if ($(this).parents('.reply-to-message').length > 0) {
            $(this).trigger('click');
          }
        });
      }
      // Comment textarea behaviors
      var sidebarButton = $('.js-expand-sidebar'),
        header = $('.js-header'),
        sidebar = $('.js-sticky-leftcol');

      var ckeditorBlurTrigger = false, breakyStatus = true;
      $(':not(.form-textarea-wrapper .comment-reply)').on('click touchstart', function() {
        if (ckeditorBlurTrigger && isAppleDevice()) {
          document.activeElement.blur();
          $('input, textarea').blur();
        }
      });

      CKEDITOR.on('instanceReady', function () {
        if (typeof breaky !== 'undefined') {
          breaky.above("small", function() {
            breakyStatus = false;
            sidebarButton.removeAttr('style');
            if (typeof PentonSingleSidebar !== 'undefined') PentonSingleSidebar.sticked();
          });
          breaky.below("small", function() {
            breakyStatus = true;
          });
        }

        if (typeof CKEDITOR.instances[commentBodyId] !== 'undefined') {
          var currentCkeditor = CKEDITOR.instances[commentBodyId];

          if (isAppleDevice()) {
            currentCkeditor.on('focus', function() {
              if (typeof PentonSingleSidebar !== 'undefined') PentonSingleSidebar.collapse();
              if (breakyStatus) {
                sidebarButton.hide();
              }
              sidebar.hide();
              header.hide();
              ckeditorBlurTrigger = true;
            });

            currentCkeditor.on('blur', function() {
              if (breakyStatus) {
                sidebarButton.show();
              }
              sidebar.show();
              header.show();
              ckeditorBlurTrigger = false;
            });
          }

          currentCkeditor.focus();
        }
      });
      // Scroll page to comment textearea
      var focusBody = function(text) {
        if ($('#' + contextId + ' span.comment-error a.ctools-use-modal').length > 0) {
          $('#' + contextId + ' span.comment-error').show();
        } else {
          $('#' + contextId + ' .publish').show().css('display','block');
        }
        if (typeof CKEDITOR.instances[commentBodyId] === 'undefined') {
          Drupal.ckeditorOn(commentBodyId);
        } else {
          CKEDITOR.instances[commentBodyId].focus();
        }
        if (typeof text !== 'undefined') {
          CKEDITOR.instances[commentBodyId].setData(text);
        }
        $('body').animate({
          scrollTop: $('#' + contextId).offset().top
        }, 500);
      };
      commentBody.focus(function() {
        focusBody();
      });
      // Fill comment form after login
      if ($.cookie(contextId + '.commentBody') !== null) {
        $('.comments a', context).click();
        focusBody($.cookie(contextId + '.commentBody'));
        $('#' + contextId + ' input[type="hidden"][name="pid"]').val($.cookie(contextId + '.pid'));
        $('#' + contextId + ' input[type="hidden"][name="cid"]').val($.cookie(contextId + '.cid'));
        $.cookie(contextId + '.commentBody', '', {expires: -1});
        $.cookie(contextId + '.pid', '', {expires: -1});
        $.cookie(contextId + '.cid', '', {expires: -1});
      }
      if (!settings.contextId && commentBody.val()) {
        focusBody();
      }
      // Publish button behavior
      $('.comments-container', context).on('click', '.publish.js-publish', function(e) {
        document.activeElement.blur();
        $('input, textarea').blur();
        $(this).closest('.comments-container').fadeTo('slow', 0.33);
        $('#' + contextId + ' [name="op"]').trigger('mousedown');
        e.stopPropagation();
        e.preventDefault();
      });
      // Reply button behavior
      $('.comments-container', context).on('click', '.comment-reply', function() {
        var cid = ($(this).closest('.comment-options').attr('data-cid'));
        $('#' + contextId + ' input[type="hidden"][name="pid"]').val(cid);
        $('#' + contextId + ' input[type="hidden"][name="cid"]').val('');
        focusBody('');
      });
      // Edit button behavior
      $('.comments-container', context).on('click', '.comment-edit', function() {
        var cid = ($(this).closest('.comment-options').attr('data-cid'));
        var pid = '';
        var parents = $(this).parents('.reply-to-message');
        if (parents.length > 0) {
          pid = $('.comment-options', $(parents[0]).siblings('.user-content')[0]).attr('data-cid');
        }
        $('#' + contextId + ' input[type="hidden"][name="pid"]').val(pid);
        $('#' + contextId + ' input[type="hidden"][name="cid"]').val(cid);
        focusBody($(this).closest('.user-content').find('.field-item').html().trim());
      });

    }
  };
})(jQuery);
