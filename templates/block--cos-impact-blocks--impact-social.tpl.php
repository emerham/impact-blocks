<?php

/**
 * @file
 * Created by PhpStorm.
 * User: brabhamm
 * Date: 12/9/15
 * Time: 4:40 PM.
 */
drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css', array(
  'type' => 'external',
));
``
?>
<div class="imp-social-icons">
  <a class="icon" id="twitter"
     href="<?php print render($items['twitter']) ?>"><i
      class="fa fa-twitter"></i></a>
  <a class="icon" id="facebook"
     href="<?php print render($items['facebook']) ?>"><i
      class="fa fa-facebook"></i></a>
  <a class="icon" id="instagram"
     href="<?php print render($items['instagram']) ?>"><i
      class="fa fa-instagram"></i></a>
</div>
