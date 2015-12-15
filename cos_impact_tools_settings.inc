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
  $form['cos_impact_tools']['#tree'] = TRUE;
  $form['overview'] = array(
    '#markup' => t('This interface allows users with appropriate rights to manage the Tools blocks.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $result = db_query('SELECT id, icon, title, url, weight FROM {cos_impact_blocks} ORDER BY weight ASC');
  foreach ($result as $item) {
    $form['cos_impact_tools'][$item->id] = array(
      'select_icon' => array(
        '#type' => 'select',
        '#description' => t('Select the Icon from Font Awesome you wish to use.'),
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
        '#default_value' => check_plain($item->icon),
      ),
      'page_title' => array(
        '#type' => 'textfield',
        '#title' => t('Toolbox Title'),
        '#required' => TRUE,
        '#size' => 20,
        '#title_display' => 'invisible',
        '#description' => t('Title will show up below the Icon'),
        '#default_value' => check_plain($item->title),
      ),
      'page_url' => array(
        '#type' => 'textfield',
        '#title' => t('Toolbox URL'),
        '#required' => TRUE,
        '#title_display' => 'invisible',
        '#description' => t('Can be relative to Drupal or external.'),
        '#default_value' => check_plain($item->url),
      ),
      'weight' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#delta' => 10,
        '#title_display' => 'invisible',
        '#default_value' => check_plain($item->weight),
      ),
    );
  }
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes'),
    );
  return $form;
}

function cos_impact_tools_settings_form_validate($form, &$form_state){

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
  foreach (element_children($form['cos_impact_tools']) as $id) {
    $form['cos_impact_tools'][$id]['weight']['#attributes']['class'] = array('toolbox-item-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['cos_impact_tools'][$id]['select_icon']),
        drupal_render($form['cos_impact_tools'][$id]['page_title']),
        drupal_render($form['cos_impact_tools'][$id]['page_url']),
        drupal_render($form['cos_impact_tools'][$id]['weight']),
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

/**
 * Implements hook_submit.
 * @param $form
 * @param $form_state
 */
function cos_impact_tools_settings_form_submit($form, &$form_state){
  foreach ($form_state['values']['cos_impact_tools'] as $id => $item){
    //db_query(
    //  "UPDATE {cos_impact_blocks} SET weight = :weight WHERE id = :id",
    //  array(':weight' => $item['weight'], ':id' => $id)
    //);
    // Better way to run a db update
    db_update('cos_impact_blocks')
      ->fields(array(
        'icon' => $item['select_icon'],
        'title' => $item['page_title'],
        'url' => $item['page_url'],
        'weight' => $item['weight'],
      ))
      ->condition('id', $id)
      ->execute();
  }
}
