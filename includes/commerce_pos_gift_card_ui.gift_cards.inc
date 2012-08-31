<?php

/**
 * @file
 * Page callbacks and form builder functions for administering gift cards.
 */


/**
 * Menu callback: display a list of gift card types that the user can create.
 */
function commerce_pos_gift_card_ui_add_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  // Bypass the admin/commerce/gift_cards/add listing if only one gift card type is
  // available.
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }

  return theme('gift_card_add_list', array('content' => $content));
}

/**
 * Displays the list of available gift card types for gift card creation.
 *
 * @ingroup themeable
 */
function theme_commerce_pos_gift_card_add_list($variables) {
  $content = $variables['content'];
  $output = '';

  if ($content) {
    $output = '<dl class="commerce-pos-gift-card-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    $output = '<p>' . t('You do not have any gift card types yet. You need to enable a gift card type module before you can create a gift card.') . '</p>';
  }

  return $output;
}

/**
 * Form callback wrapper: create or edit a gift card.
 *
 * @param $gift_card
 *   The gift card object being edited by this form.
 *
 * @see commerce_pos_gift_card_gift_card_form()
 */
function commerce_pos_gift_card_ui_gift_card_form_wrapper($gift_card) {
  // Add the breadcrumb for the form's location.
  commerce_pos_gift_card_ui_set_breadcrumb();

  // Include the forms file from the Gift card module.
  module_load_include('inc', 'commerce_pos_gift_card', 'includes/commerce_pos_gift_card.forms');

  return drupal_get_form('commerce_pos_gift_card_ui_gift_card_form', $gift_card);
}

/**
 * Form callback wrapper: confirmation form for deleting a gift card.
 *
 * @param $gift_card
 *   The gift card object being deleted by this form.
 *
 * @see commerce_pos_gift_card_gift_card_delete_form()
 */
function commerce_pos_gift_card_ui_gift_card_delete_form_wrapper($gift_card) {
  // Add the breadcrumb for the form's location.
  commerce_pos_gift_card_ui_set_breadcrumb();

  // Include the forms file from the Gift card module.
  module_load_include('inc', 'commerce_pos_gift_card', 'includes/commerce_pos_gift_card.forms');

  return drupal_get_form('commerce_pos_gift_card_ui_gift_card_delete_form', $gift_card);
}
