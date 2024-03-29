<?php

/**
 * Field handler to translate a gift card type into its readable form.
 */
class commerce_pos_gift_card_handler_field_gift_card_type extends commerce_pos_gift_card_handler_field_gift_card {
  function option_definition() {
    $options = parent::option_definition();

    $options['use_raw_value'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['use_raw_value'] = array(
      '#title' => t('Use raw value'),
      '#description' => t('Check if you want to display the raw value instead of the human readable value.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['use_raw_value']),
    );
  }

  function render($values) {
    $type = $this->get_value($values);

    // Return the raw value if specified.
    if (!empty($this->options['use_raw_value'])) {
      return $this->sanitize_value($type);
    }

    $value = commerce_pos_gift_card_type_get_name($type);

    return $this->render_link($this->sanitize_value($value), $values);
  }
}
