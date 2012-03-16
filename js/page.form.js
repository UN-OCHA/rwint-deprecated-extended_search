(function ($) {
  Drupal.behaviors.extendedSearch = {
    attach: function (context, settings) {
      $('form').keypress(function (event) {
        var key = event.keyCode || event.which;
        if (key == 13) {
          event.preventDefault();
          return false;
        }
      });
    }
  };
})(jQuery);