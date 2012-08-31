<?php

/**
 * Field handler to present a gift card's operations links.
 */
class commerce_pos_gift_card_handler_field_gift_card_operations extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['gift_card_id'] = 'gift_card_id';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['add_destination'] = TRUE;

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['add_destination'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add a destination parameter to operations links so users return to this View on form submission.'),
      '#default_value' => $this->options['add_destination'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $gift_card_id = $this->get_value($values, 'gift_card_id');

    // Get the operations links.
    $links = menu_contextual_links('commerce-pos-gift-card', 'admin/commerce/gift_cards', array($gift_card_id));

    if (!empty($links)) {
      // Add the destination to the links if specified.
      if ($this->options['add_destination']) {
        foreach ($links as $id => &$link) {
          $link['query'] = drupal_get_destination();
        }
      }

      drupal_add_css(drupal_get_path('module', 'commerce_pos_gift_card') . '/theme/commerce_pos_gift_card.admin.css');
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
