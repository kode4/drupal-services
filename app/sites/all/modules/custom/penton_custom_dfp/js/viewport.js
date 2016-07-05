/**
 *  events:
 *    - viewport:visible
 *    - viewport:hide
 */
(function($) {
  'use strict';

  var ViewportCollections = []
    , id = 0;

  function scroll() {
    if (ViewportCollections.length === 0) return;
    clearTimeout(id);

    var top = $(document).scrollTop();

    id = setTimeout(function() {
      for (var i = 0, max = ViewportCollections.length; i < max; i++) {
        ViewportCollections[i].exec(top);
      }
    }, 100);
  }

  var Screen = (function() {
    function Screen() {
      this.el = $(window);
    }

    Screen.prototype.getCoordinates = function() {
      return {
        y1: 0,
        y2: this.el.height()
      };
    };

    return Screen;
  }());

  var screen = new Screen();

  var ViewportManager = (function() {
    function ViewportManager() {
      this.collection = [];
      this.visibleElements = [];
      this.hideElements = [];
    }

    ViewportManager.prototype.sortElements = function() {
      for (var i = 0, max = this.collection.length; i < max; i++) {
        if (this.collection[i].isVisible(this.scrollTop)) {
          this.visibleElements.push(this.collection[i]);
        } else {
          this.hideElements.push(this.collection[i]);
        }
      }
    };
    ViewportManager.prototype.resetSortElements = function() {
      this.visibleElements = [];
      this.hideElements = [];
    };
    ViewportManager.prototype.triggerVisible = function() {
      for (var i = 0, max = this.visibleElements.length; i < max; i++) {
        this.visibleElements[i].triggerVisible();
      }
    };
    ViewportManager.prototype.triggerHide = function() {
      for (var i = 0, max = this.hideElements.length; i < max; i++) {
        this.hideElements[i].triggerHide();
      }
    };
    ViewportManager.prototype.setItem = function(item) {
      if (item instanceof Viewport) {
        this.collection.push(item);
      }

      return this;
    };
    ViewportManager.prototype.exec = function(top) {
      this.scrollTop = top;
      this.sortElements();
      this.triggerVisible();
      this.triggerHide();
      this.resetSortElements();
    };

    return ViewportManager;
  }());

  var Viewport = (function() {
    function Viewport(el) {
      this.el = el;
    }

    Viewport.prototype.getCoordinates = function(scrollTop) {
      var c = this.el.get(0).getBoundingClientRect();

      return {
        y1: c.top,
        y2: c.top + this.el.outerHeight()
      };
    };

    Viewport.prototype.isVisible = function(scrollTop) {
      var eCoords = this.getCoordinates(scrollTop)
        , sCoords = screen.getCoordinates();

      if (eCoords.y1 >= sCoords.y1 && eCoords.y2 <= sCoords.y2) {
        return true;
      }

      return false;
    };

    Viewport.prototype.triggerVisible = function() {
      this.el.trigger('viewport:visible');
    };
    Viewport.prototype.triggerHide = function() {
      this.el.trigger('viewport:hide');
    };

    return Viewport;
  }());

  $.fn.viewport = function() {
    var manager = new ViewportManager();

    $(this).each(function() {
      manager.setItem(new Viewport($(this)));
    });

    ViewportCollections.push(manager);
    scroll();
  };

  $(document).on('scroll mousewheel', scroll);

}(jQuery));
