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
