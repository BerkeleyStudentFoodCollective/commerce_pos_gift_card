<?php

/**
 * @file
 * The controller for the Gift card entity containing the CRUD operations.
 */

/**
 * The controller class for gift cards contains methods for the gift card CRUD operations.
 *
 * Mainly relies on the EntityAPIController class provided by the Entity
 * module, just overrides specific features.
 */
class CommercePosGiftCardEntityController extends DrupalCommerceEntityController {

  /**
   * Create a default gift card.
   *
   * @param array $values
   *   An array of values to set, keyed by property name.
   * @return
   *   A gift card object with all default fields initialized.
   */
  public function create(array $values = array()) {
    $values += array(
      'gift_card_id' => '',
      'is_new' => TRUE,
      'card_number' => '',
      'revision_id' => NULL,
      'title' => '',
      'uid' => '',
      'status' => 1,
      'created' => '',
      'changed' => '',
    );

    return parent::create($values);
  }

  /**
   * Saves a gift card.
   *
   * @param $gift_card
   *   The full gift card object to save.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   SAVED_NEW or SAVED_UPDATED depending on the operation performed.
   */
  public function save($gift_card, DatabaseTransaction $transaction = NULL) {
    global $user;
    
    if (empty($gift_card->card_number)) {
      $gift_card->card_number = commerce_pos_gift_card_default_card_number();
    }

    // Hardcode the changed time.
    $gift_card->changed = REQUEST_TIME;

    if (empty($gift_card->{$this->idKey}) || !empty($gift_card->is_new)) {
      // Set the creation timestamp if not set, for new entities.
      if (empty($gift_card->created)) {
        $gift_card->created = REQUEST_TIME;
      }
    }

    $gift_card->revision_timestamp = REQUEST_TIME;
    $gift_card->revision_uid = $user->uid;

    // Determine if we will be inserting a new gift card.
    $gift_card->is_new = empty($gift_card->gift_card_id);

    if ($gift_card->is_new || !empty($gift_card->revision)) {
      // When inserting either a new gift card or revision, $entity->log must be set
      // because {commerce_pos_gift_card_revision}.log is a text column and therefore
      // cannot have a default value. However, it might not be set at this
      // point, so we ensure that it is at least an empty string in that case.
      if (!isset($gift_card->log)) {
        $gift_card->log = '';
      }
    }
    elseif (empty($gift_card->log)) {
      // If we are updating an existing gift card without adding a new revision,
      // we need to make sure $entity->log is unset whenever it is empty. As
      // long as $entity->log is unset, drupal_write_record() will not attempt
      // to update the existing database column when re-saving the revision.
      unset($gift_card->log);
    }
    
    return parent::save($gift_card, $transaction);
  }

  /**
   * Unserializes the data property of loaded gift cards.
   */
  public function attachLoad(&$queried_gift_cards, $revision_id = FALSE) {
    foreach ($queried_gift_cards as $gift_card_id => &$gift_card) {
      $gift_card->data = unserialize($gift_card->data);
    }

    // Call the default attachLoad() method. This will add fields and call
    // hook_commerce_pos_gift_card_load().
    parent::attachLoad($queried_gift_cards, $revision_id);
  }

  /**
   * Deletes multiple gift cards by ID.
   *
   * @param $gift_card_ids
   *   An array of gift card IDs to delete.
   * @param $transaction
   *   An optional transaction object.
   *
   * @return
   *   TRUE on success, FALSE otherwise.
   */
  public function delete($gift_card_ids, DatabaseTransaction $transaction = NULL) {
    if (!empty($gift_card_ids)) {
      $gift_cards = $this->load($gift_card_ids, array());

      // Ensure the gift cards can actually be deleted.
      foreach ((array) $gift_cards as $gift_card_id => $gift_card) {
        if (!commerce_pos_gift_card_can_delete($gift_card)) {
          unset($gift_cards[$gift_card_id]);
        }
      }

      // If none of the specified gift cards can be deleted, return FALSE.
      if (empty($gift_cards)) {
        return FALSE;
      }

      parent::delete(array_keys($gift_cards), $transaction);
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Builds a structured array representing the entity's content.
   *
   * The content built for the entity will vary depending on the $view_mode
   * parameter.
   *
   * @param $entity
   *   An entity object.
   * @param $view_mode
   *   View mode, e.g. 'full', 'teaser'...
   * @param $langcode
   *   (optional) A language code to use for rendering. Defaults to the global
   *   content language of the current request.
   * @return
   *   The renderable array.
   */
  public function buildContent($gift_card, $view_mode = 'full', $langcode = NULL, $content = array()) {
    // Prepare a reusable array representing the CSS file to attach to the view.
    $attached = array(
      'css' => array(drupal_get_path('module', 'commerce_pos_gift_card') . '/theme/commerce_pos_gift_card.theme.css'),
    );

    // Add the default fields inherent to the gift card entity.
    $content['sku'] = array(
      '#markup' => theme('commerce_pos_gift_card_number', array('card_number' => $gift_card->card_number, 'label' => t('Card number:'), 'gift_card' => $gift_card)),
      '#attached' => $attached,
    );

    // Only display the title and status on the full page view.
    if ($view_mode == 'full') {
      $content['status'] = array(
        '#markup' => theme('commerce_pos_gift_card_status', array('status' => $gift_card->status ? t('Active') : t('Disabled'), 'label' => t('Status:'), 'gift_card' => $gift_card)),
        '#attached' => $attached,
      );
    }

    return parent::buildContent($gift_card, $view_mode, $langcode, $content);
  }
}
