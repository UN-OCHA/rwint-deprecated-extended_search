(function ($) {
  Drupal.behaviors.extendedSearch = {
    attach: function (context, settings) {          
      function showInput(select) {
        var group = select.id.substring(5, select.id.indexOf('-', 5));
        var value = select.value.replace(/[_ ]/g, '-');
        var target = '.extended-search-filter-input-' + group + '-' + value;
        $('.extended-search-filter-input-' + group + ':not(' + target + ')').hide();
        $(target).show();
      }
      
      $('select.extended-search-filter-select').change(function (event) {
        showInput(this);
      }).each(function () {showInput(this);});
    }
  };
})(jQuery);