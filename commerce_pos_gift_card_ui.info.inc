<?php

/**
 * Implements hook_entity_property_info_alter().
 *
 * Add UI bound gift card properties.
 */
function commerce_pos_gift_card_ui_entity_property_info_alter(&$info) {
  $info['commerce_pos_gift_card']['properties']['edit_url'] = array(
    'label' => t('Edit URL'),
    'description' => t("The URL of the gift card's edit page."),
    'getter callback' => 'commerce_pos_gift_card_get_properties',
    'type' => 'uri',
  );
}