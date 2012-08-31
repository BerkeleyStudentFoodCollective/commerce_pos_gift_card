<?php

/**
 * Export Drupal Commerce POS Gift Cards to Views.
 */

/**
 * Implements hook_views_data()
 */
function commerce_pos_gift_card_views_data() {
  $data = array();

  $data['commerce_pos_gift_card']['table']['group']  = t('Commerce POS Gift Card');

  $data['commerce_pos_gift_card']['table']['base'] = array(
    'field' => 'gift_card_id',
    'title' => t('Commerce POS Gift Card'),
    'help' => t('Gift cards from the store.'),
    'access query tag' => 'commerce_pos_gift_card_access',
  );
  $data['commerce_pos_gift_card']['table']['entity type'] = 'commerce_pos_gift_card';

  // Expose the gift card ID.
  $data['commerce_pos_gift_card']['gift_card_id'] = array(
    'title' => t('Gift Card ID'),
    'help' => t('The unique internal identifier of the gift card.'),
    'field' => array(
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'commerce_pos_gift_card_handler_argument_gift_card_id',
    ),
  );

  // Expose the gift card number.
  $data['commerce_pos_gift_card']['card_number'] = array(
    'title' => t('Card number'),
    'help' => t('The unique customer-facing identifier of the gift card.'),
    'field' => array(
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the gift card type.
  $data['commerce_pos_gift_card']['type'] = array(
    'title' => t('Type'),
    'help' => t('The human-readable name of the type of the gift card.'),
    'field' => array(
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card_type',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'commerce_pos_gift_card_handler_filter_gift_card_type',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // Expose the creator uid.
  $data['commerce_pos_gift_card']['uid'] = array(
    'title' => t('Creator'),
    'help' => t('Relate a gift card to the user who created it.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'field' => 'uid',
      'label' => t('Gift card creator'),
    ),
  );

  // Expose the gift card status.
  $data['commerce_pos_gift_card']['status'] = array(
    'title' => t('Status'),
    'help' => t('Whether or not the gift card is active.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'active-disabled' => array(t('Active'), t('Disabled')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Active'),
      'type' => 'yes-no',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Expose the created and changed timestamps.
  $data['commerce_pos_gift_card']['created'] = array(
    'title' => t('Created date'),
    'help' => t('The date the gift card was created.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_pos_gift_card']['created_fulldate'] = array(
    'title' => t('Created date'),
    'help' => t('In the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['commerce_pos_gift_card']['created_year_month'] = array(
    'title' => t('Created year + month'),
    'help' => t('In the form of YYYYMM.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['commerce_pos_gift_card']['created_timestamp_year'] = array(
    'title' => t('Created year'),
    'help' => t('In the form of YYYY.'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['commerce_pos_gift_card']['created_month'] = array(
    'title' => t('Created month'),
    'help' => t('In the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['commerce_pos_gift_card']['created_day'] = array(
    'title' => t('Created day'),
    'help' => t('In the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['commerce_pos_gift_card']['created_week'] = array(
    'title' => t('Created week'),
    'help' => t('In the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'created',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  $data['commerce_pos_gift_card']['changed'] = array(
    'title' => t('Updated date'),
    'help' => t('The date the gift card was last updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  $data['commerce_pos_gift_card']['changed_fulldate'] = array(
    'title' => t('Updated date'),
    'help' => t('In the form of CCYYMMDD.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_fulldate',
    ),
  );

  $data['commerce_pos_gift_card']['changed_year_month'] = array(
    'title' => t('Updated year + month'),
    'help' => t('In the form of YYYYMM.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_year_month',
    ),
  );

  $data['commerce_pos_gift_card']['changed_timestamp_year'] = array(
    'title' => t('Updated year'),
    'help' => t('In the form of YYYY.'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_year',
    ),
  );

  $data['commerce_pos_gift_card']['changed_month'] = array(
    'title' => t('Updated month'),
    'help' => t('In the form of MM (01 - 12).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_month',
    ),
  );

  $data['commerce_pos_gift_card']['changed_day'] = array(
    'title' => t('Updated day'),
    'help' => t('In the form of DD (01 - 31).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_day',
    ),
  );

  $data['commerce_pos_gift_card']['changed_week'] = array(
    'title' => t('Updated week'),
    'help' => t('In the form of WW (01 - 53).'),
    'argument' => array(
      'field' => 'changed',
      'handler' => 'views_handler_argument_node_created_week',
    ),
  );

  // Expose links to operate on the gift card.
  $data['commerce_pos_gift_card']['view_gift_card'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a simple link to the administrator view of the gift card.'),
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card_link',
    ),
  );
  $data['commerce_pos_gift_card']['edit_gift_card'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the gift card.'),
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card_link_edit',
    ),
  );
  $data['commerce_pos_gift_card']['delete_gift_card'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the gift card.'),
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card_link_delete',
    ),
  );

  $data['commerce_pos_gift_card']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all the available operations links for the gift card.'),
      'handler' => 'commerce_pos_gift_card_handler_field_gift_card_operations',
    ),
  );

  $data['commerce_pos_gift_card']['empty_text'] = array(
    'title' => t('Empty text'),
    'help' => t('Displays an appropriate empty text message for gift card lists.'),
    'area' => array(
      'handler' => 'commerce_pos_gift_card_handler_area_empty_text',
    ),
  );

  return $data;
}
