var DFPManager = {};

(function($) {
  'use strict';

  DFPManager = (function() {
    function DFPManager() {
      this.objectManagerPositions = {};
      this.tags = {};
      this.positionWithTags = {};
      this.async = true;
      this.singleRequest = true;
      this.emptyDivs = 0;
      this.isDefine = true;
    }

    DFPManager.prototype.import = function(data) {
      if(this.objectManagerPositions === null) {
        return false;
      }

      for(var i = 0; i < data.length; i++) {
        var tag = new DFPTag(data[i]);

        if(!tag.settings.position) { continue; }
        if(!this.positionWithTags[tag.settings.position]) {
          this.positionWithTags[tag.settings.position] = {};
        }

        tag.setPosition(this.objectManagerPositions.getPositionByName(tag.settings.position));

        this.positionWithTags[tag.settings.position][tag.getMachineName()] = tag;
        this.tags[tag.getMachineName()] = tag;
      }

      return true;
    };
    DFPManager.prototype.setPosition = function(positionManager) {
      if(positionManager instanceof DFPManagerPositions) {
        this.objectManagerPositions = positionManager;
      }
      return this;
    };
    DFPManager.prototype.getTagByMachineName = function(tagMachineName) {
      return this.tags[tagMachineName];
    };
    DFPManager.prototype.findTagByMachineName = function(regExp) {
      var tags = this.tags,
        pattern = new RegExp(regExp);

      for(var k in tags) {
        if(tags.hasOwnProperty(k) && pattern.test(k)) {
          return tags[k];
        }
      }

      return false;
    };
    DFPManager.prototype.getTagsByPositionName = function(positionName) {
      return this.positionWithTags[positionName];
    };
    DFPManager.prototype.disableByPosition = function(positionName) {
      var tags = this.positionWithTags[positionName];

      for(var k in tags) {
        if(tags.hasOwnProperty(k)) {
          tags[k].inDisabled();
        }
      }
    };
    DFPManager.prototype.enableByPosition = function(positionName) {
      var tags = this.positionWithTags[positionName];

      for(var k in tags) {
        if(tags.hasOwnProperty(k)) {
          tags[k].inEnabled();
        }
      }
    };
    DFPManager.prototype.clearByPosition = function(positionName) {
      var tags = this.positionWithTags[positionName];

      for(var k in tags) {
        if(tags.hasOwnProperty(k)) {
          tags[k].clear();
        }
      }
    };
    DFPManager.prototype.refresh = function() {
      for(var k in this.tags) {
        if(this.tags.hasOwnProperty(k)) {
          this.tags[k].refresh();
        }
      }
      return this;
    };
    DFPManager.prototype.refreshByPosition = function(positionName) {
      var tags = this.positionWithTags[positionName];

      for(var k in tags) {
        if(tags.hasOwnProperty(k)) {
          tags[k].refresh();
        }
      }
    };
    DFPManager.prototype.fetch = function() {
      for(var k in this.tags) {
        if(this.tags.hasOwnProperty(k)) {
          this.tags[k].define();
        }
      }

      if(this.isDefine) {
        this.define();
      }
    };
    DFPManager.prototype.fetchByPosition = function(positionName) {
      var tags = this.positionWithTags[positionName];

      for(var k in tags) {
        if(tags.hasOwnProperty(k)) {
          tags[k].define();
        }
      }

      if(this.isDefine) {
        this.define();
      }
    };
    DFPManager.prototype.displayByPosition = function(positionName) {
      var tags = this.positionWithTags[positionName];

      for(var k in tags) {
        if(tags.hasOwnProperty(k)) {
          tags[k].display();
        }
      }
    };
    DFPManager.prototype.define = function() {
      var self = this,
        debug = new DFPDebug('DFPManager (define): ');

      googletag.cmd.push(function() {
        if(self.async) {
          debug.addLine('Async Rendering: TRUE');
          googletag.pubads().enableAsyncRendering();
        } else {
          debug.addLine('Async Rendering: FALSE');
          googletag.pubads().enableSyncRendering();
        }
        if(self.singleRequest) {
          debug.addLine('enableSingleRequest: TRUE');
          googletag.pubads().enableSingleRequest();
        } else {
          debug.addLine('enableSingleRequest: FALSE');
        }
        switch (self.emptyDivs) {
          case 1:
            debug.addLine('collapseEmptyDivs: Collapse');
            googletag.pubads().collapseEmptyDivs();
          break;

          case 2:
            debug.addLine('collapseEmptyDivs: Expand');
            googletag.pubads().collapseEmptyDivs(true);
          break;

          default:
            debug.addLine('collapseEmptyDivs: Never');
          break;
        }
      });

      debug.addLine('enableServices: TRUE');
      googletag.enableServices();

      debug.print();
    };
    DFPManager.prototype.display = function() {
      for(var k in this.tags) {
        if(this.tags.hasOwnProperty(k)) {
          this.tags[k].display();
        }
      }

      return this;
    };
    DFPManager.prototype.offDefine = function() {
      this.isDefine = false;
      return this;
    };
    DFPManager.prototype.inSync = function() {
      this.async = false;
      return this;
    };
    DFPManager.prototype.inAsync = function() {
      this.async = true;
      return this;
    };
    DFPManager.prototype.inSingleRequestOff = function() {
      this.singleRequest = false;
      return this;
    };
    DFPManager.prototype.setCollapseEmptyDivs = function(n) {
      this.emptyDivs = n || 0;
      return this;
    };

    return DFPManager;
  })();

}(jQuery));
