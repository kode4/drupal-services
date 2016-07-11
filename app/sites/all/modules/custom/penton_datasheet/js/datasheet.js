/**
 * @file
 * JS that is associated with the datasheet module
 *
 * Created by jameslinnell on 19/08/15.
 */

(function($){
    'use strict';

    Drupal.behaviors.clickableRows = {
        attach: function (context, settings) {
            $('.row-clickable', context).on('click', function(){
                window.location = $(this).data('link');
            });
        }
    };
    Drupal.behaviors.tableSorter = {
        attach: function (context, settings) {
            var $table = $('.tablesorter', context);
            if ($table.length) {
                $table.tablesorter({cssHeader: 'ts-header'});
                $table.bind("sortEnd",function() {
                    tweakColumnSort($table);
                });
                // Initialize sorting styles.
                if (!$table.find('th.headerSortDown, th.headerSortUp').length && $table.find('th[sort]').length) {
                    $table.find('th[sort]').addClass($table.find('th[sort]').attr('sort').toLowerCase() == 'asc' ? 'headerSortDown' : 'headerSortUp');
                    tweakColumnSort($table);
                }
            }
        }
    };
    // Reproduce sorting classes on sticky header
    var tweakColumnSort = function($table) {
        var $column = $table.find('.headerSortDown, .headerSortUp'),
            $stickyTable = $table.siblings('.sticky-header');
        if ($column.length) {
            $stickyTable.find('th.headerSortDown').removeClass('headerSortDown');
            $stickyTable.find('th.headerSortUp').removeClass('headerSortUp');
            var offset = $table.find('th').index($column);
            if (offset >= 0) {
                $stickyTable.find('th:eq(' + offset + ')').attr('class', $column.attr('class'));
            }
        }
    };
})(jQuery);
