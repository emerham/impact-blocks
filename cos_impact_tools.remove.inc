<?php
/**
 * @file
 */

function cos_impact_remove_row_form($form, &$form_state) {
  $form = array();
  $form['#item'] = $form_state['build_info']['args'][0];
  $form['row_delete'] = array(
    '#type' => 'value',
    '#value' => array($form_state['build_info']['args'][0]),
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete <em>@title?</em>', array('@title' => $form_state['build_info']['args'][0]['title'])),
    'admin/config/impact/manage',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function cos_impact_remove_row_form_submit($form_id, &$form_state) {
  //dpm($form_state);
  if (isset($form_state['values']['confirm'])) {
    db_delete('cos_impact_blocks')
    ->condition('id', $form_state['values']['row_delete'][0]['id'])
    ->condition('title', $form_state['values']['row_delete'][0]['title'])
    ->execute();
    drupal_set_message(t('Form Submitted, Thank You'), 'status');
    // Set to false to redirect.
    $form_state['rebuild'] = FALSE;
    // Go back to the management page.
    $form_state['redirect'] = 'admin/config/impact/manage';
  }
}
