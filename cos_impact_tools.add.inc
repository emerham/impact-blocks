<?php
/**
 * @file
 * Adds a new row to the cos impact tools box
 */
/**
 * Implements hook_form().
 * @param $form
 * @param $form_state
 */
function cos_impact_add_form($form, &$form_state) {
  $form['toolbox_icon'] = array(
    '#type' => 'select',
    '#title' => t('Icon to be shown.'),
    '#description' => t('The font awesome Icon to be used'),
    '#options' => array(
      'fa-facebook' => t('Facebook'),
      'fa-graduation-cap' => t('Graduation Cap'),
      'fa-life-ring' => t('Life Preserver'),
      'fa-list' => t('List'),
      'fa-medkit' => t('Med Kit'),
      'fa-money' => t('Money'),
      'fa-paper-plane' => t('Paper Airplane'),
      'fa-twitter' => t('Twitter'),
    ),
    '#required' => TRUE,
  );
  $form['toolbox_icon_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Toolbox Title'),
    '#required' => TRUE,
    '#size' => 20,
    '#title_display' => 'before',
    '#description' => t('Title will show up below the Icon'),
  );
  $form['toolbox_icon_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Toolbox URL'),
    '#required' => TRUE,
    '#title_display' => 'before',
    '#description' => t('Can be relative to Drupal or external.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  return $form;
}

/**
 * Implements hock_form_validate().
 * @param $form
 * @param $form_state
 */
function cos_impact_add_form_validate($form, &$form_state) {

}

/**
 * Implements hock_form_submit().
 * @param $form
 * @param $form_state
 */
function cos_impact_add_form_submit($form, &$form_state) {
  $fields_array = array(
    'icon' => $form_state['values']['toolbox_icon'],
    'title' => $form_state['values']['toolbox_icon_title'],
    'url' => $form_state['values']['toolbox_icon_url'],
  );
  db_insert('cos_impact_blocks')
    ->fields($fields_array)
    ->execute();
  // Unset destination, we will be using a redirect.
  unset($_GET['destination']);
  // Unset rebuild so we go to the destination we want.
  unset($form_state['rebuild']);
  $form_state['redirect'] = 'admin/config/impact/manage';
  drupal_set_message(t('Added new Tool box'), 'status');
}
