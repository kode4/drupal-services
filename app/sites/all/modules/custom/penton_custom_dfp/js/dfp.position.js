var DFPManagerPositions = {},
  DFPPosition = {};

(function($) {
  'use strict';

  DFPPosition = (function() {
    function DFPPosition(el) {
      this.dataId = 'data-dfp-position';
      this.position = {};

      this.setElement(el);
    }

    DFPPosition.prototype.getByName = function(positionName) {
      this.position = $('[' + this.dataId + '="' + positionName + '"]');

      return this.position;
    };
    DFPPosition.prototype.setElement = function(el) {
      this.position = $(el);

      return this;
    };
    DFPPosition.prototype.getName = function() {
      return this.position.attr(this.dataId);
    };
    DFPPosition.prototype.addIn = function(el) {
      this.position.append(el);

      return this;
    };

    return DFPPosition;
  })();

  DFPManagerPositions = (function() {
    function DFPManagerPositions() {
      this.dataId = 'data-dfp-position';
      this.positions = {};
    }

    DFPManagerPositions.prototype.getPositionByName = function(positionName) {
      return this.positions[positionName];
    };
    DFPManagerPositions.prototype.addPosition = function(positionName, positionObject) {
      if(positionObject instanceof DFPPosition) {
        this.positions[positionName] = positionObject;
      }
      return this;
    };
    DFPManagerPositions.prototype.scan = function() {
      this.scanIn($('body'));

      return this;
    };
    DFPManagerPositions.prototype.scanIn = function(target) {
      var self = this;

      target.find('[' + self.dataId + ']').each(function() {
        self.positions[$(this).attr(self.dataId)] = new DFPPosition($(this));
      });

      return this;
    };

    return DFPManagerPositions;
  })();

}(jQuery));
