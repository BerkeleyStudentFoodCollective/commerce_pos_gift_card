<?php

/**
 * Views for the default gift card UI.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_pos_gift_card_ui_views_default_views() {
  $views = array();
  $view = new view();
  $view->name = 'gift_cards';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_pos_gift_card';
  $view->human_name = 'Gift cards';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Gift cards';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view any commerce_pos_gift_card entity';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gift_card_id' => 'gift_card_id',
    'card_number' => 'card_number',
    'operations' => 'operations',
  );
  $handler->display->display_options['style_options']['default'] = 'card_number';
  $handler->display->display_options['style_options']['info'] = array(
    'gift_card_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'card_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Commerce POS Gift Card: Card number */
  $handler->display->display_options['fields']['card_number']['id'] = 'card_number';
  $handler->display->display_options['fields']['card_number']['table'] = 'commerce_pos_gift_card';
  $handler->display->display_options['fields']['card_number']['field'] = 'card_number';
  /* Field: Commerce POS Gift Card: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_pos_gift_card';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Commerce POS Gift Card: Balance */
  $handler->display->display_options['fields']['balance']['id'] = 'balance';
  $handler->display->display_options['fields']['balance']['table'] = 'commerce_pos_gift_card';
  $handler->display->display_options['fields']['balance']['field'] = 'balance';
  /* Field: Commerce POS Gift Card: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'commerce_pos_gift_card';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['add_destination'] = 0;
  /* Sort criterion: Commerce POS Gift Card: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'commerce_pos_gift_card';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Commerce POS Gift Card: Card number */
  $handler->display->display_options['filters']['card_number']['id'] = 'card_number';
  $handler->display->display_options['filters']['card_number']['table'] = 'commerce_pos_gift_card';
  $handler->display->display_options['filters']['card_number']['field'] = 'card_number';
  $handler->display->display_options['filters']['card_number']['exposed'] = TRUE;
  $handler->display->display_options['filters']['card_number']['expose']['operator_id'] = 'card_number_op';
  $handler->display->display_options['filters']['card_number']['expose']['label'] = 'Card number';
  $handler->display->display_options['filters']['card_number']['expose']['operator'] = 'card_number_op';
  $handler->display->display_options['filters']['card_number']['expose']['identifier'] = 'card_number';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/commerce/gift_cards/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Gift cards';
  $handler->display->display_options['menu']['description'] = 'Manage gift cards.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'devel';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Gift cards';
  $handler->display->display_options['tab_options']['description'] = 'Manage gift cards in the store.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  
  $views[$view->name] = $view;  

  return $views;
}
