(function ($) {
  Drupal.behaviors.extendedSearch = {
    attach: function (context, settings) {
      Drupal.theme.tableDragChangedWarning = function () {return '';};
      
      $('select.extended-search-filter-category-select').change(function (event) {
        var self = $(this);
        var value = self.val().replace(/[_ ]/g, '-');
        var target = '.extended-search-filter-input-' + value;
        $('.extended-search-filter-input').addClass('extended-search-filter-input-hidden');
        $(target + ' .extended-search-filter-input').removeClass('extended-search-filter-input-hidden');
      });
      
      /* Full Text Search Query */
      function get_text_query() {
        var query = [];
        
        var text_search_all = $('.form-item-full-text-search-all input').val().trim();
        if (text_search_all !== '') {
          query.push(text_search_all.replace(/\s+/g, ' AND '));
        }
        
        var text_search_exact = $('.form-item-full-text-search-exact input').val().trim();
        if (text_search_exact !== '') {
          query.push('"' + text_search_exact + '"');
        }
        
        var text_search_any = $('.form-item-full-text-search-any input').val().trim();
        if (text_search_any !== '') {
          query.push('(' + text_search_any.replace(/\s+/g, ' OR ') + ')');
        }
        
        var text_search_exclude = $('.form-item-full-text-search-exclude input').val().trim();
        if (text_search_exclude !== '') {
          query.push('NOT ' + text_search_exclude.replace(/\s+/g, ' AND NOT '));
        }
        
        return query.length > 0 ? [{label:'Text', query: query.join(' AND ')}] : [];
      }
      
      /* Filter Query */
      function get_filter_query() {
        var query = [];
        
        $('#extended-search-filter-selection fieldset > .fieldset-content > .form-item').each(function (index, element) {
          element = $(element);
          var label = element.children('label').text();
          
          var groups = [];
          var group_index = 0;
          var sub_query = [];
          
          element.find('tbody tr').each(function (index, element) {
            element = $(element);
            var operator = element.find('.extended-search-filter-operator').val();
            var value = element.find('.extended-search-filter-value').text();
            
            if (index === 0) {
              groups[group_index] = {operator:'', values:[]};
            }
            else if (operator !== 'or') {
              groups[++group_index] = {operator:operator, values:[]};
            }
            
            groups[group_index].values.push(value);
          });
          
          for (var i = 0, l = groups.length; i < l; i++) {
            var operator = groups[i].operator === 'not' ? 'NOT ' : '';
            var values = groups[i].values.length > 1 ? '(' + groups[i].values.join(' OR ') + ')' : groups[i].values[0];
            sub_query.push(operator + values);
          }
          
          query.push({label:label, query:sub_query.join(' AND ')});
        });
        
        return query;
      }
      
      /* Update "Your search query" */
      function display_search_query() {
        var text_query = get_text_query();
        var filter_query = get_filter_query();
        
        var queries = text_query.concat(filter_query);

        var html = '';
        if (queries.length > 0) {
          for (var i = 0, l = queries.length; i < l; i++) {
            html += '<div class="extended-search-query">';
            html += '<div class="extended-search-query-label">' + queries[i].label + '</div>';
            html += '<div class="extended-search-query-query"><pre>' + queries[i].query + '</pre></div>';
            html += "</div>\n";
          }
        }
        else {
          html = '<em>Enter keywords and add filters below and your search query will appear here.</em>';
        }
        $('#extended-search-search-query').html(html);
      }
      
      display_search_query();
      
      $('#edit-full-text-search input').bind('keyup cut paste input', display_search_query);
      $('.extended-search-filter-operator, .extended-search-filter-weight-cell').change(display_search_query);
    }
  };
})(jQuery);