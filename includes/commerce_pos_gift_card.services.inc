<?php
/**
 * Implements hook_default_services_endpoint().
 */
function commerce_pos_gift_card_default_services_endpoint() {
  $endpoints = array();

  $endpoint = new stdClass;
  $endpoint->debug = FALSE;
  $endpoint->disabled = FALSE;
  $endpoint->name = 'commerce_pos_gift_card';
  $endpoint->title = t('Gift Card Processing');
  $endpoint->server = 'rest_server';
  $endpoint->server_settings = array(
    'formatters' => array(
      'json' => TRUE,
      'bencode' => FALSE,
      'jsonp' => FALSE,
      'php' => FALSE,
      'rss' => FALSE,
      'xml' => FALSE,
      'yaml' => FALSE,
    ),
    'parsers' => array(
      'application/x-www-form-urlencoded' => TRUE,
      'application/json' => FALSE,
      'application/vnd.php.serialized' => FALSE,
      'application/x-yaml' => FALSE,
      'multipart/form-data' => FALSE,
    ),
  );
  $endpoint->path = 'commerce_pos_gift_card/rest';
  $endpoint->api_version = 3;
  $endpoint->authentication = array(
    'services' => 'services',
  );
  $endpoint->resources = array(
    'commerce_pos_gift_card' => array(
      'alias' => 'gift_card',
      'targeted_actions' => array(
        'info' => array(
          'enabled' => 1,
        ),
        'addBalance' => array(
          'enabled' => 1,
        ),
        'voidTransaction' => array(
          'enabled' => 1,
        ),
        'processPayment' => array(
          'enabled' => 1,
        ),
      ),
    ),
    'user' => array(
      'alias' => 'user',
      'actions' => array(
        'login' => array(
          'enabled' => 1,
        ),
        'logout' => array(
          'enabled' => 1,
        ),
      ),
    ),
  );

  $endpoints[] = $endpoint;

  return $endpoints;
}