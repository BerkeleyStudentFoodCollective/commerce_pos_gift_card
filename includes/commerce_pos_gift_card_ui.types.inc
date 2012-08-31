<?php

/**
 * @file
 */


/**
 * Menu callback: display an overview of available types.
 */
function commerce_pos_gift_card_ui_types_overview() {
  drupal_add_css(drupal_get_path('module', 'commerce_pos_gift_card') . '/theme/commerce_pos_gift_card.admin.css');

  $header = array(
    t('Name'),
    t('Operations'),
  );

  $rows = array();

  // Loop through all defined gift card types.
  foreach (commerce_pos_gift_card_types() as $type => $gift_card_type) {
    // Build the operation links for the current gift card type.
    $links = menu_contextual_links('commerce-pos-gift-card-type', 'admin/commerce/gift_cards/types', array(strtr($type, array('_' => '-'))));

    // Add the gift card type's row to the table's rows array.
    $rows[] = array(
      theme('gift_card_type_admin_overview', array('gift_card_type' => $gift_card_type)),
      theme('links', array('links' => $links, 'attributes' => array('class' => 'links inline operations'))),
    );
  }

  // If no gift card types are defined...
  if (empty($rows)) {
    // Add a standard empty row with a link to add a new gift card type.
    $rows[] = array(
      array(
        'data' => t('There are no gift card types yet. You must enable a module defining a gift card type before you can create a gift card.'),
        'colspan' => 2,
      )
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Builds an overview of a gift card type for display to an administrator.
 *
 * @param $variables
 *   An array of variables used to generate the display; by default includes the
 *     type key with a value of the gift card type array.
 *
 * @ingroup themeable
 */
function theme_gift_card_type_admin_overview($variables) {
  $gift_card_type = $variables['gift_card_type'];

  $output = check_plain($gift_card_type['name']);
  $output .= ' <small>' . t('(Machine name: @type)', array('@type' => $gift_card_type['type'])) . '</small>';
  $output .= '<div class="description">' . filter_xss_admin($gift_card_type['description']) . '</div>';

  return $output;
}

/**
 * Form callback wrapper: create or edit a gift card type.
 *
 * @param $type
 *   The machine-name of the gift card type being created or edited by this form
 *     or a full gift card type array.
 *
 * @see commerce_pos_gift_card_gift_card_type_form()
 */
function commerce_pos_gift_card_ui_gift_card_type_form_wrapper($type) {
  if (is_array($type)) {
    $gift_card_type = $type;
  }
  else {
    $gift_card_type = commerce_pos_gift_card_type_load($type);
  }

  // Add the breadcrumb for the form's location.
  commerce_pos_gift_card_ui_set_breadcrumb(TRUE);

  // Return a message if the gift card type is not governed by Gift card UI.
  if (!empty($gift_card_type['type']) && $gift_card_type['module'] != 'commerce_pos_gift_card_ui') {
    return t('This gift card type cannot be edited, because it is not defined by the Gift Card UI module.');
  }

  // Include the forms file from the Gift card module.
  module_load_include('inc', 'commerce_pos_gift_card_ui', 'includes/commerce_pos_gift_card_ui.forms');

  return drupal_get_form('commerce_pos_gift_card_ui_gift_card_type_form', $gift_card_type);
}
