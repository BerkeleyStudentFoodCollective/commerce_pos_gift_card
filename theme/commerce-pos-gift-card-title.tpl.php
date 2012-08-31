<?php

/**
 * @file
 * Default theme implementation to present the title on a gift card page.
 *
 * Available variables:
 * - $title: The title to render.
 * - $label: If present, the string to use as the title label.
 *
 * Helper variables:
 * - $gift_card: The fully loaded gift card object the title belongs to.
 */
?>
<?php if ($title): ?>
  <div class="commerce-pos-gift-card-title">
    <?php if ($label): ?>
      <div class="commerce-pos-gift-card-title-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $title; ?>
  </div>
<?php endif; ?>
