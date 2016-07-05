var googletag = googletag || {},
  DFPCmd = {};

  googletag.cmd = googletag.cmd || [];
  googletag.slots = googletag.slots || {};
  DFPCmd.dfpManagers = {
    'context': []
  };
  DFPCmd.helper = {};

(function($) {
  'use strict';

  var CURRENT_COUNT_SHOW_ADS = 1, CURRENT_COUNT_SHOW_LEFT_RAIL = 1;

  DFPCmd.helper.inIterationAds = function(pos) {
    var pattern = new RegExp(/(300|728)\_(\d+)_.+/i);

    if(typeof pos === 'string' && pattern.test(pos)) {
      return true;
    } else if($.isArray(pos)) {
      for(var i = 0; i < pos.length; i++) {
        if(pattern.test(pos[i])) {
          return true;
        }
      }
    }

    return false;
  };

  DFPCmd.helper.replacePos = function(tag, num) {
    var pos = tag.getTargeting('pos'),
      str = '';

    if(typeof pos === 'string' && DFPCmd.helper.inIterationAds(pos)) {
      str = pos.split('_');
      str.splice(1, 1, num);
      pos = str.join('_');
    } else {
      for(var i = 0; i < pos.length; i++) {
        if(DFPCmd.helper.inIterationAds(pos[i])) {
          str = pos[i].split('_');
          str.splice(1, 1, num);
          pos[i] = str.join('_');
        }
      }
    }

    return pos;
  };

  DFPCmd.init = function() {
    var manager = new DFPManager(),
      pos = new DFPManagerPositions(),
      data = Drupal.settings.penton_custom_dfp,
      type = data.current_type,
      tag = null,
      dfpTags = {};

    pos.scan();

    if(!data.async_rendering) {
      manager.inSync();
    }
    if(!data.single_request) {
      manager.inSingleRequestOff();
    }
    if(typeof data.collapse_empty_divs !== 'undefined') {
      manager.setCollapseEmptyDivs(data.collapse_empty_divs);
    }
    manager.setPosition(pos);

    dfpTags = data.dfp_tags[type] ? data.dfp_tags[type] : [];
    manager.import(dfpTags);

    tag = manager.findTagByMachineName('pagewrap');
    if(tag) {
      tag.inDisabled();
    }
    manager.disableByPosition('left_rail_rect');

    if ($('.lazy-pagination .next a').length || $('.profile-info .load-more').length) {
      manager.disableByPosition('bottom_banner');
    }

    manager.fetch();
    manager.display();

    DFPCmd.dfpManagers.init = manager;
  };

  DFPCmd.initByContext = function(context, dataType) {
    var manager = new DFPManager(),
      pos = new DFPManagerPositions(),
      data = Drupal.settings.penton_custom_dfp,
      type = data.current_type;

    dataType = data.dfp_tags[type] ? data.dfp_tags[type] : [];

    pos.scanIn($(context));

    manager.offDefine();
    manager.setPosition(pos);
    manager.import(dataType);
    manager.fetch();
    manager.display();

    DFPCmd.dfpManagers.context.push(manager);

    return manager;
  };

  DFPCmd.initBottom = function() {
    var manager = DFPCmd.dfpManagers.init;
    manager.enableByPosition('bottom_banner');
    manager.fetchByPosition('bottom_banner');
    manager.displayByPosition('bottom_banner');
  };

  DFPCmd.initInUpdateTargeting = function(context, contentType) {
    var manager, pos, data, type, upData, tags, container, nid, ptype, terms, sterm, pterm, program;

    CURRENT_COUNT_SHOW_ADS++;

    manager = new DFPManager();
    pos     = new DFPManagerPositions();
    data    = Drupal.settings.penton_custom_dfp;
    type    = data.current_type;
    upData  = {};
    tags    = {};

    context = $(context);
    contentType = contentType || 'article';
    upData = (data.dfp_tags[contentType]) ? data.dfp_tags[contentType] : data.dfp_tags[type];

    pos.scanIn(context);
    manager.offDefine();
    manager.setPosition(pos);
    manager.import(upData);

    container = context.find('article');
    nid = container.attr('data-nid');
    ptype = container.attr('data-type');
    terms = container.attr('data-terms');
    pterm = container.attr('data-pterm');
    sterm = container.attr('data-sterm');
    program = container.attr('data-program');

    if(typeof nid === 'undefined') {
      return;
    }

    tags = manager.tags;
    for(var k in tags) {
      if(tags.hasOwnProperty(k)) {
        tags[k].setTargeting('pos', DFPCmd.helper.replacePos(tags[k], CURRENT_COUNT_SHOW_ADS));
        tags[k].setTargeting('ptype', ptype);
        tags[k].setTargeting('nid', nid);
        tags[k].setAdUnit(data.default_adunit + '/article/' + terms);

        if(pterm === '') {
          tags[k].clearTargeting('pterm');
        } else {
          tags[k].setTargeting('pterm', pterm);
        }
        if(sterm === '') {
          tags[k].clearTargeting('sterm');
        } else {
          tags[k].setTargeting('sterm', sterm.split('/'));
        }
        if(program === '') {
          tags[k].clearTargeting('program');
        } else {
          tags[k].setTargeting('program', program);
        }
      }
    }

    manager.fetch();
    manager.display();

    DFPCmd.dfpManagers.context.push(manager);
  };

  DFPCmd.updateLeftRailAndBottomAds = function(context, isLast) {
    var manager, tags, bottom_tags, container, nid, ptype, terms, data, pterm, sterm, program;

    CURRENT_COUNT_SHOW_LEFT_RAIL++;

    manager = DFPCmd.dfpManagers.init;
    data    = Drupal.settings.penton_custom_dfp;
    context = $(context);

    container = context.find('article');
    nid = container.attr('data-nid');
    ptype = container.attr('data-type');
    terms = container.attr('data-terms');
    pterm = container.attr('data-pterm');
    sterm = container.attr('data-sterm');
    program = container.attr('data-program');

    if(typeof nid === 'undefined') {
      return;
    }

    tags = manager.getTagsByPositionName('left_rail_rect');
    for(var k in tags) {
      if(tags.hasOwnProperty(k)) {
        tags[k].destroySlot();
        tags[k].setTargeting('pos', DFPCmd.helper.replacePos(tags[k], CURRENT_COUNT_SHOW_LEFT_RAIL));
        tags[k].setTargeting('ptype', ptype);
        tags[k].setTargeting('nid', nid);
        tags[k].setAdUnit(data.default_adunit + '/article/' + terms);

        if(pterm === '') {
          tags[k].clearTargeting('pterm');
        } else {
          tags[k].setTargeting('pterm', pterm);
        }
        if(sterm === '') {
          tags[k].clearTargeting('sterm');
        } else {
          tags[k].setTargeting('sterm', sterm.split('/'));
        }
        if(program === '') {
          tags[k].clearTargeting('program');
        } else {
          tags[k].setTargeting('program', program);
        }

        tags[k].define();
        tags[k].display();
      }
    }

    if (isLast) {
      bottom_tags = manager.getTagsByPositionName('bottom_banner');
      for (var k in bottom_tags) {
        if(!bottom_tags.hasOwnProperty(k)) { continue; }
        bottom_tags[k].inEnabled();
        bottom_tags[k].setTargeting('ptype', ptype);
        bottom_tags[k].setTargeting('nid', nid);
        bottom_tags[k].setAdUnit(data.default_adunit + '/article/' + terms);

        if(pterm === '') {
          bottom_tags[k].clearTargeting('pterm');
        } else {
          bottom_tags[k].setTargeting('pterm', pterm);
        }
        if(sterm === '') {
          bottom_tags[k].clearTargeting('sterm');
        } else {
          bottom_tags[k].setTargeting('sterm', sterm.split('/'));
        }
        if(program === '') {
          bottom_tags[k].clearTargeting('program');
        } else {
          bottom_tags[k].setTargeting('program', program);
        }

        bottom_tags[k].define();
        bottom_tags[k].display();
      }
    }
  };

  DFPCmd.refreshInitAds = function(context) {
    if(typeof DFPCmd.dfpManagers.init !== 'undefined') {
      var manager = DFPCmd.dfpManagers.init;
      manager.refreshByPosition('left_rail_rect');
      DFPCmd.initByContext(context);
    }
  };

  $(function() {
    if(!window.googletag && !googletag.apiReady) {
      return;
    }

    DFPCmd.init();
  });
}(jQuery));
