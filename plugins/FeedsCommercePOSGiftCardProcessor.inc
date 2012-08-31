<?php

/**
 * @file
 * Class definition of FeedsCommercePOSGiftCardProcessor.
 */

/**
 * Creates gift cards from feed items.
 */
class FeedsCommercePOSGiftCardProcessor extends FeedsProcessor {

  /**
   * Define entity type.
   */
  public function entityType() {
    return 'commerce_pos_gift_card';
  }

  /**
   * Implements parent::entityInfo().
   */
  protected function entityInfo() {
    $info = parent::entityInfo();
    $info['label plural'] = t('Commerce POS Gift Cards');
    return $info;
  }

  /**
   * Creates a new gift card in memory and returns it.
   */
  protected function newEntity(FeedsSource $source) {
    $type = $this->config['gift_card_type'];
    $gift_card = commerce_pos_gift_card_new($type);
    $gift_card->uid = $this->config['author'];
    return $gift_card;
  }

  /**
   * Loads an existing gift card.
   */
  protected function entityLoad(FeedsSource $source, $card_number) {
    if ($this->config['update_existing'] == FEEDS_UPDATE_EXISTING) {
      $gift_card = commerce_pos_gift_card_load_by_card_number($card_number);
    }
    return $gift_card;
  }

  /**
   * Save a gift card.
   */
  public function entitySave($entity) {
    commerce_pos_gift_card_save($entity);
  }

  /**
   * Delete a series of gift cards.
   */
  protected function entityDeleteMultiple($gift_card_ids) {
    commerce_pos_gift_card_delete_multiple($gift_card_ids);
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    $types = commerce_pos_gift_card_type_get_name();
    $type = isset($types['currency']) ? 'currency' : key($types);
    return array(
      'gift_card_type' => $type,
      'author' => 0,
    ) + parent::configDefaults();
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $types = commerce_pos_gift_card_type_get_name();
    array_walk($types, 'check_plain');
    $form = parent::configForm($form_state);
    $form['gift_card_type'] = array(
      '#type' => 'select',
      '#title' => t('Gift card type'),
      '#description' => t('Select the gift card type for the gift cards to be created. <strong>Note:</strong> Users with "import !feed_id feeds" permissions will be able to <strong>import</strong> gift cards of the type selected here regardless of the gift card level permissions. Further, users with "clear !feed_id permissions" will be able to <strong>delete</strong> imported gift cards regardless of their gift card level permissions.', array('!feed_id' => $this->id)),
      '#options' => $types,
      '#default_value' => $this->config['gift_card_type'],
    );
    $author = user_load($this->config['author']);
    $form['author'] = array(
      '#type' => 'textfield',
      '#title' => t('Author'),
      '#description' => t('Select the author of the gift cards to be created - leave empty to assign "anonymous".'),
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => empty($author->name) ? 'anonymous' : check_plain($author->name),
    );

    $form['update_existing']['#options'] = array(
      FEEDS_SKIP_EXISTING => 'Do not update existing gift cards',
      FEEDS_UPDATE_EXISTING => 'Update existing gift cards',
    );
    return $form;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    if ($author = user_load_by_name($values['author'])) {
      $values['author'] = $author->uid;
    }
    else {
      $values['author'] = 0;
    }
  }

  /**
   * Override setTargetElement to operate on a target item that is a commerce gift card.
   */
  public function setTargetElement(FeedsSource $source, $target_node, $target_element, $value) {
    parent::setTargetElement($source, $target_node, $target_element, $value);
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
    $targets = parent::getMappingTargets();
    $targets += array(
      'card_number' => array(
        'name' => t('Gift card number'),
        'description' => t('The gift card identifier. Must be unique.'),
        'optional_unique' => TRUE,
      ),
      'status' => array(
        'name' => t('Gift card status'),
        'description' => t('Status of the gift card.'),
      ),
      'uid' => array(
        'name' => t('User ID'),
        'description' => t('The Drupal user ID of the gift card owner.'),
      ),
      'language' => array(
        'name' => t('Language'),
        'description' => t('The language of this gift card.'),
      ),      
    );
    // Let implementers of hook_feeds_term_processor_targets() add their targets.
    try {
      self::loadMappers();
      feeds_alter('feeds_processor_targets', $targets, 'commerce_pos_gift_card', $this->config['gift_card_type']);
    } catch (Exception $e) {
      // Do nothing.
    }
    return $targets;
  }

  /**
   * Get gift_card_id of an existing gift card if available.
   */
  protected function existingEntityId(FeedsSource $source, FeedsParserResult $result) {
    // Iterate through all unique targets and test whether they do already
    // exist in the database.
    foreach ($this->uniqueTargets($source, $result) as $target => $value) {
      switch ($target) {
        case 'card_number':
          $card_number = db_query("SELECT card_number FROM {commerce_pos_gift_card} WHERE card_number = :card_number", array(':card_number' => $value))->fetchField();
          break;
      }
      if ($card_number) {
        // Return with the first card number found.
        return $card_number;
      }
    }
    return 0;
  }

}
