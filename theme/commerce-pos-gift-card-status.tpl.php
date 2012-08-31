<?php

/**
 * @file
 * Default theme implementation to present the status on a gift card page.
 *
 * Available variables:
 * - $status: The string representation of a gift card's status to render.
 * - $label: If present, the string to use as the status label.
 *
 * Helper variables:
 * - $gift_card: The fully loaded gift card object the status belongs to.
 */
?>
<?php if ($status): ?>
  <div class="commerce-pos-gift-card-status">
    <?php if ($label): ?>
      <div class="commerce-pos-gift-card-status-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $status; ?>
  </div>
<?php endif; ?>
