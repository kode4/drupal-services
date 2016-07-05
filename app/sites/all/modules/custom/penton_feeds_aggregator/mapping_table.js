Drupal.behaviors.feeds = {
  attach: function (context, settings) {
    (function($) {
      if (typeof mapping != "undefined") {
        var initital = true;
        mapping = mapping || {map:[]};
        mappingTargets = mappingTargets || {};
        mappingSources = mappingSources || {};
        taxonomyVocabs = taxonomyVocabs || {};

        $("#edit-feeds-FeedsPentonAggregatorProcessor-feed-content-source-wrapper").mouseenter(function() {
          $.ajax({
            type: "POST",
            data: {action: "brands"},
            url: "/admin/content/penton_feeds_aggregator/mapping",
            success: function(msg) {
              var obj = JSON.parse(msg);
              var html = '';
              var keys = [];
              var value = $("#edit-feeds-FeedsPentonAggregatorProcessor-feed-content-source").val();
              $('#edit-feeds-FeedsPentonAggregatorProcessor-feed-content-source option').remove();
              for (k in obj){
                if (obj.hasOwnProperty(k)) {
                  keys.push(k);
                }
              }
              keys.sort();
              len = keys.length;
              for (i = 0; i < len; i++) {
                k = keys[i];
                html += '<option value ="' + k + '">' + obj[k] + '</option>'
              }
              $('#edit-feeds-FeedsPentonAggregatorProcessor-feed-content-source').append(html);
              $('#edit-feeds-FeedsPentonAggregatorProcessor-feed-content-source').val(value);
            }
          })
        });

        mapping.watch('map', function(prop,oldval,newval) {
          $("#edit-feeds-FeedsPentonAggregatorProcessor-feed-mapping").val(JSON.stringify(newval));
          return newval;
        });

        // Adding unique keys for initial mapping.
        $.each(mapping.map, function(index, element) {
          if (typeof(mapping.map[index].unique) === 'undefined') {
            mapping.map[index].unique = mappingSources[element.source].unique;
          }
        });

        function mappingTableDrow() {
          var table_wrapper = $("#mapping-table-wrapper");
          table_wrapper.html('');
          var sourceOptions = '';
          if (typeof mappingSources == 'string') {mappingSources = JSON.parse(mappingSources);}
          for (var $k in mappingSources) {sourceOptions += "<option value='" + $k + "'>" + mappingSources[$k].name + "</option>"}
          var targetOptions = '';
          if (typeof mappingTargets == 'string') { mappingTargets = JSON.parse(mappingTargets); }
          for (var $k in mappingTargets) {targetOptions += "<option value='" + $k + "'>" + mappingTargets[$k].name + "</option>"}

          table_wrapper.append
            ('<table style="border: 1px solid gray">' +
             '<tr class="" style="border: 1px solid gray"><td><strong><strong>Source</strong></td><td><strong>Target</strong></td><td><strong>Unique</strong></td><td><strong>Actions</strong></td></tr>' +
             '<tr class="" style="border: 1px solid gray"><td><span><select class="form-select" id="penton-mapping-source-select">' + sourceOptions + '</select></span></td>' +
             '<td><span><select id="penton-mapping-target-select" class="form-select">' + targetOptions + '</select></span></td>' +
             '<td></td>' +
             '<td><input type="button" class="teaser-button pull-right penton-mapping-add-button form-submit" value ="Add"/></td>' +
             '</tr> </table>');
          if (typeof mapping == 'string') {mapping = JSON.parse(mapping);}
          for (var $j in mapping.map) {
            var unique = false;
            if (typeof(mappingSources[mapping.map[$j].source].unique) != 'undefined') {
              unique = mappingSources[mapping.map[$j].source].unique;
            }
            table_wrapper.find('table tr:first').after(
                "<tr><td>" + mappingSources[mapping.map[$j].source].name + "</td>" +
                "<td>" + mappingTargets[mapping.map[$j].target].name + "</td>" +
                "<td><span>" + (unique ? "Unique" : "") + "</span></td>" +
                "<td><span><input type='button' data-index='" + $j + "' class='teaser-button pull-right penton-mapping-delete-button form-submit' value ='Delete'/></span></td>" +
                "</tr>");
          }
          $(".penton-mapping-delete-button").click(function(e){
            var index = $(e.target).attr("data-index");
            mapping.map.splice(index,1);
            mapping.map = jQuery.extend([], mapping.map);
            mappingTableDrow();
          });
          $(".penton-mapping-add-button").click(function(e){
            mapItem = {
              source:$("#penton-mapping-source-select").val(),
              target:$("#penton-mapping-target-select").val()
            };
            mapping.map.splice(0,0,mapItem);
            mapping.map = jQuery.extend([], mapping.map);
            mappingTableDrow();
          });
          // $("#taxonomy_fieldset .fieldset-wrapper .form-item").css({display:'none'});
          for(var $k in taxonomyVocabs){
            $("#taxonomy_fieldset #edit-feeds-FeedsPentonAggregatorProcessor-feed-taxonomy-" + taxonomyVocabs[$k].name + "-wrapper").css({display:'block'})
          }
        }

        mappingTableDrow();
        mapping.map = jQuery.extend([], mapping.map);
      }
    })(jQuery)
  }
}

/*
 * object.watch polyfill
 *
 * 2012-04-03
 *
 * By Eli Grey, http://eligrey.com
 * Public Domain.
 * NO WARRANTY EXPRESSED OR IMPLIED. USE AT YOUR OWN RISK.
 */

// object.watch
if (!Object.prototype.watch) {
  Object.defineProperty(Object.prototype, "watch", {
    enumerable: false,
    configurable: true,
    writable: false,
    value: function (prop, handler) {
      var oldval = this[prop],
      newval = oldval,
      getter = function() {
        return newval;
      },
      setter = function(val) {
        oldval = newval;
        return newval = handler.call(this, prop, oldval, val);
      };

      // can't watch constants
      if (delete this[prop]) {
        Object.defineProperty(this, prop, {
          get: getter,
          set: setter,
          enumerable: true,
          configurable: true
        });
      }
    }
  });
}

// object.unwatch
if (!Object.prototype.unwatch) {
  Object.defineProperty(Object.prototype, "unwatch", {
    enumerable: false,
    configurable: true,
    writable: false,
    value: function(prop) {
      var val = this[prop];
      // remove accessors
      delete this[prop];
      this[prop] = val;
    }
  });
}
