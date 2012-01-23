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
    }
  };
})(jQuery);