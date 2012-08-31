
(function($) {

  /**
   * Set up the accordion on the gift card dialog.
   */

  Drupal.behaviors.commercePosGiftCardRegister = {
      attach: function(context, settings) {
        var container = $('.commerce-pos-gift-card-register-dialog-section', context).parent('.commerce-pos-gift-card-register-dialog-sections');
        var initAction = function(event, ui) {
          var action = $('.ui-accordion-content-active .commerce-pos-gift-card-register-action', event.target).val();
          $('.commerce-pos-new-action-name').val(action);
        };
        var changeAction = function(event, ui) {
          var action = $('.commerce-pos-gift-card-register-action', ui.newContent).val();
          $('.commerce-pos-new-action-name').val(action);
        };
        var setFocus = function(context) {
          var input = $('.ui-accordion-content-active input[type="text"]', context).select();
        };
        
        var options = {
            icons : false,
            active : ".option-active",
            change : function(event, ui) {changeAction(event, ui); setFocus(container);}, 
            create : function(event, ui) {initAction(event, ui); setFocus(container);}
        };        
        
        container.once('accordion').accordion(options);
        
        //Reset commands when closing the dialog.
        //(this probably should be in the commerce pos code).
        $('.commerce-pos-modal').bind('dialogclose', function (event, ui) {
          $('.commerce-pos-new-action-name').val('');
          $('.commerce-pos-gift-card-register-action-name').val('');
        });
        
      }
  };
  
})(jQuery);
