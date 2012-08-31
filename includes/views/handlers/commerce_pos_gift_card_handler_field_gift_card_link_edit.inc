<?php

/**
 * Field handler to present a gift card edit link.
 */
class commerce_pos_gift_card_handler_field_gift_card_link_edit extends commerce_pos_gift_card_handler_field_gift_card_link {
  function construct() {
    parent::construct();

    $this->additional_fields['type'] = 'type';
    $this->additional_fields['uid'] = 'uid';
  }

  function render($values) {
    // Ensure the user has access to edit this gift card.
    $gift_card = commerce_pos_gift_card_new();
    $gift_card->gift_card_id = $this->get_value($values, 'gift_card_id');
    $gift_card->type = $this->get_value($values, 'type');
    $gift_card->uid = $this->get_value($values, 'uid');

    if (!commerce_pos_gift_card_access('update', $gift_card)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');

    return l($text, 'admin/commerce/gift_cards/' . $gift_card->gift_card_id . '/edit', array('query' => drupal_get_destination()));
  }
}
