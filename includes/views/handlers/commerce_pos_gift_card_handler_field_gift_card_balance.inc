<?php

/**
 * Field handler for gift card balance
 */
class commerce_pos_gift_card_handler_field_gift_card_balance extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['gift_card_id'] = 'gift_card_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $gift_card_id = $this->get_value($values, 'gift_card_id');
    $gift_card = commerce_pos_gift_card_load($gift_card_id);
    $info = commerce_pos_gift_card_info($gift_card);
    return $info['format'];
  }
}
