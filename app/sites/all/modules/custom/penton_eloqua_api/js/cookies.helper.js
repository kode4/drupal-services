(function($) {
  'use strict';

  if (typeof $.cookie === 'undefined') return;

  var fields = Drupal.settings.penton_eloqua_api.fields;

  function parseQuery(search) {
    var args = search.substring(1).split('&'),
      argsParsed = {}, i, arg, kvp, key, value;

    for (i = 0; i < args.length; i++) {
      arg = args[i];

      if (-1 === arg.indexOf('=')) {
        argsParsed[decodeURIComponent(arg).trim()] = true;
      } else {
        kvp = arg.split('=');
        key = decodeURIComponent(kvp[0]).trim();
        value = decodeURIComponent(kvp[1]).trim();
        argsParsed[key] = value;
      }
    }

    return argsParsed;
  }

  Drupal.Eloqua = {
    get: function(name) {
      if (fields.indexOf(name)  === -1) return null;
      return $.cookie(name);
    },
    getAll: function() {
      var params = {};

      for (var i = 0, max = fields.length; i < max; i++) {
        var val = Drupal.Eloqua.get(fields[i]);

        if (val) {
          params[fields[i]] = val;
        }
      }

      return params;
    },
    set: function(name, value) {
      if (fields.indexOf(name)  === -1) return false;
      $.cookie(name, value);
      return true;
    },
    findAll: function() {
      var allParams = parseQuery(location.search);

      for (var k in allParams) {
        if (!allParams.hasOwnProperty(k)) continue;
        Drupal.Eloqua.set(k.toLowerCase(), allParams[k]);
      }
    }
  };

  Drupal.Eloqua.findAll();

}(jQuery));
