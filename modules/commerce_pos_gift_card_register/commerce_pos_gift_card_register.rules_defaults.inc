<?php

/**
 * @file
 * Default rules configuration for gift card payments.
 */

function commerce_pos_gift_card_register_default_rules_configuration_alter(&$rules) {
  $rule_set = $rules['commerce_pos_payment_validate_add'];
  //Make sure that the sign of the payment amount is always equal to the sign of the balance.

  //Prevent credit payments that are larger than the order balance
  $rule = rule();
  $rule->label = t('Prevent positive gift card payments larger than order balance.');
  $rule->active = TRUE;
  $rule->condition('data_is', array(
      'data:select' => 'commerce-payment-transaction:payment-method',
      'operator' => '==',
      'value' => 'commerce_pos_gift_card',
    ))
    ->condition('commerce_payment_order_balance_comparison', array(
      'commerce_order:select' => 'commerce-order',
      'operator' => '>',
      'value' => '0',
    ))
    ->condition('commerce_payment_order_balance_comparison', array(
      'commerce_order:select' => 'commerce-order',
      'operator' => '<',
      'value:select' => 'commerce-payment-transaction:amount',
    ))
    ->action('list_add', array(
        'list:select' => 'errors',
        'item' => t('You cannot add a gift card payment larger than the balance.'),
      ));

  $rule_set->rule($rule);

  //Prevent gift card payments that are larger than the order balance
  $rule = rule();
  $rule->label = t('Prevent negative gift card payments larger than order balance.');
  $rule->active = TRUE;
  $rule->condition('data_is', array(
    'data:select' => 'commerce-payment-transaction:payment-method',
    'operator' => '==',
    'value' => 'commerce_pos_gift_card',
    ))
    ->condition('commerce_payment_order_balance_comparison', array(
        'commerce_order:select' => 'commerce-order',
        'operator' => '<',
        'value' => '0',
  ))
  ->condition('commerce_payment_order_balance_comparison', array(
        'commerce_order:select' => 'commerce-order',
        'operator' => '>',
        'value:select' => 'commerce-payment-transaction:amount',
  ))
  ->action('list_add', array(
        'list:select' => 'errors',
        'item' => t('You cannot add a gift card refund in that amount.'),
      ));

  $rule_set->rule($rule);

  return $rules;

}
