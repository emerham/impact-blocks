<?php
/**
 * @file
 * Created by PhpStorm.
 * User: brabhamm
 * Date: 12/15/15
 * Time: 4:52 PM.
 */
drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css', array(
  'type' => 'external',
));
?>
<div class="toolbox-container"
<div class="impact-tools">
  <div class="row-fluid">
    <?php foreach ($items as $var) { ?>
      <div class="toolbox">
        <a href="<?php print $var['url']; ?>"><i
            class="fa <?php print $var['icon']; ?>"></i>
          <p><?php print drupal_strtoupper($var['title']); ?></p>
        </a>
      </div>
      <?php
    };
    ?>
  </div>
  <div class="row-fluid">
    <a href="<?php print variable_get('last_button_link') ?>" class="beyond">
      <i class="fa fa-globe"
         style="font-size:18px;"></i> <?php print variable_get('last_button_text') ?>
    </a>
  </div>
</div>
</div>
