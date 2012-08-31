<?php

/**
 * Argument handler to display gift card titles in View using gift card arguments.
 */
class commerce_pos_gift_card_handler_argument_gift_card_id extends views_handler_argument_numeric {
  function title_query() {
    $titles = array();
    $result = db_select('commerce_pos_gift_card', 'cgc')
      ->fields('cgc', array('title'))
      ->condition('cgc.gift_card_id', $this->value)
      ->execute();
    foreach ($result as $gift_card) {
      $titles[] = check_plain($gift_card->title);
    }
    return $titles;
  }
}
