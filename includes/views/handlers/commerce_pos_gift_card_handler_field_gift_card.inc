<?php

/**
 * @file
 * Contains the basic gift card field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a gift card.
 */
class commerce_pos_gift_card_handler_field_gift_card extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);

    if (!empty($this->options['link_to_gift_card'])) {
      $this->additional_fields['gift_card_id'] = 'gift_card_id';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_gift_card'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Provide the link to gift card option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_gift_card'] = array(
      '#title' => t("Link this field to the gift card's administrative view page"),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_gift_card']),
    );
  }

  /**
   * Render whatever the data is as a link to the gift card.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_gift_card']) && $data !== NULL && $data !== '') {
      $gift_card_id = $this->get_value($values, 'gift_card_id');
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'admin/commerce/gift_cards/' . $gift_card_id;
    }

    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
