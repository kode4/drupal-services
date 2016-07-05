var DFPTag = {};

(function($) {
  'use strict';

  DFPTag = (function() {
    function DFPTag(data) {
      this.objectPosition = {};
      this.hasImported = false;
      this.disabled = false;
      this.googleTag = {};
      this.mapping = null;
      this.divId = 'dfp-tag-' + this.generateDivId(64);
      this.element = $('<div>');
      this.defined = false;

      if(!$.isEmptyObject(data)) {
        this.import(data);
      }
    }

    DFPTag.prototype.isDefined = function() {
      return this.defined;
    };
    DFPTag.prototype.import = function(tag) {
      for(var k in tag) {
        if(tag.hasOwnProperty(k)) {
          this[k] = tag[k];
        }
      }

      this.hasImported = true;

      return this;
    };
    DFPTag.prototype.generateDivId = function(lengthString) {
      return Array(lengthString+1).join((Math.random().toString(36)+'00000000000000000').slice(2, 18)).slice(0, lengthString);
    }
    DFPTag.prototype.hasImport = function() {
      return this.hasImported;
    };
    DFPTag.prototype.setPosition = function(position) {
      if(position instanceof DFPPosition) {
        this.objectPosition = position;
      }
    };
    DFPTag.prototype.getMachineName = function() {
      return this.machinename;
    };
    DFPTag.prototype.setAdUnit = function(adunit) {
      this.adunit = adunit;
      return this;
    };
    DFPTag.prototype.destroySlot= function(key) {
      googletag.destroySlots([this.googleTag]);
      return this;
    };
    DFPTag.prototype.clearTargeting= function(key) {
      for(var i = 0; i < this.targeting.length; i++) {
        if(this.targeting[i].target === key) {
          this.targeting.splice(i, 1);
          break;
        }
      }

      if(typeof this.googleTag.clearTargeting === 'function') {
        this.googleTag.clearTargeting(key);
      }

      return this;
    };

    DFPTag.prototype.getTargeting= function(key) {
      for(var i = 0; i < this.targeting.length; i++) {
        if(this.targeting[i].target === key) {
          return this.targeting[i].value;
        }
      }

      return false;
    };
    DFPTag.prototype.setTargeting= function(key, value) {
      var status = true;

      for(var i = 0; i < this.targeting.length; i++) {
        if(this.targeting[i].target === key) {
          this.targeting[i].value = value;
          status = false;
        }
      }

      if(status) {
        this.targeting.push({
          'target': key,
          'value': value
        });
      }

      if(typeof this.googleTag.setTargeting === 'function') {
        this.googleTag.setTargeting(key, value);
      }

      return this;
    };
    DFPTag.prototype.define = function() {
      var debug = new DFPDebug('DFPTag (define): ' + this.machinename);

      if($.isEmptyObject(this.objectPosition)) {
        debug.addLine('Define: FALSE');
        debug.addLine('Position: Not found ' + this.settings.position);
        debug.setTag(this);
        debug.print();
        return;
      }

      if(this.disabled) {
        debug.addLine('Define: FALSE');
        debug.addLine('Position: ' + this.settings.position);
        debug.addLine('Disabled: TRUE');
        debug.setTag(this);
        debug.print();
        return;
      }

      if(this.breakpoints.length && parseInt(this.settings.out_of_page) === 0) {
        this.mapping = googletag.sizeMapping();

        for(var i = 0; i < this.breakpoints.length; i++) {
          this.mapping.addSize(this.breakpoints[i].browser_size, this.breakpoints[i].ad_sizes);
          debug.addBreakpoints(this.breakpoints[i]);
        }

        this.mapping = this.mapping.build();
      }

      if(parseInt(this.settings.out_of_page) === 0) {
        this.googleTag = googletag.defineSlot(this.adunit, this.size, this.divId);
        debug.addTag('Size: ' + this.size.join(', '));
        debug.addTag('Out of Page: FALSE');
      } else {
        this.googleTag = googletag.defineOutOfPageSlot(this.adunit, this.divId);
        debug.addTag('Out of Page: TRUE');
      }

      if(this.settings.adsense_ad_types) {
        this.googleTag.set('adsense_ad_types', this.settings.adsense_ad_types);
        debug.addTag('Adsense ad types: ' + this.settings.adsense_ad_types);
      }
      if(this.settings.adsense_channel_ids) {
        this.googleTag.set('adsense_channel_ids', this.settings.adsense_channel_ids);
        debug.addTag('Adsense channel ids: ' + this.settings.adsense_channel_ids);
      }

      var adsense_colors = this.settings.adsense_colors.background;
      for(var adsenseKey in adsense_colors) {
        if(adsense_colors.hasOwnProperty(adsenseKey) && adsense_colors[adsenseKey] !== '') {
          this.googleTag.set('adsense_' + adsenseKey + '_color', '#' + adsense_colors[adsenseKey]);
          debug.addTag('Adsense ' + adsenseKey + ' color: ' + adsense_colors[adsenseKey]);
        }
      }

      this.googleTag.addService(googletag.pubads());

      for(var j = 0; j < this.targeting.length; j++) {
        this.googleTag.setTargeting(this.targeting[j].target, this.targeting[j].value);
        debug.addTargeting(this.targeting[j]);
      }

      if(this.breakpoints.length) {
        this.googleTag.defineSizeMapping(this.mapping);
      }

      googletag.slots[this.divId] = this.googleTag;

      this.defined = true;

      debug.setTag(this);
      debug.print();
    };
    DFPTag.prototype.display = function() {
      var debug = new DFPDebug('DFPTag: (display) ' + this.machinename),
        self = this;

      debug.setTag(this);

      if($.isEmptyObject(this.objectPosition)) {
        debug.addLine('Render: FALSE');
        debug.addLine('Position: Not found ' + this.settings.position);
        debug.setTag(this);
        debug.print();
        return;
      }

      if(this.disabled) {
        debug.addLine('Define: FALSE');
        debug.addLine('Position: ' + this.settings.position);
        debug.setTag(this);
        debug.print();
        return;
      }

      debug.addLine('Render: TRUE');
      debug.addLine('Position: ' + this.objectPosition.getName());

      this.element.attr({
        'id': this.divId,
        'data-dfp-machinename': this.machinename
      });

      this.objectPosition.addIn(this.element);

      $(function() {
        googletag.display(self.divId);
      });

      debug.print();
    };
    DFPTag.prototype.clear = function() {
      googletag.pubads().clear([this.googleTag]);
    };
    DFPTag.prototype.refresh = function() {
      googletag.pubads().refresh([this.googleTag]);
    };
    DFPTag.prototype.inDisabled = function() {
      this.disabled = true;
      return this;
    };
    DFPTag.prototype.inEnabled = function() {
      this.disabled = false;
      return this;
    };

    return DFPTag;
  })();

}(jQuery));
