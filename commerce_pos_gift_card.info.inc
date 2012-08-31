<?php

/**
 * @file
 * Provides metadata for the gift card entity.
 */

/**
 * Implements hook_entity_property_info().
 */
function commerce_pos_gift_card_entity_property_info() {
  $info = array();

  // Add meta-data about the basic commerce_pos_gift_card properties.
  $properties = &$info['commerce_pos_gift_card']['properties'];

  $properties['gift_Card_id'] = array(
    'label' => t('Gift Card ID'),
    'description' => t('The internal numeric ID of the gift card.'),
    'type' => 'integer',
    'schema field' => 'gift_card_id',
  );
  $properties['card_number'] = array(
    'label' => t('Card number'),
    'description' => t('The customer-facing gift card number.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'required' => TRUE,
    'schema field' => 'sku',
  );
  $properties['type'] = array(
    'label' => t('Type'),
    'description' => t('The type of the gift card.'),
    'type' => 'token',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_pos_gift_card entities',
    'options list' => 'commerce_pos_gift_card_type_options_list',
    'required' => TRUE,
    'schema field' => 'type',
  );
  $properties['title'] = array(
    'label' => t('Title'),
    'description' => t('The title of the gift card.'),
    'type' => 'text',
    'setter callback' => 'entity_property_verbatim_set',
    'required' => TRUE,
    'schema field' => 'title',
  );
  $properties['status'] = array(
    'label' => t('Status'),
    'description' => t('Boolean indicating whether the gift card is active or disabled.'),
    'type' => 'boolean',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_pos_gift_card entities',
    'schema field' => 'status',
  );
  $properties['created'] = array(
    'label' => t('Date created'),
    'description' => t('The date the gift card was created.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_pos_gift_card entities',
    'schema field' => 'created',
  );
  $properties['changed'] = array(
    'label' => t('Date updated'),
    'description' => t('The date the gift card was most recently updated.'),
    'type' => 'date',
    'setter callback' => 'entity_property_verbatim_set',
    'query callback' => 'entity_metadata_table_query',
    'setter permission' => 'administer commerce_pos_gift_card entities',
    'schema field' => 'changed',
  );
  $properties['uid'] = array(
    'label' => t("Creator ID"),
    'type' => 'integer',
    'description' => t("The unique ID of the gift card creator."),
    'setter callback' => 'entity_property_verbatim_set',
    'setter permission' => 'administer commerce_pos_gift_card entities',
    'clear' => array('creator'),
    'schema field' => 'uid',
  );
  $properties['creator'] = array(
    'label' => t("Creator"),
    'type' => 'user',
    'description' => t("The creator of the gift card."),
    'getter callback' => 'commerce_pos_gift_card_get_properties',
    'setter callback' => 'commerce_pos_gift_card_set_properties',
    'setter permission' => 'administer commerce_pos_gift_card entities',
    'required' => TRUE,
    'clear' => array('uid'),
  );

  return $info;
}
