<?php
/**
 * @file
 */
/**
 * Implements hook_confirm_form().
 */
function cos_impact_remove_confirm($form, &$form_state, $row_id) {
  $form['cos_tools_box'] = array(
    '#type' => 'value',
    '#value' => $row_id,
  );

  return confirm_form($form,
    t('Are you sure you want to delete the tool box %boxid', array('%boxid' => $row_id)),
    'admin/config/impact/manage',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function cos_impact_remove($form, &$form_state){
  
}
