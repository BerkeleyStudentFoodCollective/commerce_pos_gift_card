<?php

/**
 * Field handler to present a link to a gift cards.
 */
class commerce_pos_gift_card_handler_field_gift_card_link extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['gift_card_id'] = 'gift_card_id';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $gift_card_id = $this->get_value($values, 'gift_card_id');

    return l($text, 'admin/commerce/gift_cards/' . $gift_card_id);
  }
}
