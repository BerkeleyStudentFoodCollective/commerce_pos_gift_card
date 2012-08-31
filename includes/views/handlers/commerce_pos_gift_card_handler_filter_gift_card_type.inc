<?php

/**
 * Filter by gift card type.
 */
class commerce_pos_gift_card_handler_filter_gift_card_type extends views_handler_filter_in_operator {
  // Display a list of gift card types in the filter's options.
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Gift card type');
      $this->value_options = commerce_pos_gift_card_type_get_name();
    }
  }
}
