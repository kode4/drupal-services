(function($) {
  'use strict';

  $(function() {
    var alert, popup, legal;

    legal = new LegalCommunication();

    if(legal.isNotDisable() && legal.isLogin() && legal.isPopup()) {
      legal.removeIndented();
      popup = new LegalPopup();
      popup.show();
      popup.events(legal);
    } else if(legal.isNotDisable() && legal.isLogin()) {
      popup = new LegalAlert();
      popup.show();
      popup.events(legal);
    }

    if(!legal.isLogin()) {
      legal.getMessage(function(self, data) {
        self.selfEl.hide().html(data);

        if(self.isPopup()) {
          popup = new LegalPopup();
          popup.show();
          popup.events(self);
        } else {
          self.selfEl.show();
          self.addIndented();

          alert = new LegalAlert();
          alert.show(function() {
            alert.events(self);
          });
        }
      });
    }
  });
}(jQuery));
