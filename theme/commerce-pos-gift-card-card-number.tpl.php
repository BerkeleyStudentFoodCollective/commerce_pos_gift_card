<?php

/**
 * @file
 * Default theme implementation to present the card number on a gift card page.
 *
 * Available variables:
 * - $card_number: The gift card to render.
 * - $label: If present, the string to use as the gift card number label.
 *
 * Helper variables:
 * - $gift_card: The fully loaded gift card object the gift card number represents.
 */
?>
<?php if ($card_number): ?>
  <div class="commerce-pos-gift-card-card-number">
    <?php if ($label): ?>
      <div class="commerce-pos-gift-card-card-number-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $card_number; ?>
  </div>
<?php endif; ?>
