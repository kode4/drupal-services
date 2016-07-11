var eloquaTrackingEnabled = false;
var eloquaSiteId = '';

// Returns input with customer GUID to paste into form.
function getEloquaCustomerGUIDinput(callback) {
  callback = callback || $.noop;
  if (!eloquaTrackingEnabled || typeof eloquaSiteId === 'undefined' || !eloquaSiteId) {
    return;
  }
  _getCustomerGUID(function(GUID) {
    var customerGUIDinput = document.createElement('input');
    customerGUIDinput.type = 'hidden';
    customerGUIDinput.name = 'elqCustomerGUID';
    customerGUIDinput.value = GUID;
    return callback(customerGUIDinput);
  });
}

// Wrapper function for GetElqCustomerGUID.
function _getCustomerGUID(callback) {
  callback = callback || $.noop;
  _requestGUIDfunction(function() {
    return callback(GetElqCustomerGUID());
  });
}

// Makes a request for GetElqCustomerGUID function to Eloqua.
// Replaces _elqQ.push(['elqGetCustomerGUID']) because we need
// to implement onload callback.
function _requestGUIDfunction(callback) {
  callback = callback || $.noop;
  if (typeof GetElqCustomerGUID === 'function') {
    return callback();
  }
  var host = '//s' + eloquaSiteId + '.t.eloqua.com/';
  var url = 'visitor/v200/svrGP';
  var dat = new Date;
  var time = dat.getMilliseconds();
  var get = '?pps=70&siteid=' + eloquaSiteId + '&ref=' + encodeURI(document.referrer) + '&ms=' + time;
  var f = document.createElement('script');
  f.type = 'text/javascript';
  f.src = host + url + get;
  f.async = true;
  f.onload = function() {
    if (typeof GetElqCustomerGUID !== 'function') {
      console.log('Could not retreive GetElqCustomerGUID function');
      return;
    }
    return callback();
  }
  document.getElementsByTagName('head')[0].appendChild(f)
}

(function($) {
  Drupal.behaviors.penton_eloqua_api = {
    attach: function (context, settings) {
      var elqSettings = settings.penton_eloqua_api;
      eloquaTrackingEnabled = elqSettings.tracking_enabled;
      if (typeof elqSettings === 'undefined' || !eloquaTrackingEnabled) {
        return;
      }
      eloquaSiteId = elqSettings.eloqua_site_id;
      if (typeof eloquaSiteId === 'undefined' || !eloquaSiteId) {
        return;
      }

      window._elqQ = window._elqQ || [];
      window._elqQ.push(['elqSetSiteId', eloquaSiteId]);
      window._elqQ.push(['elqTrackPageView']);

      var s = document.createElement('script'); s.type = 'text/javascript'; s.async = true;
      s.src = '//img.en25.com/i/elqCfg.min.js';
      var x = document.getElementsByTagName('script')[0]; x.parentNode.insertBefore(s, x);
    }
  }
})(jQuery);
;
