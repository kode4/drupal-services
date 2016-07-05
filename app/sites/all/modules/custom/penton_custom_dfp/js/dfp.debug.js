var DFPDebug = {};

(function($, console) {
  'use strict';

  var IS_DEBUG = false;

  function scan_debug_mode() {
    var pattern = new RegExp('dfp_log');
    IS_DEBUG = pattern.test(location.search);

    if(IS_DEBUG) {
      console.log('%cDFP ENABLE DEBUG MODE', 'color: blue; font-size: x-large');
    }
  }

  DFPDebug = (function() {
    function DFPDebug(type) {
      this.prefix = '%c';
      this.content= [];
      this.breakpoints = [];
      this.targeting = [];
      this.longString = 0;
      this.tag = {};
      this.type = type || 'DFPDebug';
      this.tagMessage = [];
    }

    DFPDebug.prototype.print = function() {
      if(!IS_DEBUG) {
        return;
      }

      this.printTag();
      this.printTargeting();
      this.printBreakpoints();
      this._print();
    };
    DFPDebug.prototype._print = function() {
      if(!this.content.length) {
        return;
      }
      console.group(this.type);

      this.countLongString(this.content);

      var pipe = '|',
        dashline = new Array(this.longString + 3).join('-'),
        line = '+' + dashline + '+';

      console.log(line);

      for(var i = 0; i < this.content.length; i++) {
        var contentLine = '';
        if(this.content[i] === '[blank]') {
          contentLine = dashline;
        } else {
          contentLine = ' ' + this.content[i] + new Array(this.longString - this.content[i].length + 2).join(' ');
        }

        console.log(pipe + contentLine + pipe);
      }

      console.log(line);
      console.groupEnd();
    };
    DFPDebug.prototype.printBlank = function() {
      this.content.push('[blank]');
    };
    DFPDebug.prototype.printBreakpoints = function() {
      if(this.breakpoints.length) {
        this.printBlank();
        this.content.push('Breakpoints:');

        for(var i = 0; i < this.breakpoints.length; i++) {
          this.content.push(this.breakpoints[i]);
        }
      }
    };
    DFPDebug.prototype.printTargeting = function() {
      if(this.targeting.length) {
        this.printBlank();
        this.content.push('Targeting:');

        for(var i = 0; i < this.targeting.length; i++) {
          this.content.push(this.targeting[i]);
        }
      }
    };
    DFPDebug.prototype.printTag = function() {
      if(!$.isEmptyObject(this.tag)) {
        this.content.push('adUnitPath: ' + this.tag.adunit);
        this.content.push('machineName: ' + this.tag.machinename);
        this.content.push('selector: ' + this.tag.divId);

        this.content = this.content.concat(this.tagMessage);
      }
    };
    DFPDebug.prototype.addLine = function(message) {
      this.content.push(message);
      return this;
    };
    DFPDebug.prototype.countLongString = function(data) {
      for(var i = 0; i < data.length; i++) {
        if(this.longString < data[i].length) {
          this.longString = data[i].length;
        }
      }

      return this;
    };
    DFPDebug.prototype.addBreakpoints = function(breakpoints) {
      this.breakpoints.push(' - browser size: ' + this.formatSize(breakpoints.browser_size));
      this.breakpoints.push(' - ad sizes: ' + this.formatSize(breakpoints.ad_sizes));

      return this;
    };
    DFPDebug.prototype.addTargeting = function(target) {
      this.targeting.push(' - target: ' + target.target);
      this.targeting.push(' - value: ' + '[' + target.value.toString() + ']');

      return this;
    };
    DFPDebug.prototype.addTag = function(message) {
      this.tagMessage.push(message);

      return this;
    };
    DFPDebug.prototype.setTag = function(tag) {
      this.tag = tag;
      return this;
    };
    DFPDebug.prototype.setType = function(type) {
      this.type = type;
      return this;
    };
    DFPDebug.prototype.formatSize = function(sizes) {
      var size = [];

      if($.isArray(sizes[0])) {
        for(var i = 0; i < sizes.length; i++) {
          size.push('[' + sizes[i].join(', ') + ']');
        }
        return '[' + size.join(', ') + ']';
      } else {
        return '[' + sizes.join(', ') + ']';
      }
    };

    return DFPDebug;
  })();

  scan_debug_mode();
}(jQuery, window.console));
