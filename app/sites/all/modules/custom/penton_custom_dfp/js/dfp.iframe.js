var DFPIframe = {};

(function($) {
  'use strict';

  DFPIframe = (function() {
    function DFPIframe() {
      this.src = 'http://ad.doubleclick.net/activity;';
      this.params = {};
      this.attr = {
        width: 1,
        height: 1,
        frameborder: 0,
        src: this.src
      };
      this.style = {
        display: 'none'
      };
      this.el = $('<iframe>');
    }

    DFPIframe.prototype.addParam = function(name, value) {
      this.params[name] = value;
    };

    DFPIframe.prototype.setParams = function(values) {
      this.params = values;
    };

    DFPIframe.prototype.createIframe = function() {
      var paramsInline = [];

      for (var k in this.params) {
        if (this.params.hasOwnProperty(k)) {
          paramsInline.push(k + '=' + this.params[k]);
        }
      }

      this.attr.src += paramsInline.join(';') + '?';
      this.el.attr(this.attr).css(this.style);
    };

    DFPIframe.prototype.exec = function() {
      if ($.isEmptyObject(this.params)) return;
      this.createIframe();
      $('body').append(this.el);
    };

    return DFPIframe;
  }());
}(jQuery));
