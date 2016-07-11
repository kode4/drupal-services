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
(function ($) {

/**
 * Drag and drop table rows with field manipulation.
 *
 * Using the drupal_add_tabledrag() function, any table with weights or parent
 * relationships may be made into draggable tables. Columns containing a field
 * may optionally be hidden, providing a better user experience.
 *
 * Created tableDrag instances may be modified with custom behaviors by
 * overriding the .onDrag, .onDrop, .row.onSwap, and .row.onIndent methods.
 * See blocks.js for an example of adding additional functionality to tableDrag.
 */
Drupal.behaviors.tableDrag = {
  attach: function (context, settings) {
    for (var base in settings.tableDrag) {
      $('#' + base, context).once('tabledrag', function () {
        // Create the new tableDrag instance. Save in the Drupal variable
        // to allow other scripts access to the object.
        Drupal.tableDrag[base] = new Drupal.tableDrag(this, settings.tableDrag[base]);
      });
    }
  }
};

/**
 * Constructor for the tableDrag object. Provides table and field manipulation.
 *
 * @param table
 *   DOM object for the table to be made draggable.
 * @param tableSettings
 *   Settings for the table added via drupal_add_dragtable().
 */
Drupal.tableDrag = function (table, tableSettings) {
  var self = this;

  // Required object variables.
  this.table = table;
  this.tableSettings = tableSettings;
  this.dragObject = null; // Used to hold information about a current drag operation.
  this.rowObject = null; // Provides operations for row manipulation.
  this.oldRowElement = null; // Remember the previous element.
  this.oldY = 0; // Used to determine up or down direction from last mouse move.
  this.changed = false; // Whether anything in the entire table has changed.
  this.maxDepth = 0; // Maximum amount of allowed parenting.
  this.rtl = $(this.table).css('direction') == 'rtl' ? -1 : 1; // Direction of the table.

  // Configure the scroll settings.
  this.scrollSettings = { amount: 4, interval: 50, trigger: 70 };
  this.scrollInterval = null;
  this.scrollY = 0;
  this.windowHeight = 0;

  // Check this table's settings to see if there are parent relationships in
  // this table. For efficiency, large sections of code can be skipped if we
  // don't need to track horizontal movement and indentations.
  this.indentEnabled = false;
  for (var group in tableSettings) {
    for (var n in tableSettings[group]) {
      if (tableSettings[group][n].relationship == 'parent') {
        this.indentEnabled = true;
      }
      if (tableSettings[group][n].limit > 0) {
        this.maxDepth = tableSettings[group][n].limit;
      }
    }
  }
  if (this.indentEnabled) {
    this.indentCount = 1; // Total width of indents, set in makeDraggable.
    // Find the width of indentations to measure mouse movements against.
    // Because the table doesn't need to start with any indentations, we
    // manually append 2 indentations in the first draggable row, measure
    // the offset, then remove.
    var indent = Drupal.theme('tableDragIndentation');
    var testRow = $('<tr/>').addClass('draggable').appendTo(table);
    var testCell = $('<td/>').appendTo(testRow).prepend(indent).prepend(indent);
    this.indentAmount = $('.indentation', testCell).get(1).offsetLeft - $('.indentation', testCell).get(0).offsetLeft;
    testRow.remove();
  }

  // Make each applicable row draggable.
  // Match immediate children of the parent element to allow nesting.
  $('> tr.draggable, > tbody > tr.draggable', table).each(function () { self.makeDraggable(this); });

  // Add a link before the table for users to show or hide weight columns.
  $(table).before($('<a href="#" class="tabledrag-toggle-weight"></a>')
    .attr('title', Drupal.t('Re-order rows by numerical weight instead of dragging.'))
    .click(function () {
      if ($.cookie('Drupal.tableDrag.showWeight') == 1) {
        self.hideColumns();
      }
      else {
        self.showColumns();
      }
      return false;
    })
    .wrap('<div class="tabledrag-toggle-weight-wrapper"></div>')
    .parent()
  );

  // Initialize the specified columns (for example, weight or parent columns)
  // to show or hide according to user preference. This aids accessibility
  // so that, e.g., screen reader users can choose to enter weight values and
  // manipulate form elements directly, rather than using drag-and-drop..
  self.initColumns();

  // Add mouse bindings to the document. The self variable is passed along
  // as event handlers do not have direct access to the tableDrag object.
  $(document).bind('mousemove', function (event) { return self.dragRow(event, self); });
  $(document).bind('mouseup', function (event) { return self.dropRow(event, self); });
};

/**
 * Initialize columns containing form elements to be hidden by default,
 * according to the settings for this tableDrag instance.
 *
 * Identify and mark each cell with a CSS class so we can easily toggle
 * show/hide it. Finally, hide columns if user does not have a
 * 'Drupal.tableDrag.showWeight' cookie.
 */
Drupal.tableDrag.prototype.initColumns = function () {
  for (var group in this.tableSettings) {
    // Find the first field in this group.
    for (var d in this.tableSettings[group]) {
      var field = $('.' + this.tableSettings[group][d].target + ':first', this.table);
      if (field.length && this.tableSettings[group][d].hidden) {
        var hidden = this.tableSettings[group][d].hidden;
        var cell = field.closest('td');
        break;
      }
    }

    // Mark the column containing this field so it can be hidden.
    if (hidden && cell[0]) {
      // Add 1 to our indexes. The nth-child selector is 1 based, not 0 based.
      // Match immediate children of the parent element to allow nesting.
      var columnIndex = $('> td', cell.parent()).index(cell.get(0)) + 1;
      $('> thead > tr, > tbody > tr, > tr', this.table).each(function () {
        // Get the columnIndex and adjust for any colspans in this row.
        var index = columnIndex;
        var cells = $(this).children();
        cells.each(function (n) {
          if (n < index && this.colSpan && this.colSpan > 1) {
            index -= this.colSpan - 1;
          }
        });
        if (index > 0) {
          cell = cells.filter(':nth-child(' + index + ')');
          if (cell[0].colSpan && cell[0].colSpan > 1) {
            // If this cell has a colspan, mark it so we can reduce the colspan.
            cell.addClass('tabledrag-has-colspan');
          }
          else {
            // Mark this cell so we can hide it.
            cell.addClass('tabledrag-hide');
          }
        }
      });
    }
  }

  // Now hide cells and reduce colspans unless cookie indicates previous choice.
  // Set a cookie if it is not already present.
  if ($.cookie('Drupal.tableDrag.showWeight') === null) {
    $.cookie('Drupal.tableDrag.showWeight', 0, {
      path: Drupal.settings.basePath,
      // The cookie expires in one year.
      expires: 365
    });
    this.hideColumns();
  }
  // Check cookie value and show/hide weight columns accordingly.
  else {
    if ($.cookie('Drupal.tableDrag.showWeight') == 1) {
      this.showColumns();
    }
    else {
      this.hideColumns();
    }
  }
};

/**
 * Hide the columns containing weight/parent form elements.
 * Undo showColumns().
 */
Drupal.tableDrag.prototype.hideColumns = function () {
  // Hide weight/parent cells and headers.
  $('.tabledrag-hide', 'table.tabledrag-processed').css('display', 'none');
  // Show TableDrag handles.
  $('.tabledrag-handle', 'table.tabledrag-processed').css('display', '');
  // Reduce the colspan of any effected multi-span columns.
  $('.tabledrag-has-colspan', 'table.tabledrag-processed').each(function () {
    this.colSpan = this.colSpan - 1;
  });
  // Change link text.
  $('.tabledrag-toggle-weight').text(Drupal.t('Show row weights'));
  // Change cookie.
  $.cookie('Drupal.tableDrag.showWeight', 0, {
    path: Drupal.settings.basePath,
    // The cookie expires in one year.
    expires: 365
  });
  // Trigger an event to allow other scripts to react to this display change.
  $('table.tabledrag-processed').trigger('columnschange', 'hide');
};

/**
 * Show the columns containing weight/parent form elements
 * Undo hideColumns().
 */
Drupal.tableDrag.prototype.showColumns = function () {
  // Show weight/parent cells and headers.
  $('.tabledrag-hide', 'table.tabledrag-processed').css('display', '');
  // Hide TableDrag handles.
  $('.tabledrag-handle', 'table.tabledrag-processed').css('display', 'none');
  // Increase the colspan for any columns where it was previously reduced.
  $('.tabledrag-has-colspan', 'table.tabledrag-processed').each(function () {
    this.colSpan = this.colSpan + 1;
  });
  // Change link text.
  $('.tabledrag-toggle-weight').text(Drupal.t('Hide row weights'));
  // Change cookie.
  $.cookie('Drupal.tableDrag.showWeight', 1, {
    path: Drupal.settings.basePath,
    // The cookie expires in one year.
    expires: 365
  });
  // Trigger an event to allow other scripts to react to this display change.
  $('table.tabledrag-processed').trigger('columnschange', 'show');
};

/**
 * Find the target used within a particular row and group.
 */
Drupal.tableDrag.prototype.rowSettings = function (group, row) {
  var field = $('.' + group, row);
  for (var delta in this.tableSettings[group]) {
    var targetClass = this.tableSettings[group][delta].target;
    if (field.is('.' + targetClass)) {
      // Return a copy of the row settings.
      var rowSettings = {};
      for (var n in this.tableSettings[group][delta]) {
        rowSettings[n] = this.tableSettings[group][delta][n];
      }
      return rowSettings;
    }
  }
};

/**
 * Take an item and add event handlers to make it become draggable.
 */
Drupal.tableDrag.prototype.makeDraggable = function (item) {
  var self = this;

  // Create the handle.
  var handle = $('<a href="#" class="tabledrag-handle"><div class="handle">&nbsp;</div></a>').attr('title', Drupal.t('Drag to re-order'));
  // Insert the handle after indentations (if any).
  if ($('td:first .indentation:last', item).length) {
    $('td:first .indentation:last', item).after(handle);
    // Update the total width of indentation in this entire table.
    self.indentCount = Math.max($('.indentation', item).length, self.indentCount);
  }
  else {
    $('td:first', item).prepend(handle);
  }

  // Add hover action for the handle.
  handle.hover(function () {
    self.dragObject == null ? $(this).addClass('tabledrag-handle-hover') : null;
  }, function () {
    self.dragObject == null ? $(this).removeClass('tabledrag-handle-hover') : null;
  });

  // Add the mousedown action for the handle.
  handle.mousedown(function (event) {
    // Create a new dragObject recording the event information.
    self.dragObject = {};
    self.dragObject.initMouseOffset = self.getMouseOffset(item, event);
    self.dragObject.initMouseCoords = self.mouseCoords(event);
    if (self.indentEnabled) {
      self.dragObject.indentMousePos = self.dragObject.initMouseCoords;
    }

    // If there's a lingering row object from the keyboard, remove its focus.
    if (self.rowObject) {
      $('a.tabledrag-handle', self.rowObject.element).blur();
    }

    // Create a new rowObject for manipulation of this row.
    self.rowObject = new self.row(item, 'mouse', self.indentEnabled, self.maxDepth, true);

    // Save the position of the table.
    self.table.topY = $(self.table).offset().top;
    self.table.bottomY = self.table.topY + self.table.offsetHeight;

    // Add classes to the handle and row.
    $(this).addClass('tabledrag-handle-hover');
    $(item).addClass('drag');

    // Set the document to use the move cursor during drag.
    $('body').addClass('drag');
    if (self.oldRowElement) {
      $(self.oldRowElement).removeClass('drag-previous');
    }

    // Hack for IE6 that flickers uncontrollably if select lists are moved.
    if (navigator.userAgent.indexOf('MSIE 6.') != -1) {
      $('select', this.table).css('display', 'none');
    }

    // Hack for Konqueror, prevent the blur handler from firing.
    // Konqueror always gives links focus, even after returning false on mousedown.
    self.safeBlur = false;

    // Call optional placeholder function.
    self.onDrag();
    return false;
  });

  // Prevent the anchor tag from jumping us to the top of the page.
  handle.click(function () {
    return false;
  });

  // Similar to the hover event, add a class when the handle is focused.
  handle.focus(function () {
    $(this).addClass('tabledrag-handle-hover');
    self.safeBlur = true;
  });

  // Remove the handle class on blur and fire the same function as a mouseup.
  handle.blur(function (event) {
    $(this).removeClass('tabledrag-handle-hover');
    if (self.rowObject && self.safeBlur) {
      self.dropRow(event, self);
    }
  });

  // Add arrow-key support to the handle.
  handle.keydown(function (event) {
    // If a rowObject doesn't yet exist and this isn't the tab key.
    if (event.keyCode != 9 && !self.rowObject) {
      self.rowObject = new self.row(item, 'keyboard', self.indentEnabled, self.maxDepth, true);
    }

    var keyChange = false;
    switch (event.keyCode) {
      case 37: // Left arrow.
      case 63234: // Safari left arrow.
        keyChange = true;
        self.rowObject.indent(-1 * self.rtl);
        break;
      case 38: // Up arrow.
      case 63232: // Safari up arrow.
        var previousRow = $(self.rowObject.element).prev('tr').get(0);
        while (previousRow && $(previousRow).is(':hidden')) {
          previousRow = $(previousRow).prev('tr').get(0);
        }
        if (previousRow) {
          self.safeBlur = false; // Do not allow the onBlur cleanup.
          self.rowObject.direction = 'up';
          keyChange = true;

          if ($(item).is('.tabledrag-root')) {
            // Swap with the previous top-level row.
            var groupHeight = 0;
            while (previousRow && $('.indentation', previousRow).length) {
              previousRow = $(previousRow).prev('tr').get(0);
              groupHeight += $(previousRow).is(':hidden') ? 0 : previousRow.offsetHeight;
            }
            if (previousRow) {
              self.rowObject.swap('before', previousRow);
              // No need to check for indentation, 0 is the only valid one.
              window.scrollBy(0, -groupHeight);
            }
          }
          else if (self.table.tBodies[0].rows[0] != previousRow || $(previousRow).is('.draggable')) {
            // Swap with the previous row (unless previous row is the first one
            // and undraggable).
            self.rowObject.swap('before', previousRow);
            self.rowObject.interval = null;
            self.rowObject.indent(0);
            window.scrollBy(0, -parseInt(item.offsetHeight, 10));
          }
          handle.get(0).focus(); // Regain focus after the DOM manipulation.
        }
        break;
      case 39: // Right arrow.
      case 63235: // Safari right arrow.
        keyChange = true;
        self.rowObject.indent(1 * self.rtl);
        break;
      case 40: // Down arrow.
      case 63233: // Safari down arrow.
        var nextRow = $(self.rowObject.group).filter(':last').next('tr').get(0);
        while (nextRow && $(nextRow).is(':hidden')) {
          nextRow = $(nextRow).next('tr').get(0);
        }
        if (nextRow) {
          self.safeBlur = false; // Do not allow the onBlur cleanup.
          self.rowObject.direction = 'down';
          keyChange = true;

          if ($(item).is('.tabledrag-root')) {
            // Swap with the next group (necessarily a top-level one).
            var groupHeight = 0;
            var nextGroup = new self.row(nextRow, 'keyboard', self.indentEnabled, self.maxDepth, false);
            if (nextGroup) {
              $(nextGroup.group).each(function () {
                groupHeight += $(this).is(':hidden') ? 0 : this.offsetHeight;
              });
              var nextGroupRow = $(nextGroup.group).filter(':last').get(0);
              self.rowObject.swap('after', nextGroupRow);
              // No need to check for indentation, 0 is the only valid one.
              window.scrollBy(0, parseInt(groupHeight, 10));
            }
          }
          else {
            // Swap with the next row.
            self.rowObject.swap('after', nextRow);
            self.rowObject.interval = null;
            self.rowObject.indent(0);
            window.scrollBy(0, parseInt(item.offsetHeight, 10));
          }
          handle.get(0).focus(); // Regain focus after the DOM manipulation.
        }
        break;
    }

    if (self.rowObject && self.rowObject.changed == true) {
      $(item).addClass('drag');
      if (self.oldRowElement) {
        $(self.oldRowElement).removeClass('drag-previous');
      }
      self.oldRowElement = item;
      self.restripeTable();
      self.onDrag();
    }

    // Returning false if we have an arrow key to prevent scrolling.
    if (keyChange) {
      return false;
    }
  });

  // Compatibility addition, return false on keypress to prevent unwanted scrolling.
  // IE and Safari will suppress scrolling on keydown, but all other browsers
  // need to return false on keypress. http://www.quirksmode.org/js/keys.html
  handle.keypress(function (event) {
    switch (event.keyCode) {
      case 37: // Left arrow.
      case 38: // Up arrow.
      case 39: // Right arrow.
      case 40: // Down arrow.
        return false;
    }
  });
};

/**
 * Mousemove event handler, bound to document.
 */
Drupal.tableDrag.prototype.dragRow = function (event, self) {
  if (self.dragObject) {
    self.currentMouseCoords = self.mouseCoords(event);

    var y = self.currentMouseCoords.y - self.dragObject.initMouseOffset.y;
    var x = self.currentMouseCoords.x - self.dragObject.initMouseOffset.x;

    // Check for row swapping and vertical scrolling.
    if (y != self.oldY) {
      self.rowObject.direction = y > self.oldY ? 'down' : 'up';
      self.oldY = y; // Update the old value.

      // Check if the window should be scrolled (and how fast).
      var scrollAmount = self.checkScroll(self.currentMouseCoords.y);
      // Stop any current scrolling.
      clearInterval(self.scrollInterval);
      // Continue scrolling if the mouse has moved in the scroll direction.
      if (scrollAmount > 0 && self.rowObject.direction == 'down' || scrollAmount < 0 && self.rowObject.direction == 'up') {
        self.setScroll(scrollAmount);
      }

      // If we have a valid target, perform the swap and restripe the table.
      var currentRow = self.findDropTargetRow(x, y);
      if (currentRow) {
        if (self.rowObject.direction == 'down') {
          self.rowObject.swap('after', currentRow, self);
        }
        else {
          self.rowObject.swap('before', currentRow, self);
        }
        self.restripeTable();
      }
    }

    // Similar to row swapping, handle indentations.
    if (self.indentEnabled) {
      var xDiff = self.currentMouseCoords.x - self.dragObject.indentMousePos.x;
      // Set the number of indentations the mouse has been moved left or right.
      var indentDiff = Math.round(xDiff / self.indentAmount);
      // Indent the row with our estimated diff, which may be further
      // restricted according to the rows around this row.
      var indentChange = self.rowObject.indent(indentDiff);
      // Update table and mouse indentations.
      self.dragObject.indentMousePos.x += self.indentAmount * indentChange * self.rtl;
      self.indentCount = Math.max(self.indentCount, self.rowObject.indents);
    }

    return false;
  }
};

/**
 * Mouseup event handler, bound to document.
 * Blur event handler, bound to drag handle for keyboard support.
 */
Drupal.tableDrag.prototype.dropRow = function (event, self) {
  // Drop row functionality shared between mouseup and blur events.
  if (self.rowObject != null) {
    var droppedRow = self.rowObject.element;
    // The row is already in the right place so we just release it.
    if (self.rowObject.changed == true) {
      // Update the fields in the dropped row.
      self.updateFields(droppedRow);

      // If a setting exists for affecting the entire group, update all the
      // fields in the entire dragged group.
      for (var group in self.tableSettings) {
        var rowSettings = self.rowSettings(group, droppedRow);
        if (rowSettings.relationship == 'group') {
          for (var n in self.rowObject.children) {
            self.updateField(self.rowObject.children[n], group);
          }
        }
      }

      self.rowObject.markChanged();
      if (self.changed == false) {
        $(Drupal.theme('tableDragChangedWarning')).insertBefore(self.table).hide().fadeIn('slow');
        self.changed = true;
      }
    }

    if (self.indentEnabled) {
      self.rowObject.removeIndentClasses();
    }
    if (self.oldRowElement) {
      $(self.oldRowElement).removeClass('drag-previous');
    }
    $(droppedRow).removeClass('drag').addClass('drag-previous');
    self.oldRowElement = droppedRow;
    self.onDrop();
    self.rowObject = null;
  }

  // Functionality specific only to mouseup event.
  if (self.dragObject != null) {
    $('.tabledrag-handle', droppedRow).removeClass('tabledrag-handle-hover');

    self.dragObject = null;
    $('body').removeClass('drag');
    clearInterval(self.scrollInterval);

    // Hack for IE6 that flickers uncontrollably if select lists are moved.
    if (navigator.userAgent.indexOf('MSIE 6.') != -1) {
      $('select', this.table).css('display', 'block');
    }
  }
};

/**
 * Get the mouse coordinates from the event (allowing for browser differences).
 */
Drupal.tableDrag.prototype.mouseCoords = function (event) {
  if (event.pageX || event.pageY) {
    return { x: event.pageX, y: event.pageY };
  }
  return {
    x: event.clientX + document.body.scrollLeft - document.body.clientLeft,
    y: event.clientY + document.body.scrollTop  - document.body.clientTop
  };
};

/**
 * Given a target element and a mouse event, get the mouse offset from that
 * element. To do this we need the element's position and the mouse position.
 */
Drupal.tableDrag.prototype.getMouseOffset = function (target, event) {
  var docPos   = $(target).offset();
  var mousePos = this.mouseCoords(event);
  return { x: mousePos.x - docPos.left, y: mousePos.y - docPos.top };
};

/**
 * Find the row the mouse is currently over. This row is then taken and swapped
 * with the one being dragged.
 *
 * @param x
 *   The x coordinate of the mouse on the page (not the screen).
 * @param y
 *   The y coordinate of the mouse on the page (not the screen).
 */
Drupal.tableDrag.prototype.findDropTargetRow = function (x, y) {
  var rows = $(this.table.tBodies[0].rows).not(':hidden');
  for (var n = 0; n < rows.length; n++) {
    var row = rows[n];
    var indentDiff = 0;
    var rowY = $(row).offset().top;
    // Because Safari does not report offsetHeight on table rows, but does on
    // table cells, grab the firstChild of the row and use that instead.
    // http://jacob.peargrove.com/blog/2006/technical/table-row-offsettop-bug-in-safari.
    if (row.offsetHeight == 0) {
      var rowHeight = parseInt(row.firstChild.offsetHeight, 10) / 2;
    }
    // Other browsers.
    else {
      var rowHeight = parseInt(row.offsetHeight, 10) / 2;
    }

    // Because we always insert before, we need to offset the height a bit.
    if ((y > (rowY - rowHeight)) && (y < (rowY + rowHeight))) {
      if (this.indentEnabled) {
        // Check that this row is not a child of the row being dragged.
        for (var n in this.rowObject.group) {
          if (this.rowObject.group[n] == row) {
            return null;
          }
        }
      }
      else {
        // Do not allow a row to be swapped with itself.
        if (row == this.rowObject.element) {
          return null;
        }
      }

      // Check that swapping with this row is allowed.
      if (!this.rowObject.isValidSwap(row)) {
        return null;
      }

      // We may have found the row the mouse just passed over, but it doesn't
      // take into account hidden rows. Skip backwards until we find a draggable
      // row.
      while ($(row).is(':hidden') && $(row).prev('tr').is(':hidden')) {
        row = $(row).prev('tr').get(0);
      }
      return row;
    }
  }
  return null;
};

/**
 * After the row is dropped, update the table fields according to the settings
 * set for this table.
 *
 * @param changedRow
 *   DOM object for the row that was just dropped.
 */
Drupal.tableDrag.prototype.updateFields = function (changedRow) {
  for (var group in this.tableSettings) {
    // Each group may have a different setting for relationship, so we find
    // the source rows for each separately.
    this.updateField(changedRow, group);
  }
};

/**
 * After the row is dropped, update a single table field according to specific
 * settings.
 *
 * @param changedRow
 *   DOM object for the row that was just dropped.
 * @param group
 *   The settings group on which field updates will occur.
 */
Drupal.tableDrag.prototype.updateField = function (changedRow, group) {
  var rowSettings = this.rowSettings(group, changedRow);

  // Set the row as its own target.
  if (rowSettings.relationship == 'self' || rowSettings.relationship == 'group') {
    var sourceRow = changedRow;
  }
  // Siblings are easy, check previous and next rows.
  else if (rowSettings.relationship == 'sibling') {
    var previousRow = $(changedRow).prev('tr').get(0);
    var nextRow = $(changedRow).next('tr').get(0);
    var sourceRow = changedRow;
    if ($(previousRow).is('.draggable') && $('.' + group, previousRow).length) {
      if (this.indentEnabled) {
        if ($('.indentations', previousRow).length == $('.indentations', changedRow)) {
          sourceRow = previousRow;
        }
      }
      else {
        sourceRow = previousRow;
      }
    }
    else if ($(nextRow).is('.draggable') && $('.' + group, nextRow).length) {
      if (this.indentEnabled) {
        if ($('.indentations', nextRow).length == $('.indentations', changedRow)) {
          sourceRow = nextRow;
        }
      }
      else {
        sourceRow = nextRow;
      }
    }
  }
  // Parents, look up the tree until we find a field not in this group.
  // Go up as many parents as indentations in the changed row.
  else if (rowSettings.relationship == 'parent') {
    var previousRow = $(changedRow).prev('tr');
    while (previousRow.length && $('.indentation', previousRow).length >= this.rowObject.indents) {
      previousRow = previousRow.prev('tr');
    }
    // If we found a row.
    if (previousRow.length) {
      sourceRow = previousRow[0];
    }
    // Otherwise we went all the way to the left of the table without finding
    // a parent, meaning this item has been placed at the root level.
    else {
      // Use the first row in the table as source, because it's guaranteed to
      // be at the root level. Find the first item, then compare this row
      // against it as a sibling.
      sourceRow = $(this.table).find('tr.draggable:first').get(0);
      if (sourceRow == this.rowObject.element) {
        sourceRow = $(this.rowObject.group[this.rowObject.group.length - 1]).next('tr.draggable').get(0);
      }
      var useSibling = true;
    }
  }

  // Because we may have moved the row from one category to another,
  // take a look at our sibling and borrow its sources and targets.
  this.copyDragClasses(sourceRow, changedRow, group);
  rowSettings = this.rowSettings(group, changedRow);

  // In the case that we're looking for a parent, but the row is at the top
  // of the tree, copy our sibling's values.
  if (useSibling) {
    rowSettings.relationship = 'sibling';
    rowSettings.source = rowSettings.target;
  }

  var targetClass = '.' + rowSettings.target;
  var targetElement = $(targetClass, changedRow).get(0);

  // Check if a target element exists in this row.
  if (targetElement) {
    var sourceClass = '.' + rowSettings.source;
    var sourceElement = $(sourceClass, sourceRow).get(0);
    switch (rowSettings.action) {
      case 'depth':
        // Get the depth of the target row.
        targetElement.value = $('.indentation', $(sourceElement).closest('tr')).length;
        break;
      case 'match':
        // Update the value.
        targetElement.value = sourceElement.value;
        break;
      case 'order':
        var siblings = this.rowObject.findSiblings(rowSettings);
        if ($(targetElement).is('select')) {
          // Get a list of acceptable values.
          var values = [];
          $('option', targetElement).each(function () {
            values.push(this.value);
          });
          var maxVal = values[values.length - 1];
          // Populate the values in the siblings.
          $(targetClass, siblings).each(function () {
            // If there are more items than possible values, assign the maximum value to the row.
            if (values.length > 0) {
              this.value = values.shift();
            }
            else {
              this.value = maxVal;
            }
          });
        }
        else {
          // Assume a numeric input field.
          var weight = parseInt($(targetClass, siblings[0]).val(), 10) || 0;
          $(targetClass, siblings).each(function () {
            this.value = weight;
            weight++;
          });
        }
        break;
    }
  }
};

/**
 * Copy all special tableDrag classes from one row's form elements to a
 * different one, removing any special classes that the destination row
 * may have had.
 */
Drupal.tableDrag.prototype.copyDragClasses = function (sourceRow, targetRow, group) {
  var sourceElement = $('.' + group, sourceRow);
  var targetElement = $('.' + group, targetRow);
  if (sourceElement.length && targetElement.length) {
    targetElement[0].className = sourceElement[0].className;
  }
};

Drupal.tableDrag.prototype.checkScroll = function (cursorY) {
  var de  = document.documentElement;
  var b  = document.body;

  var windowHeight = this.windowHeight = window.innerHeight || (de.clientHeight && de.clientWidth != 0 ? de.clientHeight : b.offsetHeight);
  var scrollY = this.scrollY = (document.all ? (!de.scrollTop ? b.scrollTop : de.scrollTop) : (window.pageYOffset ? window.pageYOffset : window.scrollY));
  var trigger = this.scrollSettings.trigger;
  var delta = 0;

  // Return a scroll speed relative to the edge of the screen.
  if (cursorY - scrollY > windowHeight - trigger) {
    delta = trigger / (windowHeight + scrollY - cursorY);
    delta = (delta > 0 && delta < trigger) ? delta : trigger;
    return delta * this.scrollSettings.amount;
  }
  else if (cursorY - scrollY < trigger) {
    delta = trigger / (cursorY - scrollY);
    delta = (delta > 0 && delta < trigger) ? delta : trigger;
    return -delta * this.scrollSettings.amount;
  }
};

Drupal.tableDrag.prototype.setScroll = function (scrollAmount) {
  var self = this;

  this.scrollInterval = setInterval(function () {
    // Update the scroll values stored in the object.
    self.checkScroll(self.currentMouseCoords.y);
    var aboveTable = self.scrollY > self.table.topY;
    var belowTable = self.scrollY + self.windowHeight < self.table.bottomY;
    if (scrollAmount > 0 && belowTable || scrollAmount < 0 && aboveTable) {
      window.scrollBy(0, scrollAmount);
    }
  }, this.scrollSettings.interval);
};

Drupal.tableDrag.prototype.restripeTable = function () {
  // :even and :odd are reversed because jQuery counts from 0 and
  // we count from 1, so we're out of sync.
  // Match immediate children of the parent element to allow nesting.
  $('> tbody > tr.draggable:visible, > tr.draggable:visible', this.table)
    .removeClass('odd even')
    .filter(':odd').addClass('even').end()
    .filter(':even').addClass('odd');
};

/**
 * Stub function. Allows a custom handler when a row begins dragging.
 */
Drupal.tableDrag.prototype.onDrag = function () {
  return null;
};

/**
 * Stub function. Allows a custom handler when a row is dropped.
 */
Drupal.tableDrag.prototype.onDrop = function () {
  return null;
};

/**
 * Constructor to make a new object to manipulate a table row.
 *
 * @param tableRow
 *   The DOM element for the table row we will be manipulating.
 * @param method
 *   The method in which this row is being moved. Either 'keyboard' or 'mouse'.
 * @param indentEnabled
 *   Whether the containing table uses indentations. Used for optimizations.
 * @param maxDepth
 *   The maximum amount of indentations this row may contain.
 * @param addClasses
 *   Whether we want to add classes to this row to indicate child relationships.
 */
Drupal.tableDrag.prototype.row = function (tableRow, method, indentEnabled, maxDepth, addClasses) {
  this.element = tableRow;
  this.method = method;
  this.group = [tableRow];
  this.groupDepth = $('.indentation', tableRow).length;
  this.changed = false;
  this.table = $(tableRow).closest('table').get(0);
  this.indentEnabled = indentEnabled;
  this.maxDepth = maxDepth;
  this.direction = ''; // Direction the row is being moved.

  if (this.indentEnabled) {
    this.indents = $('.indentation', tableRow).length;
    this.children = this.findChildren(addClasses);
    this.group = $.merge(this.group, this.children);
    // Find the depth of this entire group.
    for (var n = 0; n < this.group.length; n++) {
      this.groupDepth = Math.max($('.indentation', this.group[n]).length, this.groupDepth);
    }
  }
};

/**
 * Find all children of rowObject by indentation.
 *
 * @param addClasses
 *   Whether we want to add classes to this row to indicate child relationships.
 */
Drupal.tableDrag.prototype.row.prototype.findChildren = function (addClasses) {
  var parentIndentation = this.indents;
  var currentRow = $(this.element, this.table).next('tr.draggable');
  var rows = [];
  var child = 0;
  while (currentRow.length) {
    var rowIndentation = $('.indentation', currentRow).length;
    // A greater indentation indicates this is a child.
    if (rowIndentation > parentIndentation) {
      child++;
      rows.push(currentRow[0]);
      if (addClasses) {
        $('.indentation', currentRow).each(function (indentNum) {
          if (child == 1 && (indentNum == parentIndentation)) {
            $(this).addClass('tree-child-first');
          }
          if (indentNum == parentIndentation) {
            $(this).addClass('tree-child');
          }
          else if (indentNum > parentIndentation) {
            $(this).addClass('tree-child-horizontal');
          }
        });
      }
    }
    else {
      break;
    }
    currentRow = currentRow.next('tr.draggable');
  }
  if (addClasses && rows.length) {
    $('.indentation:nth-child(' + (parentIndentation + 1) + ')', rows[rows.length - 1]).addClass('tree-child-last');
  }
  return rows;
};

/**
 * Ensure that two rows are allowed to be swapped.
 *
 * @param row
 *   DOM object for the row being considered for swapping.
 */
Drupal.tableDrag.prototype.row.prototype.isValidSwap = function (row) {
  if (this.indentEnabled) {
    var prevRow, nextRow;
    if (this.direction == 'down') {
      prevRow = row;
      nextRow = $(row).next('tr').get(0);
    }
    else {
      prevRow = $(row).prev('tr').get(0);
      nextRow = row;
    }
    this.interval = this.validIndentInterval(prevRow, nextRow);

    // We have an invalid swap if the valid indentations interval is empty.
    if (this.interval.min > this.interval.max) {
      return false;
    }
  }

  // Do not let an un-draggable first row have anything put before it.
  if (this.table.tBodies[0].rows[0] == row && $(row).is(':not(.draggable)')) {
    return false;
  }

  return true;
};

/**
 * Perform the swap between two rows.
 *
 * @param position
 *   Whether the swap will occur 'before' or 'after' the given row.
 * @param row
 *   DOM element what will be swapped with the row group.
 */
Drupal.tableDrag.prototype.row.prototype.swap = function (position, row) {
  Drupal.detachBehaviors(this.group, Drupal.settings, 'move');
  $(row)[position](this.group);
  Drupal.attachBehaviors(this.group, Drupal.settings);
  this.changed = true;
  this.onSwap(row);
};

/**
 * Determine the valid indentations interval for the row at a given position
 * in the table.
 *
 * @param prevRow
 *   DOM object for the row before the tested position
 *   (or null for first position in the table).
 * @param nextRow
 *   DOM object for the row after the tested position
 *   (or null for last position in the table).
 */
Drupal.tableDrag.prototype.row.prototype.validIndentInterval = function (prevRow, nextRow) {
  var minIndent, maxIndent;

  // Minimum indentation:
  // Do not orphan the next row.
  minIndent = nextRow ? $('.indentation', nextRow).length : 0;

  // Maximum indentation:
  if (!prevRow || $(prevRow).is(':not(.draggable)') || $(this.element).is('.tabledrag-root')) {
    // Do not indent:
    // - the first row in the table,
    // - rows dragged below a non-draggable row,
    // - 'root' rows.
    maxIndent = 0;
  }
  else {
    // Do not go deeper than as a child of the previous row.
    maxIndent = $('.indentation', prevRow).length + ($(prevRow).is('.tabledrag-leaf') ? 0 : 1);
    // Limit by the maximum allowed depth for the table.
    if (this.maxDepth) {
      maxIndent = Math.min(maxIndent, this.maxDepth - (this.groupDepth - this.indents));
    }
  }

  return { 'min': minIndent, 'max': maxIndent };
};

/**
 * Indent a row within the legal bounds of the table.
 *
 * @param indentDiff
 *   The number of additional indentations proposed for the row (can be
 *   positive or negative). This number will be adjusted to nearest valid
 *   indentation level for the row.
 */
Drupal.tableDrag.prototype.row.prototype.indent = function (indentDiff) {
  // Determine the valid indentations interval if not available yet.
  if (!this.interval) {
    var prevRow = $(this.element).prev('tr').get(0);
    var nextRow = $(this.group).filter(':last').next('tr').get(0);
    this.interval = this.validIndentInterval(prevRow, nextRow);
  }

  // Adjust to the nearest valid indentation.
  var indent = this.indents + indentDiff;
  indent = Math.max(indent, this.interval.min);
  indent = Math.min(indent, this.interval.max);
  indentDiff = indent - this.indents;

  for (var n = 1; n <= Math.abs(indentDiff); n++) {
    // Add or remove indentations.
    if (indentDiff < 0) {
      $('.indentation:first', this.group).remove();
      this.indents--;
    }
    else {
      $('td:first', this.group).prepend(Drupal.theme('tableDragIndentation'));
      this.indents++;
    }
  }
  if (indentDiff) {
    // Update indentation for this row.
    this.changed = true;
    this.groupDepth += indentDiff;
    this.onIndent();
  }

  return indentDiff;
};

/**
 * Find all siblings for a row, either according to its subgroup or indentation.
 * Note that the passed-in row is included in the list of siblings.
 *
 * @param settings
 *   The field settings we're using to identify what constitutes a sibling.
 */
Drupal.tableDrag.prototype.row.prototype.findSiblings = function (rowSettings) {
  var siblings = [];
  var directions = ['prev', 'next'];
  var rowIndentation = this.indents;
  for (var d = 0; d < directions.length; d++) {
    var checkRow = $(this.element)[directions[d]]();
    while (checkRow.length) {
      // Check that the sibling contains a similar target field.
      if ($('.' + rowSettings.target, checkRow)) {
        // Either add immediately if this is a flat table, or check to ensure
        // that this row has the same level of indentation.
        if (this.indentEnabled) {
          var checkRowIndentation = $('.indentation', checkRow).length;
        }

        if (!(this.indentEnabled) || (checkRowIndentation == rowIndentation)) {
          siblings.push(checkRow[0]);
        }
        else if (checkRowIndentation < rowIndentation) {
          // No need to keep looking for siblings when we get to a parent.
          break;
        }
      }
      else {
        break;
      }
      checkRow = $(checkRow)[directions[d]]();
    }
    // Since siblings are added in reverse order for previous, reverse the
    // completed list of previous siblings. Add the current row and continue.
    if (directions[d] == 'prev') {
      siblings.reverse();
      siblings.push(this.element);
    }
  }
  return siblings;
};

/**
 * Remove indentation helper classes from the current row group.
 */
Drupal.tableDrag.prototype.row.prototype.removeIndentClasses = function () {
  for (var n in this.children) {
    $('.indentation', this.children[n])
      .removeClass('tree-child')
      .removeClass('tree-child-first')
      .removeClass('tree-child-last')
      .removeClass('tree-child-horizontal');
  }
};

/**
 * Add an asterisk or other marker to the changed row.
 */
Drupal.tableDrag.prototype.row.prototype.markChanged = function () {
  var marker = Drupal.theme('tableDragChangedMarker');
  var cell = $('td:first', this.element);
  if ($('span.tabledrag-changed', cell).length == 0) {
    cell.append(marker);
  }
};

/**
 * Stub function. Allows a custom handler when a row is indented.
 */
Drupal.tableDrag.prototype.row.prototype.onIndent = function () {
  return null;
};

/**
 * Stub function. Allows a custom handler when a row is swapped.
 */
Drupal.tableDrag.prototype.row.prototype.onSwap = function (swappedRow) {
  return null;
};

Drupal.theme.prototype.tableDragChangedMarker = function () {
  return '<span class="warning tabledrag-changed">*</span>';
};

Drupal.theme.prototype.tableDragIndentation = function () {
  return '<div class="indentation">&nbsp;</div>';
};

Drupal.theme.prototype.tableDragChangedWarning = function () {
  return '<div class="tabledrag-changed-warning messages warning">' + Drupal.theme('tableDragChangedMarker') + ' ' + Drupal.t('Changes made in this table will not be saved until the form is submitted.') + '</div>';
};

})(jQuery);
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
