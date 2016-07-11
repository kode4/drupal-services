(function($) {
  'use strict';

  $(function() {
    var alert, popup, legal;

    legal = new LegalCommunication();

    if(legal.isNotDisable() && legal.isLogin() && legal.isPopup()) {
      legal.removeIndented();
      popup = new LegalPopup();
      popup.show();
      popup.events(legal);
    } else if(legal.isNotDisable() && legal.isLogin()) {
      popup = new LegalAlert();
      popup.show();
      popup.events(legal);
    }

    if(!legal.isLogin()) {
      legal.getMessage(function(self, data) {
        self.selfEl.hide().html(data);

        if(self.isPopup()) {
          popup = new LegalPopup();
          popup.show();
          popup.events(self);
        } else {
          self.selfEl.show();
          self.addIndented();

          alert = new LegalAlert();
          alert.show(function() {
            alert.events(self);
          });
        }
      });
    }
  });
}(jQuery));
;
var LegalAlert = {},
  LegalPopup = {},
  LegalCommunication = {};

(function($, win) {
  'use strict';

  function eventHide() {
    if(typeof PentonSingleHeader !== 'undefined' &&
      typeof PentonSingleHeader.toDefaultHeight === 'function' &&
      typeof PentonSingleHeader.resize === 'function') {

      PentonSingleHeader.toDefaultHeight();
      PentonSingleHeader.resize();
    }
    if(typeof PentonSingleSidebar !== 'undefined' &&
      typeof PentonSingleSidebar.inSticked === 'function') {

      PentonSingleSidebar.inSticked();
    }
  }
  function eventBreakpoint(self) {
    if(typeof PentonSingleHeader !== 'undefined' &&
      typeof PentonSingleHeader.toDefaultHeight === 'function' &&
      typeof PentonSingleHeader.getHeight === 'function' &&
      typeof PentonSingleHeader.resize === 'function') {

      PentonSingleHeader.toDefaultHeight();
      var height = PentonSingleHeader.getHeight();
      PentonSingleHeader.setHeight(height.minHeight + self.minHeight, height.maxHeight + self.minHeight);
    }

    if(typeof PentonSingleSidebar !== 'undefined' &&
      typeof PentonSingleSidebar.inSticked === 'function') {

      PentonSingleSidebar.inSticked();
    }
  }

  LegalCommunication = (function() {
    function LegalCommunication() {
      this.approvalUrl = 'ajax/penton-legal-comm';
      this.messageUrl = 'ajax/penton-legal-comm-get-message';
      this.countUrl = 'ajax/penton-legal-comm-count';

      this.selfSel = '.js-penton-legal-comm-ajax-output-alert';
      this.popupSel = '.js-legal-comm-message-pop-up';
      this.selfEl = null;
      this.htmlEl = null;

      this.init();
    }

    function checkCallback(cb) {
      if(typeof cb === 'function') {
        return true;
      }

      return false;
    }

    LegalCommunication.prototype.init = function() {
      this.selfEl = $(this.selfSel);
      this.htmlEl = $('html');
    };
    LegalCommunication.prototype.isNotDisable = function() {
      return !!this.selfEl.children().length;
    };
    LegalCommunication.prototype.isPopup = function() {
      return !!this.selfEl.find(this.popupSel).length;
    };
    LegalCommunication.prototype.removeIndented = function() {
      this.htmlEl.removeClass('js-legal-comm-message-show');
    };
    LegalCommunication.prototype.addIndented = function() {
      this.htmlEl.addClass('js-legal-comm-message-show');
    };
    LegalCommunication.prototype.isLogin = function() {
      return !$('.not-logged-in').length;
    };
    LegalCommunication.prototype.approval = function(id) {
      $.ajax({
        type: "POST",
        url: Drupal.settings.basePath + this.approvalUrl,
        data: ({ 'nid' : id })
      });
    };
    LegalCommunication.prototype.counting = function(id) {
      $.ajax({
        type: "POST",
        url: Drupal.settings.basePath + this.countUrl,
        data: ({ 'nid' : id })
      });
    };
    LegalCommunication.prototype.getMessage = function(succCb, failCb) {
      var self = this;

      $.ajax({
        type: "POST",
        url: Drupal.settings.basePath + this.messageUrl,
        success: function(data) {
          if(data.length) {
            if(checkCallback(succCb)) {
              succCb(self, data);
            }
          } else {
            if(checkCallback(failCb)) {
              failCb(self);
            }
          }
        }
      });
    };

    return LegalCommunication;
  }());

  LegalAlert = (function() {
    function LegalAlert() {
      this.ID = 0;
      this.animateTime = 500;

      this.selfSel = '.js-legal-comm-message';
      this.linkCollSel = '.js-legal-comm-trigger';

      this.containerEl = null;
      this.selfEl = null;
      this.linkCollEl = null;
      this.messContEl = null;

      this.minHeight = 42;
      this.maxHeight = 0;

      this.messMinHeight = 22;
      this.messMaxHeight = 0;

      this.visible = false;

      this.init();
    }

    LegalAlert.prototype.init = function() {
      this.selfEl = $(this.selfSel);
      this.linkCollEl = $(this.linkCollSel);
      this.ID = this.selfEl.attr('data-penton-legal-comm-nid');
      this.dotted = this.selfEl.find('.js-legal-comm-trigger-three-dotted');
    };
    LegalAlert.prototype.isset = function() {
      return !!this.selfSel.length;
    };
    LegalAlert.prototype._countHeight = function() {
      this.messContEl = this.selfEl.find('.alert-msg');
      this.messContEl.removeAttr('style');
      this.minHeight = this.selfEl.height();
      this.messMinHeight = this.messContEl.height();
      this.messContEl.css('height', 'auto');
      this.messContEl.addClass('active');
      this.selfEl.addClass('active');
      this.maxHeight = this.selfEl.height();
      this.messMaxHeight = this.messContEl.height();
      this.messContEl.css('height', this.messMinHeight);
      this.messContEl.removeClass('active');
      this.selfEl.removeClass('active');
    };
    LegalAlert.prototype.show = function(cb, time) {
      var self = this;

      cb = cb || function(){};
      time = time || this.animateTime;

      this.visible = true;

      this.selfEl.slideDown(time, function() {
        cb();
        self._isCollapse();
        self._countHeight();
        // Prevent  banner overlapping
        $('.banner-top-wrapper').css('padding-top',  $('.js-penton-legal-comm-ajax-output-alert').outerHeight());
      });
    };
    LegalAlert.prototype.hide = function(cb, time) {
      cb = cb || function(){};
      time = time || this.animateTime;

      this.selfEl.slideUp(time, cb);

      this.visible = false;

      eventHide();
    };
    LegalAlert.prototype.expand = function(cb, time) {
      cb = cb || function(){};
      time = time || this.animateTime;

      this.messContEl.stop(true, true).animate({'height': this.messMaxHeight}, time, function(){
        this.messContEl.css('overflow', 'visible');
      }.bind(this));
      this.messContEl.addClass('active');
      this.selfEl.addClass('active');
      this.linkCollEl.removeClass('js-legal-comm-collapse');
      this.linkCollEl.addClass('js-legal-comm-expand');
      this.linkCollEl.text('hide');
      this.dotted.hide();

    };
    LegalAlert.prototype.collapse = function(cb, time) {
      cb = cb || function(){};
      time = time || this.animateTime;

      this.messContEl.stop(true, true).animate({'height': this.messMinHeight}, time, function() {
        this.linkCollEl.removeClass('js-legal-comm-expand');
        this.linkCollEl.addClass('js-legal-comm-collapse');
        this.linkCollEl.text('read more');
        this.messContEl.css('overflow', 'hidden');
        this.messContEl.removeClass('active');
        this.selfEl.removeClass('active');
      }.bind(this));

      this.dotted.show();
    };
    LegalAlert.prototype._isCollapse = function() {
      var contHeight = this.selfEl.find('.alert-msg').height(),
        textHeight = this.selfEl.find('.js-legal-comm-text').height();

      if(contHeight < textHeight) {
        this.linkCollEl.show();
        this.dotted.show();
      } else {
        this.linkCollEl.hide();
        this.dotted.hide();
      }
    };
    LegalAlert.prototype.events = function(legal) {
      var self = this;

      if(!(legal instanceof LegalCommunication)) {
        return false;
      }

      $(win).on('resize', function() {
        self.collapse();
        self._isCollapse();
        self._countHeight();
      });
      this.linkCollEl.on('click', function(e) {
        e.preventDefault();

        if($(this).hasClass('js-legal-comm-collapse')) {
          self.expand();
        } else {
          self.collapse();
        }
      });
      this.selfEl.find('.js-legal-comm-message-agree').on('click', function(e) {
        e.preventDefault();
        legal.approval(self.ID);
        self.hide();
      });
      this.selfEl.find('.js-legal-comm-message-close').on('click', function(e) {
        e.preventDefault();
        legal.counting(self.ID);
        self.hide();
      });
      this.selfEl.find('.js-legal-comm-message-confirm').on('click', function(e) {
        e.preventDefault();
        legal.approval(self.ID);
        self.hide();
        // Restore banner position
        $('.banner-top-wrapper').css('padding-top',  '');
      });

      function breakpoint() {
        self._isCollapse();
        self._countHeight();

        if(self.visible) {
          eventBreakpoint(self);
        }
      }

      breaky.above("small", breakpoint);
      breaky.below("small", breakpoint);
    };

    return LegalAlert;
  }());

  LegalPopup = (function() {
    function LegalPopup() {
      this.ID = 0;

      this.selfSel = '.js-legal-comm-message-pop-up';

      this.containerEl = null;
      this.selfEl = null;

      this.init();
    }

    LegalPopup.prototype.init = function() {
      this.selfEl = $(this.selfSel);

      this.ID = this.selfEl.attr('data-penton-legal-comm-nid');
    };
    LegalPopup.prototype.isset = function() {
      return !!this.selfSel.length;
    };
    LegalPopup.prototype.show = function() {
      Drupal.CTools.Modal.show('modal-popup-legal-comm');
      $('#modal-title').text(this.selfEl.find('.js-legal-comm-message-title').text());
      $('#modal-content').html(this.selfEl.find('.js-legal-comm-message-description').html());
    };
    LegalPopup.prototype.hide = function() {
      Drupal.CTools.Modal.dismiss('modal-popup-legal-comm');
    };
    LegalPopup.prototype.events = function(legal) {
      var self = this;

      if(!(legal instanceof LegalCommunication)) {
        return false;
      }

      $('.js-legal-comm-message-agree').on('click', function(e) {
        e.preventDefault();
        legal.approval(self.ID);
        self.hide();
      });
    };

    return LegalPopup;
  }());

}(jQuery, window));
;
