/**
 * @file
 * Wraps up Penton Modal forms.
 *
 * Themed CTools modal forms wrapper.
 */

Drupal.theme.prototype.PentonModalPopup = function() {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="ctools-modal-wrapper">';
  html += '    <div class="ctools-modal__inner registration-form__inner">';
  html += '      <div class="close-reg-btn close">x</div>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

Drupal.theme.prototype.PentonModalPopupBasic = function() {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="ctools-modal-wrapper">';
  html += '    <div class="ctools-modal__inner registration-form__inner registration-form-basic__inner">';
  html += '      <div class="close-reg-btn close">x</div>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

Drupal.theme.prototype.PentonModalPopupBasicEmail = function() {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="ctools-modal-wrapper">';
  html += '    <div class="ctools-modal__inner registration-form__inner registration-form-basic-email__inner">';
  html += '      <div class="close-reg-btn close">x</div>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

Drupal.theme.prototype.PentonModalPopupAdvanced = function() {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="ctools-modal-wrapper">';
  html += '    <div class="ctools-modal__inner registration-form__inner registration-form-advanced__inner">';
  html += '      <div class="close-reg-btn close">x</div>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

/**
  * Wraps up Penton Modal login forms.
  *
  * Themed CTools modal forms wrapper.
  */

Drupal.theme.prototype.PentonModalPopupLogin = function () {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="ctools-modal-wrapper">';
  html += '    <div class="ctools-modal__inner login-form__inner">';
  html += '      <div class="close-reg-btn close">x</div>';
  html += '      <h2 id="modal-title" class="login-form__header"></h2>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

Drupal.theme.prototype.PentonModalPopupLegalComm = function() {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="legal_comm-modal">';
  html += '    <div class="legal_comm-modal-content">';
  html += '      <h1 id="modal-title"></h1>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}

Drupal.theme.prototype.PentonModalPopupValidationPrompt = function() {
  var html = '';

  html += '<div id="ctools-modal">';
  html += '  <div class="ctools-modal-wrapper">';
  html += '    <div class="ctools-modal__inner validation-prompt-form__inner">';
  html += '      <div class="close-reg-btn close">x</div>';
  html += '      <h1 id="modal-title"></h1>';
  html += '      <div id="modal-content"></div>';
  html += '    </div>';
  html += '  </div>';
  html += '</div>';

  return html;
}
;
(function($) {
  'use strict';

  function getProperty(object, path) {
    var obj = Object.create(object)
      , paths = path.split('.')
      , current = obj
      , i
      ;

    for (i = 0; i < paths.length; ++i) {
      if (current[paths[i]] == undefined) {
        return undefined;
      } else {
        current = current[paths[i]];
      }
    }

    return current;
  }

  $.fn.dataRender = function(settings, data) {
    var options = $.extend({
          tag: 'div',
          filter: function(value) {
            return value.toString();
          },
          attr: {},
          schema: {}
        }, settings)
      , tag
      , item
      , name
      , val
      , schema = options.schema
      , type
      ;

    for (var i = 0; i < data.length; i++) {
      tag = $('<{tag}>'.replace('{tag}', options.tag));
      item  = data[i];

      if ($.isEmptyObject(options.schema)) {
        for (var k in item) {
          if (!item.hasOwnProperty(k)) {
            continue;
          }
          tag.attr(options.attr);
          tag.attr('data-' + k, options.filter(item[k]));
        }
      } else {
        for (var k in schema) {
          if (!schema.hasOwnProperty(k)) {
            continue;
          }

          tag.attr(options.attr);

          if (typeof getProperty(item, k) !== 'undefined') {
            name = (typeof schema[k].rename === 'undefined' || $.isEmptyObject(schema[k])) ? k : schema[k].rename;
            val  = (typeof schema[k].filter === 'undefined' || $.isEmptyObject(schema[k])) ? getProperty(item, k) : schema[k].filter(getProperty(item, k));
            type = (typeof schema[k].type === 'undefined' || $.isEmptyObject(schema[k])) ? 'data-' : '';

            val = options.filter(val);
            if (val) {
              tag.attr(type + name, val);
            }
          }
        }
      }

      $(this).append(tag);
    }
  };

} (jQuery));
;
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
;
var googletag = googletag || {}, DFPHelper = {};
googletag.cmd = googletag.cmd || [];
googletag.slots = googletag.slots || {};


(function($) {
  'use strict';

  var DFPItems = {}
    , DFP
    , Debug
    , IS_DEBUG = false
    ;

    /**
     *  Helper check debug mode.
     *  @return: void;
     */
  function scanDebugMode() {
    var pattern = new RegExp('dfp_log');
    IS_DEBUG = pattern.test(location.search);

    if(IS_DEBUG) {
      console.log('%cDFP ENABLE DEBUG MODE', 'color: blue; font-size: x-large');
    }
  }
  scanDebugMode();

  /**
   *  Helper for get count properties in object.
   *  @return: Int length;
   */
  function length(object) {
    var k, length = 0;

    for (k in object) {
      if (!object.hasOwnProperty(k)) {
        continue;
      }

      length++;
    }

    return length;
  }


  function cleanMapping(arr) {
    for (var i = arr.length - 1; i >= 0; i--) {
      if ($.isArray(arr[i])) {
        cleanMapping(arr[i]);
      } else if (arr[i] === '') {
        arr.splice(i, 1);
      }
    }
  }

  Debug = (function () {
    function Debug(title) {
      this.title = title || '';
      this.content= [];
      this.longString = 0;
      this.breakpoints = [];
      this.targeting = [];
    }

    Debug.prototype.print = function () {
      if(!IS_DEBUG) {
        return;
      }

      this._printTargeting();
      this._printBreakpoints();
      this._print();
    };
    Debug.prototype._print = function () {
      var pipe = '|'
        , dashline
        , line
        ;

      if (!this.content.length) {
        return;
      }

      console.groupCollapsed(this.title);

      this.countLongString(this.content);

      dashline = new Array(this.longString + 3).join('-');
      line = '+' + dashline + '+';

      console.log(line);

      for (var i = 0; i < this.content.length; i++) {
        var contentLine = '';

        if (this.content[i] === '[blank]') {
          contentLine = dashline;
        } else {
          contentLine = ' ' + this.content[i] + new Array(this.longString - this.content[i].length + 2).join(' ');
        }

        console.log(pipe + contentLine + pipe);
      }

      console.log(line);
      console.groupEnd();
    };
    Debug.prototype._printBreakpoints = function() {
      if(this.breakpoints.length) {
        this.printBlank();
        this.content.push('Breakpoints:');

        for(var i = 0; i < this.breakpoints.length; i++) {
          this.content.push(this.breakpoints[i]);
        }
      }
    };
    Debug.prototype._printTargeting = function() {
      if(this.targeting.length) {
        this.printBlank();
        this.content.push('Targeting:');

        for(var i = 0; i < this.targeting.length; i++) {
          this.content.push(this.targeting[i]);
        }
      }
    };
    Debug.prototype.printBlank = function () {
      this.content.push('[blank]');
    };
    Debug.prototype.countLongString = function (data) {
      for (var i = 0; i < data.length; i++) {
        if (this.longString < data[i].length) {
          this.longString = data[i].length;
        }
      }

      return this;
    };
    Debug.prototype.addLine = function (message) {
      this.content.push(message);
      return this;
    };
    Debug.prototype.addBreakpoints = function(browserSize, adSizes) {
      this.breakpoints.push(' - browser size: ' + this.formatSize(browserSize));
      this.breakpoints.push(' - ad sizes: ' + this.formatSize(adSizes));

      return this;
    };
    Debug.prototype.addTargeting = function(target, value) {
      this.targeting.push(' - target: ' + target);
      this.targeting.push(' - value: ' + '[' + value.toString() + ']');

      return this;
    };
    Debug.prototype.formatSize = function(sizes) {
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

    return Debug;
  }());

  DFP = (function() {
    /**
     *  Init DFP ads for element.
     *  @param: jQuery Element;
     *  @return: Object DFP;
     */
    function DFP(el) {
      this.allowedParameters = {
        adunit: {
          parse: false,
          required: true,
          default: false
        },
        outofpage: {
          parse: false,
          required: false,
          default: false
        },
        size: {
          parse: true,
          required: false,
          default: [0, 0]
        },
        mapping: {
          parse: true,
          required: false,
          default: false,
          filter: function(value) {

            cleanMapping(value);

            var numArray = false;

            if (!$.isArray(value)) {
              return value;
            }

            value.map(function(items) {
              items.map(function(item) {
                if ($.isNumeric(item)) {
                  numArray = true;
                }
              });
            });

            if (numArray) {
              return [value];
            }

            return value;
          }
        },
        targeting: {
          parse: true,
          required: false,
          default: false
        },
        adsenseColor: {
          parse: true,
          required: false,
          default: false
        },
        adsenseType: {
          parse: false,
          required: false,
          default: false
        },
        adsenseChannelIds: {
          parse: false,
          required: false,
          default: false
        },
        companion: {
          parse: false,
          required: false,
          default: false
        },
        name: {
          parse: false,
          required: false,
          default: 'tag'
        }
      };

      this.data = {};
      this.$el = el;
      this.id = this.genID(40);
      this.$el.attr('id', this.id);
      this.googleTag = null;
      this.disabled = false;
      this.defined = false;
    }

    /**
     *  Get attribute ID.
     *  @return: String ID;
     */
    DFP.prototype.getID = function () {
      return this.id;
    };

    /**
     *  Generate ID.
     *  @param: Int length generated ID;
     *  @return: String ID;
     */
    DFP.prototype.genID = function (lengthString) {
      var lengthString = lengthString || 20;

      return Array(lengthString + 1).join((Math.random().toString(36) + '00000000000000000').slice(2, 18)).slice(0, lengthString);
    };

    /**
     *  Execution dfp ads.
     *  @param: String [define, display];
     *  @default: void;
     *  @return: void;
     */
    DFP.prototype.exec = function (option) {
      this.data = this._parseData();

      switch (option) {
        case 'define':
          this.define();
          break;
        case 'display':
          this.display();
          break;
        default:
          this.define();
          this.display();
      }
    };

    /**
     *  Define dfp ads.
     *  @return: void;
     */
    DFP.prototype.define = function (prefix) {
      var name = '', debug ,prefix = prefix || '';

      name = 'DFPTag{prefix}: ' + this.data.name;
      debug = new Debug(name.replace('{prefix}', prefix));

      if (this.disabled || this.defined) {
        return;
      }
      this.defined = true;

      debug.addLine('Adunit: ' + this.data.adunit);
      debug.addLine('Element ID: ' + this.getID());

      if (this.data.outofpage) {
        this.googleTag = googletag.defineOutOfPageSlot(this.data.adunit, this.getID());
        debug.addLine('Out of page: true');
      } else {
        this.googleTag = googletag.defineSlot(this.data.adunit, this.data.size, this.getID());
        debug.addLine('Size: ' + debug.formatSize(this.data.size));
        debug.addLine('Out of page: false');

        if (this.data.companion) {
          this.googleTag = this.googleTag.addService(googletag.companionAds());
          debug.addLine('Companion: true');
        } else {
          debug.addLine('Companion: false');
        }
      }

      this._defineConfigure(debug);

      this.googleTag.addService(googletag.pubads());
      googletag.slots[this.getID()] = this.googleTag;

      debug.print();
    };

    /**
     *  Helper define dfp ads.
     *  @return: void;
     */
    DFP.prototype._defineConfigure = function (debug) {
      var mapping = {};

      if (this.data.adsenseType) {
        this.googleTag.set('adsense_ad_types', this.data.adsenseType);
        debug.addLine('Adsense ad types: ' + this.data.adsenseType);
      } else {
        debug.addLine('Adsense ad types: none');
      }
      if (this.data.adsenseChannelIds) {
        this.googleTag.set('adsense_channel_ids', this.data.adsenseChannelIds);
        debug.addLine('Adsense channel ids: ' + this.data.adsenseType);
      } else {
        debug.addLine('Adsense channel ids: none');
      }

      if (this.data.adsenseColor) {
        var adsenseColors = this.data.adsenseColor;

        for(var i = 0; i < adsenseColors.length; i++) {
          if (adsenseColors[i][1] === '') {
            continue;
          }
          this.googleTag.set('adsense_' + adsenseColors[i][0].toLowerCase() + '_color', adsenseColors[i][1]);
          debug.addLine('Adsense ' + adsenseColors[i][0] + ' color: ' + adsenseColors[i][1]);
        }
      } else {
        debug.addLine('Adsense color: none');
      }

      for (var j = 0; j < this.data.targeting.length; j++) {
        this.googleTag.setTargeting(this.data.targeting[j][0], this.data.targeting[j][1]);
        debug.addTargeting(this.data.targeting[j][0], this.data.targeting[j][1]);
      }

      if (this.data.mapping.length && this.data.outofpage === false) {
        mapping = googletag.sizeMapping();

        for (var i = 0; i < this.data.mapping.length; i++) {
          mapping.addSize(this.data.mapping[i][0], this.data.mapping[i][1]);
          debug.addBreakpoints(this.data.mapping[i][0], this.data.mapping[i][1]);
        }

        this.googleTag.defineSizeMapping(mapping.build());
      } else {
        debug.addLine('Breakpoints: none');
      }
    };

    /**
     *  Display dfp ads.
     *  @return: void;
     */
    DFP.prototype.display = function () {
      if (this.disabled) {
        return;
      }

      googletag.display(this.getID());
    };

    /**
     *  Clear dfp ads.
     *  @return: void;
     */
    DFP.prototype.clear = function () {
      if (this.disabled || this.googleTag === null) {
        return;
      }

      googletag.pubads().clear([this.googleTag]);
    };

    /**
     *  Refresh dfp ads.
     *  @return: void;
     */
    DFP.prototype.refresh = function () {
      var diff, debug;

      debug = new Debug('DFPTag (refresh): ' + this.data.name);

      if (this.disabled || this.googleTag === null) {
        debug.addLine('disabled: true');
        debug.print();
        return;
      }

      diff = this._diff();
      this.data = this._parseData();

      if (diff.modifyAdunit) {
        this.destroy();
        this.define(' (refresh)');
        this.display();
        return;
      }

      this.clear();

      debug.addLine('Adunit: ' + this.data.adunit);
      debug.addLine('Element ID: ' + this.getID());

      if (this.data.outofpage) {
        debug.addLine('Out of page: true');
      } else {
        debug.addLine('Out of page: false');

        if (this.data.companion) {
          debug.addLine('Companion: true');
        } else {
          debug.addLine('Companion: false');
        }
      }

      this._defineConfigure(debug);

      googletag.pubads().refresh([this.googleTag]);
      debug.print();
    };

    /**
     *  Destroy dfp ads.
     *  @return: void;
     */
    DFP.prototype.destroy = function () {
      if (this.disabled || this.googleTag === null) {
        return;
      }

      this.defined = false;
      googletag.destroySlots([this.googleTag]);
    };

    /**
     *  Check diff data attr.
     *  @return: Bool;
     */
    DFP.prototype._diff = function () {
      var data = this.data
        , key
        , newData = this._parseData()
        , isRefresh = false
        , modifyAdunit = false
        , master
        , second
        ;

      if (data.adunit !== newData.adunit ||
        data.size.toString() !== newData.size.toString()
      ) {
        modifyAdunit = true;
        isRefresh = true;
      } else {
        if (length(data) >= length(newData)) {
          master = data;
          second = newData;
        } else {
          master = newData;
          second = data;
        }

        for (key in master) {
          if (!master.hasOwnProperty(key)) {
            continue;
          }

          if (master[key].toString() !== second[key].toString()) {
            isRefresh = true;
            break;
          }
        }
      }

      return {
        isRefresh : isRefresh,
        modifyAdunit : modifyAdunit
      };
    };

    /**
     *  Parse data attr.
     *  @return: Object with params;
     */
    DFP.prototype._parseData = function () {
      var params = this.allowedParameters
        , key
        , value = {}
        , dataVal
        ;

        if (typeof this.$el.attr('disabled') !== 'undefined') {
          this.disabled = true;
        } else {
          this.disabled = false;
        }

        for (key in params) {
          if (!params.hasOwnProperty(key)) {
            continue;
          }

          dataVal = this.$el.attr('data-' + key) || '';

          if (params[key].required && dataVal.length <= 0)  {
            this.disabled = true;
            console.error('"{name}" is required data attribute.'.replace('{name}', key));
            break;
          }

          if (params[key].parse) {
            value[key] = dataVal.length ? this._read(dataVal) : params[key].default;

            if (typeof params[key].filter !== 'undefined') {
              value[key] = params[key].filter(value[key]);
            }
          } else {
            value[key] = dataVal.length ? dataVal : params[key].default;
          }
        }

        return value;
    };

    /**
     *  Transform values to JSON.
     *  @param: String value;
     *  @return: Mix (Object | Array);
     */
    DFP.prototype._read = function (value) {
      if (typeof value === 'undefined') {
        return [];
      }

      return new DFPHelper().read(value);
    };

    /**
     *  Transform JSON to Human string.
     *  @param: Array value;
     *  @return: String;
     */
    DFP.prototype._write = function (value) {
      if (typeof value === 'undefined') {
        return '';
      }

      return new DFPHelper().write(value);
    };

    return DFP;
  }());

  /**
   *  Initialization DFP and set params work dfp on this page.
   *
   *  @param: Object settings
   *    renderAsync: Bool,
   *    singleRequest: Bool,
   *    emptyDivs: Int range 0 - 2;
   *
   *  @default: Object settings
   *    renderAsync: false,
   *    singleRequest: false,
   *    emptyDivs: 0;
   *
   *  @return: void;
   */
  $.DFPInit = function(settings) {
    var options = $.extend({
      renderAsync: false,
      singleRequest: false,
      emptyDivs: 0
    }, settings), debug;

    debug = new Debug('DFP Initialization');

    if (options.renderAsync) {
      googletag.pubads().enableAsyncRendering();
      debug.addLine('Rendering: async');
    } else {
      googletag.pubads().enableSyncRendering();
      debug.addLine('Rendering: sync');
    }

    if (options.singleRequest) {
      googletag.pubads().enableSingleRequest();
      debug.addLine('Single Request: enable');
    } else {
      debug.addLine('Single Request: disabled');
    }

    switch (options.emptyDivs) {
      case 1:
        googletag.pubads().collapseEmptyDivs();
        debug.addLine('Collapse empty divs: Collapse only if no ad is served');
        break;
      case 2:
        googletag.pubads().collapseEmptyDivs(true);
        debug.addLine('Collapse empty divs: Expand only if an ad is served');
        break;
      default:
        debug.addLine('Collapse empty divs: Never');
    }
    googletag.enableServices();

    debug.addLine('Services: enable');
    debug.print();
  };

  /**
   *  Wrapper for render data in html
   *  @param: Array with ads Object;
   */
  $.fn.DFPrender = function(data) {
    var config = {
      tag: 'div',
      attr: {
        class: 'dfp-tags'
      },
      schema: {
        size: {},
        adunit: {},
        disabled: {
          type: 'attr'
        },
        machinename: {
          rename: 'name',
        },
        targeting: {
          rename: 'targeting',
          filter: function(value) {
            var result = [];

            for (var i = 0; i < value.length; i++) {
              result.push([value[i].target, value[i].value]);
            }

            return result;
          }
        },
        'breakpoints': {
          rename: 'mapping',
          filter: function(value) {
            var result = [];

            for (var i = 0; i < value.length; i++) {
              result.push([value[i].browser_size, value[i].ad_sizes]);
            }

            return result;
          }
        },
        'settings.adsense_ad_types': {
          rename: 'adsenseType',
        },
        'settings.adsense_channel_ids': {
          rename: 'adsenseChannelIds',
        },
        'settings.adsense_colors': {
          rename: 'adsenseColor',
          filter: function(value) {
            var result = [];

            for (var k in value) {
              if (!value.hasOwnProperty(k)) {
                continue;
              }

              result.push([k, value[k]]);
            }

            return result;
          }
        },
        'settings.out_of_page': {
          rename: 'outofpage'
        }
      },
      filter: function(value) {
        if($.type(value) === 'string' || $.type(value) === 'number') {
          return value;
        } else {
          return new DFPHelper().write(value);
        }
      }
    };

    $('[data-dfp-position]', $(this)).each(function() {
      var pos = $(this).attr('data-dfp-position');

      if (typeof data[pos] === 'undefined') {
        return;
      }

      $(this).dataRender(config, data[pos]);
    });
  };

  /**
   *  DFPHelper parse data.
   */
  DFPHelper = function () {};

  /**
   *  Transform values to JSON.
   *  @param: String value;
   *  @return: Mix (Object | Array);
   */
  DFPHelper.prototype.read = function(value) {
    if (typeof value === 'undefined') {
      return [];
    }

    return this._helperParse(value);
  };

  /**
   *  Transform JSON to Human string.
   *  @param: Array value;
   *  @return: String;
   */
  DFPHelper.prototype.write = function(value) {
    if (typeof value === 'undefined') {
      return '';
    }

    return this._helperStringify(value);
  };

  /**
   *  Helper parse data to JSON.
   *
   *  @example: data-size="728*90,970*90,320*50"                                   -> [[728, 90], [970, 90], [320, 50]]
   *  @example: data-mapping="0*0=320*50|779*0=970*90,728*90"                      -> [ [[0, 0], [320,50]],  [[779, 0], [[970, 90], [728,90]]]]
   *  @example: data-targeting="pos=728_1_a,testAd|ptype=homepage|reg=registered"> -> [[pos, [728_1_a,testAd]], [ptype, [homepage]]]
   *
   *  @param: String value;
   *
   *  @return: Array;
   */
  DFPHelper.prototype._helperParse = function (value) {
    var result = []
      , sign
      , splitedValue
      ;

    sign = this._helperParseGetSign(value) || '*';
    splitedValue = value.split(sign);

    if (splitedValue.length > 1) {
      if (this._helperParseGetSign(splitedValue.join('_'))) {
        for (var i = 0; i < splitedValue.length; i++) {
          result.push(this._helperParse(splitedValue[i]));
        }
      } else {
        result = splitedValue.map(function(item) {
          return ($.isNumeric(item)) ? parseInt(item, 10) : item;
        });
      }

      return result;
    }

    return value;
  };

  /**
   *  Search separator sign in string.
   *  @param: String value;
   *  @return: String sign;
   */
  DFPHelper.prototype._helperParseGetSign = function (value) {
    var signs = ['|', '=', ',', '*']
      , sign = false
      ;

    for (var i = 0; i < signs.length; i++) {
      if (value.indexOf(signs[i]) === -1) {
        continue;
      }

      sign = signs[i];
      break;
    }

    return sign;
  };

  /**
   *  Helper stringify data to Human string.
   *
   *  @example: [[728, 90], [970, 90], [320, 50]]                          -> data-size="728*90,970*90,320*50"
   *  @example: [[[0, 0], [320, 50]],  [[779, 0], [[970, 90], [728, 90]]]] -> data-mapping="0*0=320*50|779*0=970*90,728*90"
   *  @example: [[pos, [728_1_a, testAd]], [ptype, [homepage]]]            -> data-targeting="pos=728_1_a,testAd|ptype=homepage|reg=registered">
   *
   *  @param: Array value;
   *
   *  @return: String;
   */
  DFPHelper.prototype._helperStringify = function (value) {
    var result = [], sign = '|', concatValue, item, isNum = false;

    for (var i = 0; i < value.length; i++) {
      item = value[i];

      if ($.isArray(value[i]) && $.isNumeric(value[i][0]) && $.isNumeric(value[i][1])) {
        result.push(value[i].join('*'));
      } else if(this._helperFindArray(item)) {
        item = this._helperRecursiveStringify(value[i]);
      } else if ($.isNumeric(item)) {
        result.push(item);
      }
      if ($.isArray(item) && !$.isNumeric(value[i][0]) && !$.isNumeric(value[i][1])) {
        result.push(this._helperConcatPair(item[0], item[1]));
      }
      if ($.isArray(item) && !$.isNumeric(value[i][0]) && $.isNumeric(value[i][1])) {
        result.push(this._helperConcatPair(item[0], item[1]));
      }
    }

    concatValue = result.join('^');

    result.map(function(item) {
      if ($.isNumeric(item)) {
        isNum = true;
      }
    });

    if (isNum) {
      sign = '*';
    } else if ((concatValue.indexOf('*') === -1 || concatValue.indexOf(',') === -1) && concatValue.indexOf('=') === -1) {
      sign = ',';
    }

    return result.join(sign);
  };

  /**
   *  Stringify value.
   *  @param: Array value;
   *  @return: String value;
   */
  DFPHelper.prototype._helperRecursiveStringify = function (value, depth) {
    var result = [], depth = depth || 0;

    if ($.isArray(value)) {
      for (var i = 0; i < value.length; i++) {
        if (this._helperFindArray(value[i])) {
          result[i] = this._helperRecursiveStringify(value[i]);
        } else if ($.isArray(value[i])) {
          result[i] = this._helperConcatPair(value[i][0], value[i][1], depth + 1);
        } else {
          result[i] = value[i];
        }
      }
    }

    return result;
  };

  /**
   *  Concat pair {key, value}.
   *  @param: Mix {Array, String} key;
   *  @param: Mix {Array, String} value;
   *  @param: String isStrSign;
   *  @return: String value;
   */
  DFPHelper.prototype._helperConcatPair = function (key, value, depth) {
    var sign = '*';

    if ($.type(key) === 'string' || $.type(value) === 'string') {
      sign = depth >= 1 ? ',' : '=';
    }

    return [key, value].join(sign);
  };

  /**
   *  Find in array of array.
   *  @param: Array value;
   *  @return: Bool;
   */
  DFPHelper.prototype._helperFindArray = function(value) {
    for (var i = 0; i < value.length; i++) {
      if ($.isArray(value[i])) {
        return true;
      }
    }

    return false;
  };

  /**
   *  Initialization DFP ads on this page.
   *
   *  @param: Object settings
   *    exec : String enum [onlyDefine, onlyDisplay, defineAndDisplay],
   *    refresh : Bool;
   *
   *  @default: Object settings
   *    exec : defineAndDisplay,
   *    refresh : false;
   *
   *  @return: void;
   */
  $.fn.DFP = function(settings) {
    var options = $.extend({
      exec : 'defineAndDisplay',
      refresh : false,
      clear: false,
      destroy: false
    }, settings);

    $(this).each(function() {
      var id = $(this).attr('id')
        , item = null
        ;

      if (typeof DFPItems[id] === 'undefined') {
        item = new DFP($(this));
        DFPItems[item.getID()] = item;
      } else {
        item = DFPItems[id];
      }

      if (options.destroy) {
        item.destroy();
        return this;
      }

      if (options.clear) {
        item.clear();
        return this;
      }

      if (options.refresh) {
        item.refresh();
        return this;
      }

      switch (options.exec) {
        case 'onlyDefine':
          item.exec('define');
          break;
        case 'onlyDisplay':
          item.exec('display');
          break;
        default:
          item.exec();
      }
    });
  };

}(jQuery));
;
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
;
