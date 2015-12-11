<?php
/**
 * Created by PhpStorm.
 * User: brabhamm
 * Date: 12/11/15
 * Time: 9:08 AM
 */
/**
 * Implements hook_form().
 */
function cos_impact_tools_settings_form($form, &$form_state){
  $form = array();
  $form['overview'] = array(
    '#markup' => t('This interface allows users with appropriate rights to manage the Tools blocks.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );
  $form['test_table']['#tree'] = TRUE;
  $form['test_table'][0] = array(
    'select_icon' => array(
      '#type' => 'select',
      '#description' => t('Select the Icon from Font Awesome you wish to use.'),
      '#options' => array(
        'fa-list' => t('List'),
        'fa-twitter' => t('Twitter'),
        'fa-facebook' => t('Facebook'),
        ),
      ),
    'page_title' => array(
      '#type' => 'textfield',
      '#title' => t('Toolbox Title'),
      '#size' => 10,
      '#title_display' => 'invisible',
      '#description' => t('Title will show up below the Icon'),
    ),
    'page_url' => array(
      '#type' => 'textfield',
      '#title' => t('Toolbox URL'),
      '#title_display' => 'invisible',
      '#description' => t('Can be relative to Drupal or external.'),
    ),
    'weight' => array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => 0,
      '#delta' => 10,
      '#title_display' => 'invisible',
    ),
  );
  $form['actions'] = array('#type' => 'actions');
  return $form;
}

/**
 * custom theme function for table drag.
 * @param $variables
 * @return string
 * @throws \Exception
 */
function theme_cos_impact_tools_settings_form($variables){
  $form = $variables['form'];
  $rows = array();
  foreach (element_children($form['test_table']) as $id) {
    $form['test_table'][$id]['weight']['#attributes']['class'] = array('toolbox-item-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['test_table'][$id]['select_icon']),
        drupal_render($form['test_table'][$id]['page_title']),
        drupal_render($form['test_table'][$id]['page_url']),
        drupal_render($form['test_table'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }
  $header = array(
    t('Icon'),
    t('Title'),
    t('URL'),
    t('Weight'),
  );

  $table_id = 'toolbox-item-weight';
  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));
  $output .= drupal_render_children($form);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'toolbox-item-weight');
  return $output;
}
