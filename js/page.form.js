(function ($) {
  Drupal.behaviors.extendedSearch = {
    attach: function (context, settings) {
      // Prevent submission on "enter".
      $('form').keypress(function (event) {
        var key = event.keyCode || event.which;
        if (key == 13) {
          event.preventDefault();
          return false;
        }
      });

      // From http://www.zurb.com/playground/jquery-text-change-custom-event
      $.event.special.textchange = {

        setup: function (data, namespaces) {
          $(this).data('lastValue', this.contentEditable === 'true' ? $(this).html() : $(this).val());
          $(this).bind('keyup.textchange', $.event.special.textchange.handler);
          $(this).bind('cut.textchange paste.textchange input.textchange', $.event.special.textchange.delayedHandler);
        },

        teardown: function (namespaces) {
          $(this).unbind('.textchange');
        },

        handler: function (event) {
          $.event.special.textchange.triggerIfChanged($(this));
        },

        delayedHandler: function (event) {
          var element = $(this);
          setTimeout(function () {
            $.event.special.textchange.triggerIfChanged(element);
          }, 25);
        },

        triggerIfChanged: function (element) {
          var current = element[0].contentEditable === 'true' ? element.html() : element.val();
          if (current !== element.data('lastValue')) {
            element.trigger('textchange',  [element.data('lastValue')]);
            element.data('lastValue', current);
          }
        }
      };

      $.event.special.hastext = {

        setup: function (data, namespaces) {
          $(this).bind('textchange', $.event.special.hastext.handler);
        },

        teardown: function (namespaces) {
          $(this).unbind('textchange', $.event.special.hastext.handler);
        },

        handler: function (event, lastValue) {
          if ((lastValue === '') && lastValue !== $(this).val()) {
            $(this).trigger('hastext');
          }
        }
      };

      $.event.special.notext = {

        setup: function (data, namespaces) {
          $(this).bind('textchange', $.event.special.notext.handler);
        },

        teardown: function (namespaces) {
          $(this).unbind('textchange', $.event.special.notext.handler);
        },

        handler: function (event, lastValue) {
          if ($(this).val() === '' && $(this).val() !== lastValue) {
            $(this).trigger('notext');
          }
        }
      };
      
      // Hide exclude if no other keyword.
      var exclude = $('.form-item-full-text-search-exclude').hide();
      var fields = $('.form-item-full-text-search-all input, .form-item-full-text-search-any input, .form-item-full-text-search-exact input');      
      fields.bind('notext', function (event) {
        if ($(fields[0]).val() === '' && $(fields[1]).val() === '' && $(fields[2]).val() === '') {
          exclude.fadeOut();
        }
      });
      fields.bind('hastext', function (event) {
        exclude.fadeIn();
      });
      if ($(fields[0]).val() !== '' || $(fields[1]).val() !== '' || $(fields[2]).val() !== '') {
        exclude.fadeIn();
      }      
    }
  };
})(jQuery);