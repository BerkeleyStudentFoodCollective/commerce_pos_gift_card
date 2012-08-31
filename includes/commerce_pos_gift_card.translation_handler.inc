<?php

/**
 * @file
 * Translation handler for the Commerce POS Gift Card entity.
 */

/**
 * Commerce POS Gift Card translation handler.
 *
 * This class is registered in commerce_pos_gift_card.module using the translation
 * property the Entity Translation module uses via hook_entity_info().
 *
 * @see commerce_pos_gift_card_entity_info()
 */
class EntityTranslationCommercePosGiftCardHandler extends EntityTranslationDefaultHandler {

  public function __construct($entity_type, $entity_info, $entity, $entity_id) {
    parent::__construct('commerce_pos_gift_card', $entity_info, $entity, $entity_id);
  }

  /**
   * Indicates whether this Commerce POS Gift Card is a revision or not.
   */
  public function isRevision() {
    return !empty($this->entity->revision);
  }

  /**
   * Returns the original language of the gift card.
   */
  public function getLanguage() {
    return $this->entity->language;
  }

  /**
   * Checks whether the current user has access to this gift card.
   */
  public function getAccess($op) {
    return commerce_pos_gift_card_access($op, $this->entity);
  }

  /**
   * Returns whether the gift card is active (TRUE) or disabled (FALSE).
   */
  protected function getStatus() {
    return (boolean) $this->entity->status;
  }
}
