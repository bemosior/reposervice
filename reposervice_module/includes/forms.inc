<?php

/**
 * Form for editing the banner and description of a collection.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 * @param object $islandora_object
 *   The Islandora Collection Object being acted upon.
 *
 * @return array
 *   The Drupal form definition.
 */
function reposervice_collection_details_form($form, &$form_state, $islandora_object) {
  $form_state['storage']['reposervice_collection_details']['update'] = FALSE;
  $form_state['storage']['reposervice']['pid'] = $islandora_object->id;

  $desc_text = '';
  if (isset($islandora_object['DESC-TEXT'])) {
    $desc_ds = $islandora_object['DESC-TEXT'];
    $desc_text = $desc_ds->content;
  }
  
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#description' => t('Description of the collection.'),
    '#default_value' => $desc_text,
  );
  
  $form['image_example_image_fid'] = array(
    '#title' => t('Banner Image'),
    '#type' => 'managed_file',
    '#description' => t('Image used as a replacement for the collection title in the collection display.  Allowed extensions: gif, png, jpg, jpeg.'),
    '#default_value' => variable_get('image_example_image_fid', ''),
    '#upload_location' => 'private://',
  );
  
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save Details'));

  return $form;
}

/**
 * Submit handler for collection descriptions.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 */
function reposervice_collection_details_form_submit($form, &$form_state) {
  $form_state['storage']['reposervice_collection_details']['update'] = TRUE;
  $pid = $form_state['storage']['reposervice']['pid'];
  $islandora_object = islandora_object_load($pid);
  if (!$islandora_object) {
    drupal_set_message(t('Object with identifer @pid not found in repository.', array('pid' => $pid)), 'error');
    return;
  }
  
  if (!isset($islandora_object['DESC-TEXT'])) {
    $desc_ds = $islandora_object->constructDatastream('DESC-TEXT', 'M');
  } else {
    $desc_ds = $islandora_object["DESC-TEXT"];
  }
  $desc_ds->label = 'Collection Description';
  $desc_ds->mimetype = 'text/plain';
  $desc_ds->setContentFromString($form_state['values']['description']);
  $islandora_object->ingestDatastream($desc_ds);

  return $form;
}