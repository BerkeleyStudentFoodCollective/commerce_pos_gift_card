<?php

/**
 * @file
 * Builds placeholder replacement tokens for gift card-related data.
 */


/**
 * Implements hook_token_info().
 */
function commerce_pos_gift_card_token_info() {
  $type = array(
    'name' => t('Gift Cards'),
    'description' => t('Tokens related to individual gift cards.'),
    'needs-data' => 'commerce-pos-gift-card',
  );

  // Tokens for gift cards.
  $gift_card = array();

  $gift_card['gift-card-id'] = array(
    'name' => t('Gift card ID'),
    'description' => t('The internal numeric ID of the gift card.'),
  );
  $gift_card['card-number'] = array(
    'name' => t('Gift card number'),
    'description' => t('The customer-facing card number.'),
  );
  $gift_card['type'] = array(
    'name' => t('Type'),
    'description' => t('The machine name of the gift card type.'),
  );
  $gift_card['type-name'] = array(
    'name' => t('Type name'),
    'description' => t('The human readable name of the gift card type.'),
  );

  // Chained tokens for gift cards.
  $gift_card['creator'] = array(
    'name' => t('Creator'),
    'description' => t('The creator of the gift card.'),
    'type' => 'user',
  );
  $gift_card['created'] = array(
    'name' => t('Date created'),
    'description' => t('The date the gift card was created.'),
    'type' => 'date',
  );
  $gift_card['changed'] = array(
    'name' => t('Date updated'),
    'description' => t('The date the gift card was last updated.'),
    'type' => 'date',
  );

  return array(
    'types' => array('commerce-pos-gift-card' => $type),
    'tokens' => array('commerce-pos-gift-card' => $gift_card),
  );
}

/**
 * Implements hook_tokens().
 */
function commerce_pos_gift_card_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'commerce-pos-gift-card' && !empty($data['commerce-pos-gift-card'])) {
    $gift_card = $data['commerce-pos-gift-card'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Simple key values on the gift card.
        case 'gift-card-id':
          $replacements[$original] = $gift_card->gift_card_id;
          break;

        case 'card-number':
          $replacements[$original] = $sanitize ? check_plain($gift_card->card_number) : $gift_card->card_number;
          break;

        case 'type':
          $replacements[$original] = $sanitize ? check_plain($gift_card->type) : $gift_card->type;
          break;

        case 'type-name':
          $replacements[$original] = $sanitize ? check_plain(commerce_pos_gift_card_type_get_name($gift_card->type)) : commerce_pos_gift_card_type_get_name($gift_card->type);
          break;

        // Default values for the chained tokens handled below.
        case 'creator':
          if (!$gift_card->uid) {
            $name = variable_get('anonymous', t('Anonymous'));
          }
          else {
            $creator = user_load($gift_card->uid);
            $name = $creator->name;
          }
          $replacements[$original] = $sanitize ? filter_xss($name) : $name;
          break;
        case 'created':
          $replacements[$original] = format_date($gift_card->created, 'medium', '', NULL, $language_code);
          break;

        case 'changed':
          $replacements[$original] = format_date($gift_card->changed, 'medium', '', NULL, $language_code);
          break;
      }
    }

    if ($creator_tokens = token_find_with_prefix($tokens, 'creator')) {
      $creator = user_load($gift_card->uid);
      $replacements += token_generate('user', $creator_tokens, array('user' => $creator), $options);
    }

    foreach (array('created', 'changed') as $date) {
      if ($created_tokens = token_find_with_prefix($tokens, $date)) {
        $replacements += token_generate('date', $created_tokens, array('date' => $gift_card->{$date}), $options);
      }
    }
  }

  return $replacements;
}
