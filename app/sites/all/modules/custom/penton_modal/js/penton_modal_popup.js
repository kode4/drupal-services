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
