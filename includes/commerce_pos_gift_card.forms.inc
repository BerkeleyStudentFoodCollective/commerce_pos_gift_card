<?php

/**
 * @file
 * Forms for creating, editing, and deleting gift cards.
 */


/**
 * Form callback: create or edit a gift card.
 *
 * @param $gift_card
 *   The gift card object to edit or for a create form an empty gift card object
 *     with only a gift card type defined.
 */
function commerce_pos_gift_card_gift_card_form($form, &$form_state, $gift_card) {
  $language = !empty($gift_card->language) ? $gift_card->language : LANGUAGE_NONE;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_pos_gift_card') . '/includes/commerce_pos_gift_card.forms.inc';

  // Add the default field elements.
  // TODO: Update description to include the acceptable gift card tokens.
  $form['card_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Gift card number'),
    '#description' => t('Supply a unique identifier for this gift card using letters, numbers, hyphens, and underscores. Commas may not be used.'),
    '#default_value' => $gift_card->card_number,
    '#maxlength' => 128,
    '#required' => TRUE,
    '#weight' => -10,
  );

  // Add the field related form elements.
  $form_state['commerce_pos_gift_card'] = $gift_card;
  field_attach_form('commerce_pos_gift_card', $gift_card, $form, $form_state, $language);

  $form['status'] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#description' => t('Disabled gift cards cannot be used to pay for purchases and may not show up in administrative gift card lists.'),
    '#options' => array(
      '1' => t('Active'),
      '0' => t('Disabled'),
    ),
    '#default_value' => $gift_card->status,
    '#required' => TRUE,
    '#weight' => 35,
  );

  // Load the gift card type to get the default revision setting.
  $gift_card_type = commerce_pos_gift_card_type_load($gift_card->type);

  // When updating a gift card, do not collapse the Change History fieldset if the
  // gift card type is configured to create a new revision by default.
  $form['change_history'] = array(
    '#type' => 'fieldset',
    '#title' => t('Change history'),
    '#collapsible' => TRUE,
    '#collapsed' => empty($gift_card->gift_card_id) || empty($gift_card_type['revision']),
    '#weight' => 50,
  );
  if (!empty($gift_card->gift_card_id)) {
    $form['change_history']['revision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Create new revision on update'),
      '#description' => t('If an update log message is entered, a revision will be created even if this is unchecked.'),
      '#default_value' => $gift_card_type['revision'],
      '#access' => user_access('administer commerce_pos_gift_card entities'),
    );
  }
  $form['change_history']['log'] = array(
    '#type' => 'textarea',
    '#title' => !empty($gift_card->gift_card_id) ? t('Update log message') : t('Creation log message'),
    '#rows' => 4,
    '#description' => t('Provide an explanation of the changes you are making. This will provide a meaningful history of changes to this gift card.'),
  );

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // Simply use default language
  $form['language'] = array(
    '#type' => 'value',
    '#value' => $language,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save gift card'),
    '#submit' => array_merge($submit, array('commerce_pos_gift_card_gift_card_form_submit')),
  );

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'commerce_pos_gift_card_gift_card_form_validate';

  return $form;
}

/**
 * Validation callback for commerce_pos_gift_card_gift_card_form().
 */
function commerce_pos_gift_card_gift_card_form_validate($form, &$form_state) {
  $gift_card = $form_state['commerce_pos_gift_card'];

  // TODO: Resolve workflow issues pertaining to token replacement in gift card numbers.
  // Perform token replacement on the entered gift cards numbers.
  // $card_number = commerce_pos_gift_card_replace_card_number_tokens($form_state['values']['card_number'], $gift_card);

  // Until the above is resolved, simply use the card number as entered with no tokens.
  $card_number = $form_state['values']['card_number'];

  // If invalid tokens were specified, throw an error.
  if ($card_number === FALSE) {
    form_set_error('card_number', t('The card number contains invalid tokens.'));
  }
  else {
    // Ensure the proposed card number is unique.
    if (!commerce_pos_gift_card_validate_card_number_unique($card_number, $gift_card->gift_card_id)) {
      form_set_error('card_number', t('This card number is already in use and must be unique. Please supply another value.'));
    }

    // Check the card number for invalid characters.
    if (!commerce_pos_gift_card_validate_card_number($card_number)) {
      form_set_error('card_number', t('The card number %card_number contains invalid characters.', array('%card_number' => $card_number)));
    }

    // Trim leading and trailing whitespace from the card number.
    form_set_value($form['card_number'], trim($card_number), $form_state);
  }

  // Notify field widgets to validate their data.
  field_attach_form_validate('commerce_pos_gift_card', $gift_card, $form, $form_state);
}

/**
 * Submit callback for commerce_pos_gift_card_gift_card_form().
 */
function commerce_pos_gift_card_gift_card_form_submit($form, &$form_state) {
  global $user;

  $gift_card = &$form_state['commerce_pos_gift_card'];

  // Save default parameters back into the $gift_card object.
  $gift_card->card_number = $form_state['values']['card_number'];
  $gift_card->title = $form_state['values']['title'];
  $gift_card->status = $form_state['values']['status'];
  $gift_card->language = $form_state['values']['language'];

  // Set the gift card's uid if it's being created at this time.
  if (empty($gift_card->gift_card_id)) {
    $gift_card->uid = $user->uid;
  }

  // Trigger a new revision if the checkbox was enabled or a log message supplied.
  if ((user_access('administer commerce_pos_gift_card entities') && !empty($form_state['values']['revision'])) ||
    (!user_access('administer commerce_pos_gift_card entities') && !empty($form['change_history']['revision']['#default_value'])) ||
    !empty($form_state['values']['log'])) {
    $gift_card->revision = TRUE;
    $gift_card->log = $form_state['values']['log'];
  }

  // Notify field widgets.
  field_attach_submit('commerce_pos_gift_card', $gift_card, $form, $form_state);

  // Save the gift card.
  commerce_pos_gift_card_save($gift_card);

  // Redirect based on the button clicked.
  drupal_set_message(t('Gift Card saved.'));
}

/**
 * Form callback: confirmation form for deleting a gift card.
 *
 * @param $gift_card
 *   The gift card object to be deleted.
 *
 * @see confirm_form()
 */
function commerce_pos_gift_card_gift_card_delete_form($form, &$form_state, $gift_card) {
  $form_state['gift_card'] = $gift_card;

  // Ensure this include file is loaded when the form is rebuilt from the cache.
  $form_state['build_info']['files']['form'] = drupal_get_path('module', 'commerce_pos_gift_card') . '/includes/commerce_pos_gift_card.forms.inc';

  $form['#submit'][] = 'commerce_pos_gift_card_gift_card_delete_form_submit';

  $content = entity_view('commerce_pos_gift_card', array($gift_card->gift_card_id => $gift_card));

  $form = confirm_form($form,
    t('Are you sure you want to delete gift card %number?', array('%number' => $gift_card->card_number)),
    '',
    drupal_render($content) . '<p>' . t('Deleting this gift card cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for commerce_pos_gift_card_gift_card_delete_form().
 */
function commerce_pos_gift_card_gift_card_delete_form_submit($form, &$form_state) {
  $gift_card = $form_state['gift_card'];

  if (commerce_pos_gift_card_delete($gift_card->gift_card_id)) {
    drupal_set_message(t('%number has been deleted.', array('%number' => $gift_card->card_number)));
    watchdog('commerce_pos_gift_card', 'Deleted gift card %number.', array('%number' => $gift_card->card_number), WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('%number could not be deleted.', array('%number' => $gift_card->card_number)), 'error');
  }
}
