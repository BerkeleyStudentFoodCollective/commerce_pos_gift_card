<?php

/**
 * @file
 * Hooks provided by the Gift Card module.
 */


/**
 * Defines the types of gift cards available for creation on the site.
 *
 * Gift Card types are represented as bundles of the Commerce POS Gift Card entity type.
 * Each one has a unique machine-name, title, description, and help text. They
 * can also each have unique fields to store additional gift card data.
 *
 * The Gift Card UI module implements this hook to define gift card types based on
 * information stored in the database. 
 *
 * The gift card type array structure includes the following keys:
 * - type: the machine-name of the gift card type
 * - name: the translatable name of the gift card type
 * - description: a translatable description of the gift card type for use in
 *   administrative lists and pages
 * - help: the translatable help text included at the top of the add / edit form
 *   for gift cards of this type
 * - revision: for gift card types governed by the Gift Card UI module, this boolean
 *   determines whether or not gift cards of this type will default to creating
 *   new revisions when edited
 * - module: the name of the module defining the gift card type; should not be set
 *   by the hook itself but will be set when all gift card types are loaded
 *
 * @return
 *   An array of gift card type arrays keyed by type.
 */
function hook_commerce_pos_gift_card_type_info() {
  // Return the gift card types defined in the database by the Gift Card UI module.
  return db_query('SELECT * FROM {commerce_pos_gift_card_type}')->fetchAllAssoc('type', PDO::FETCH_ASSOC);
}

/**
 * Allows modules to alter the gift card types defined by other modules.
 *
 * @param $gift_card_types
 *   The array of gift card types defined by enabled modules.
 *
 * @see hook_commerce_pos_gift_card_type_info()
 */
function hook_commerce_pos_gift_card_type_info_alter(&$gift_card_types) {
  // No example.
}

/**
 * Allows modules to react to the creation of a new gift card type via Gift Card UI.
 *
 * @param $gift_card_type
 *   The gift card type info array.
 * @param $skip_reset
 *   Boolean indicating whether or not this insert will trigger a cache reset
 *   and menu rebuild.
 *
 * @see commerce_pos_gift_card_ui_gift_card_type_save()
 */
function hook_commerce_pos_gift_card_type_insert($gift_card_type, $skip_reset) {
  // No example.
}

/**
 * Allows modules to react to the update of a gift card type via Gift Card UI.
 *
 * @param $gift_card_type
 *   The gift card type info array.
 * @param $skip_reset
 *   Boolean indicating whether or not this update will trigger a cache reset
 *   and menu rebuild.
 *
 * @see commerce_pos_gift_card_ui_gift_card_type_save()
 */
function hook_commerce_pos_gift_card_type_update($gift_card_type, $skip_reset) {
  // No example.
}

/**
 * Allows modules to react to the deletion of a gift card type via Gift Card UI.
 *
 * @param $gift_card_type
 *   The gift card type info array.
 * @param $skip_reset
 *   Boolean indicating whether or not this deletion will trigger a cache reset
 *   and menu rebuild.
 *
 * @see commerce_pos_gift_card_ui_gift_card_type_delete()
 */
function hook_commerce_pos_gift_card_type_delete($gift_card_type, $skip_reset) {
  // No example.
}

/**
 * Lets modules specify the path information expected by a uri callback.
 *
 * The Gift Card module defines a uri callback for the gift card entity even though
 * it doesn't actually define any gift card menu items. The callback invokes this
 * hook and will return the first set of path information it finds. If the
 * Gift Card UI module is enabled, it will alter the gift card entity definition to
 * use its own uri callback that checks commerce_pos_gift_card_uri() for a return
 * value and defaults to an administrative link defined by that module.
 *
 * This hook is used as demonstrated below by the Gift Card Reference module to
 * direct modules to link the gift card to the page where it is actually displayed
 * to the user. Currently this is specific to nodes, but the system should be
 * beefed up to accommodate even non-entity paths.
 *
 * @param $gift_card
 *   The gift card object whose uri information should be returned.
 *
 * @return
 *   Implementations of this hook should return an array of information as
 *   expected to be returned to entity_uri() by a uri callback function.
 *
 * @see commerce_pos_gift_card_uri()
 * @see entity_uri()
 */
function hook_commerce_pos_gift_card_uri($gift_card) {
  // If the gift card has a display context, use it entity_uri().
  if (!empty($gift_card->display_context)) {
    return entity_uri($gift_card->display_context['entity_type'], $gift_card->display_context['entity']);
  }
}

/**
 * Lets modules prevent the deletion of a particular gift card.
 *
 * Before a gift card can be deleted, other modules are given the chance to say
 * whether or not the action should be allowed. Modules implementing this hook
 * can check for reference data or any other reason to prevent a gift card from
 * being deleted and return FALSE to prevent the action.
 *
 * This is an API level hook, so implementations should not display any messages
 * to the user (although logging to the watchdog is fine).
 *
 * @param $gift_card
 *   The gift card to be deleted.
 *
 * @return
 *   TRUE or FALSE indicating whether or not the given gift card can be deleted.
 *
 * @see commerce_pos_gift_card_reference_commerce_pos_gift_card_can_delete()
 */
function hook_commerce_pos_gift_card_can_delete($gift_card) {
  // Use EntityFieldQuery to look for line items referencing this gift card and do
  // not allow the delete to occur if one exists.
  $query = new EntityFieldQuery();

  $query
    ->entityCondition('entity_type', 'commerce_line_item', '=')
    ->entityCondition('bundle', 'gift_card', '=')
    ->fieldCondition('gift_card', 'gift_card_id', $gift_card->gift_card_id, '=')
    ->count();

  return $query->execute() > 0 ? FALSE : TRUE;
}
