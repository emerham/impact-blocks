<?php
/**
 * @file
 * Created by PhpStorm.
 * User: brabhamm.
 * Date: 12/11/15.
 * Time: 9:08 AM.
 */

/**
 * Implements hook_form().
 */
function cos_impact_tools_settings_form($form, &$form_state) {
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
      'remove' => array(
        '#id' => 'row_' . $item->id,
        '#name' => 'row_' . $item->id,
        '#type' => 'submit',
        '#value' => t('Remove'),
        '#submit' => array('cos_impact_tools_delete_row'),
        '#attributes' => array(
          'class' => array(
            'btn',
            'btn-danger',
            'cos-btn-danger',
          ),
        ),
      ),
    );
  }
  $form['add_new_row'] = array(
    '#type' => 'submit',
    '#value' => t('Add New Row'),
    '#submit' => array('cos_impact_tools_add_row'),
    '#attributes' => array(
      'class' => array(
        'btn',
        'btn-success',
        'cos-btn-success',
      ),
    ),
  );
  $form['last_button'] = array(
    '#type' => 'textfield',
    '#title' => t('Text for the Blue Button'),
    '#required' => TRUE,
    '#description' => t('Text to be displayed in the Blue Box below tools.'),
    '#default_value' => variable_get('last_button_text', t('Beyond the Classroom')),
  );
  $form['last_button_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Blue Button Link'),
    '#required' => TRUE,
    '#description' => t('Link destination you wish this to go to.'),
    '#default_value' => variable_get('last_button_link', t('#')),
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes'),
  );
  return $form;
}

function cos_impact_tools_settings_form_validate($form, &$form_state) {

}

/**
 * Implements hook_settings_form().
 */
function theme_cos_impact_tools_settings_form($variables) {
  $form = $variables['form'];
  $output = drupal_render($form['overview']);
  $rows = array();
  foreach (element_children($form['cos_impact_tools']) as $id) {
    $form['cos_impact_tools'][$id]['weight']['#attributes']['class'] = array('toolbox-item-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['cos_impact_tools'][$id]['select_icon']),
        drupal_render($form['cos_impact_tools'][$id]['page_title']),
        drupal_render($form['cos_impact_tools'][$id]['page_url']),
        drupal_render($form['cos_impact_tools'][$id]['weight']),
        drupal_render($form['cos_impact_tools'][$id]['remove']),
      ),
      'class' => array('draggable'),
    );
  }
  $header = array(
    t('Icon'),
    t('Title'),
    t('URL'),
    t('Weight'),
    t('Remove'),
  );

  $table_id = 'toolbox-item-weight';
  $output .= theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));
  $output .= drupal_render_children($form);
  drupal_add_tabledrag($table_id, 'order', 'sibling', 'toolbox-item-weight');
  return $output;
}

/**
 * Implements hook_form_submit().
 *
 */
function cos_impact_tools_settings_form_submit($form, &$form_state) {
  variable_set('last_button_text', $form_state['values']['last_button']);
  variable_set('last_button_link', $form_state['values']['last_button_link']);
  foreach ($form_state['values']['cos_impact_tools'] as $id => $item) {
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
  drupal_set_message(t('Impact Tools Options have been saved.'), 'status');
}

/**
 * Custom submit handler to redirect user away to new form.
 */
function cos_impact_tools_add_row($form, &$form_state) {
  unset($_GET['destination']);
  unset($form_state['rebuild']);
  $form_state['redirect'] = 'admin/config/impact/add';
}

/**
 * Custom function to redirect over and delete an item from the table.
 */
function cos_impact_tools_delete_row($form, &$form_state) {
  unset($_GET['destination']);
  unset($form_state['rebuild']);
  $form_state['redirect'] = 'admin/config/impact/delete/' . drupal_substr($form_state['triggering_element']['#id'], 4);
}
