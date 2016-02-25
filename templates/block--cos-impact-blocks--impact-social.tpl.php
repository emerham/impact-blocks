<?php
/**
 * Created by PhpStorm.
 * User: brabhamm
 * Date: 12/9/15
 * Time: 4:40 PM
 */
drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css', array(
  'type' => 'external'
));
?>
<div class="imp-social-icons">
  <a class="twitter" href="<?php print render($items['twitter'])?>"><i class="fa fa-twitter"></i></a>
  <a class="facebook" href="<?php print render($items['facebook'])?>"><i class="fa fa-facebook"></i></a>
  <a class="instagram" href="<?php print render($items['instagram'])?>"><i class="fa fa-instagram"></i></a>
</div>
