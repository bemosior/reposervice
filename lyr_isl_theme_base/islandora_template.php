<?php

/**
 * @file
 * Template.php - process theme data for your sub-theme.
 * 
 * Rename each function and instance of "footheme" to match
 * your subthemes name, e.g. if you name your theme "footheme" then the function
 * name will be "footheme_preprocess_hook". Tip - you can search/replace
 * on "footheme".
 */

require_once 'includes/islandora_mods.inc';

/*
 * Custom function to set some variables used throughout the theme
 */
function lyr_isl_theme_base_variables(&$vars) {
  $vars['default_brand_logo'] = 'default_logo.png';
  $vars['default_brand_link'] = 'http://www.flvc.org';
  return $vars;
}

/**
 * Override or insert variables for the html template.
 */
function lyr_isl_theme_base_preprocess_html(&$vars) {
  drupal_add_library ('system', 'ui.tabs');
  drupal_add_js('jQuery(document).ready(function(){jQuery("#tabs").tabs();});', 'inline');
  drupal_add_css(drupal_get_path('theme', 'lyr_isl_theme_base').'/islandora_css/islandoratheme.css', array('group' => CSS_THEME, 'type' => 'file'));
}

function lyr_isl_theme_base_process_html(&$vars) {
}
// */

/**
 * Override the Islandora Basic Image preprocess function
 */
function lyr_isl_theme_base_preprocess_islandora_basic_image(&$variables) {
  
  drupal_add_css(drupal_get_path('theme', 'lyr_isl_theme_base') . '/islandora_css/basic-image.css', array('group' => CSS_THEME, 'type' => 'file'));
  
  $islandora_object = $variables['islandora_object'];
  
  try {
    $mods = $islandora_object['MODS']->content;
    $mods_object = simplexml_load_string($mods);
  } catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
 
  $variables['mods_array'] = isset($mods_object) ? MODS::as_formatted_array($mods_object) : array(); 
}

/**
 * Override the Islandora PDF preprocess function
 */
function lyr_isl_theme_base_preprocess_islandora_pdf(&$variables) {
  
  // Add css file for PDF presentation
  drupal_add_css(drupal_get_path('theme', 'islandoratheme') . '/css/pdf.css', array('group' => CSS_THEME, 'type' => 'file'));
  
  // Create full screen view
  if (isset($variables['islandora_view_link'])) {
    $variables['islandora_view_link'] = str_replace("download", "view", $variables['islandora_download_link']);
    $variables['islandora_view_link'] = str_replace("Download pdf", "Full Screen View", $variables['islandora_view_link']);
  }
  
  $islandora_object = $variables['islandora_object'];
  
  try {
    $mods = $islandora_object['MODS']->content;
    $mods_object = simplexml_load_string($mods);
  } catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
 
  $variables['mods_array'] = isset($mods_object) ? MODS::as_formatted_array($mods_object) : array(); 
}

/**
 * Override the Islandora Large Image preprocess function
 */
function lyr_isl_theme_base_preprocess_islandora_large_image(&$variables) {

  // When switching back to the Summary tab from the metadata details tab, the openseadragon view does not restore the
  // image.  This JavaScript from FLVC will force the page to reload when the Summary tab is selected.
  drupal_add_js('function tabLinkReload() {jQuery("#tabs a:first").click(function() {window.location.reload(true);});}', 'inline');
  drupal_add_js('jQuery(document).ready(function(){tabLinkReload();});', 'inline');

  drupal_add_css(drupal_get_path('theme', 'islandoratheme') . '/css/large-image.css', array('group' => CSS_THEME, 'type' => 'file'));
  
  $islandora_object = $variables['islandora_object'];
  
  try {
    $mods = $islandora_object['MODS']->content;
    $mods_object = simplexml_load_string($mods);
  } catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
 
  $variables['mods_array'] = isset($mods_object) ? MODS::as_formatted_array($mods_object) : array();
}

/**
 * Override the Islandora Internet Archive Bookreader module process function
 */
function lyr_isl_theme_base_process_islandora_internet_archive_bookreader(&$variables) {

  $islandora_object = $variables['object'];

  drupal_add_css(drupal_get_path('theme', 'islandoratheme') . '/css/book.css', array('group' => CSS_THEME, 'type' => 'file'));
  
  try {
    $mods = $islandora_object['MODS']->content;
    $mods_object = simplexml_load_string($mods);
  } catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
 
  $variables['mods_array'] = isset($mods_object) ? MODS::as_formatted_array($mods_object) : array();
}

function lyr_isl_theme_base_preprocess_islandora_basic_collection_grid(&$variables) {
  lyr_isl_theme_base_preprocess_islandora_basic_collection($variables);
}
/**
 * Override the Islandora Collection preprocess function
 */
function lyr_isl_theme_base_preprocess_islandora_basic_collection(&$variables) {  

  global $base_url;
  global $base_path;
  $islandora_object = $variables['islandora_object'];

  try {
    $dc = $islandora_object['DC']->content;
    $dc_object = DublinCore::importFromXMLString($dc);
  }
  catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
  $page_number = (empty($_GET['page'])) ? 0 : $_GET['page'];
  $page_size = (empty($_GET['pagesize'])) ? variable_get('islandora_basic_collection_page_size', '10') : $_GET['pagesize'];
  $results = $variables['collection_results'];
  $total_count = count($results);
  $variables['islandora_dublin_core'] = isset($dc_object) ? $dc_object : array();
  $variables['islandora_object_label'] = $islandora_object->label;
  $display = (empty($_GET['display'])) ? 'list' : $_GET['display'];
  if ($display == 'grid') {
    $variables['theme_hook_suggestions'][] = 'islandora_basic_collection_grid__' . str_replace(':', '_', $islandora_object->id);
  }
  else {
    $variables['theme_hook_suggestions'][] = 'islandora_basic_collection__' . str_replace(':', '_', $islandora_object->id);
  }
  if (isset($islandora_object['OBJ'])) {
    $full_size_url = url("islandora/object/{$islandora_object->id}/datastram/OBJ/view");
    $params = array(
      'title' => $islandora_object->label,
      'path' => $full_size_url);
    $variables['islandora_full_img'] = theme('image', $params);
  }
  if (isset($islandora_object['TN'])) {
    $full_size_url = url("islandora/objects/{$islandora_object->id}/datastream/TN/view");
    $params = array(
      'title' => $islandora_object->label,
      'path' => $full_size_url);
    $variables['islandora_thumbnail_img'] = theme('image', $params);
  }
  if (isset($islandora_object['MEDIUM_SIZE'])) {
    $full_size_url = url("islandora/object/{$islandora_object->id}/datastream/MEDIUM_SIZE/view");
    $params = array(
      'title' => $islandora_object->label,
      'path' => $full_size_url);
    $variables['islandora_medium_img'] = theme('params', $params);
  }

  $associated_objects_array = array();

  foreach ($results as $result) {
    $pid = $result['object']['value'];
    $fc_object = islandora_object_load($pid);
    if (!is_object($fc_object)) {
      // NULL object so don't show in collection view.
      continue;
    }
    $associated_objects_array[$pid]['object'] = $fc_object;
    try {
      $dc = $fc_object['DC']->content;
      $dc_object = DublinCore::importFromXMLString($dc);
      $associated_objects_array[$pid]['dc_array'] = $dc_object->asArray();
      $dc_title = $associated_objects_array[$pid]['dc_array']['dc:title']['value'];
    }
    catch (Exception $e) {
      drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
    }
    $object_url = 'islandora/object/' . $pid;

    $title = (isset($dc_title))? $dc_title : $result['title']['value'];
    $associated_objects_array[$pid]['pid'] = $pid;
    $associated_objects_array[$pid]['path'] = $object_url;
    $associated_objects_array[$pid]['title'] = $title;
    $associated_objects_array[$pid]['class'] = drupal_strtolower(preg_replace('/[^A-Za-z0-9]/', '-', $pid));
    if (isset($fc_object['TN'])) {
      $thumbnail_img = theme('image', array('path' => "$object_url/datastream/TN/view"));
    }
    else {
      $image_path = drupal_get_path('module', 'islandora');
      $thumbnail_img = theme('image', array('path' => "$image_path/images/folder.png"));
    }
    $associated_objects_array[$pid]['thumbnail'] = $thumbnail_img;
    $associated_objects_array[$pid]['title_link'] = l($title, $object_url, array('html' => TRUE, 'attributes' => array('title' => $title)));
    $associated_objects_array[$pid]['thumb_link'] = l($thumbnail_img, $object_url, array('html' => TRUE, 'attributes' => array('title' => $title)));
  }
  $variables['associated_objects_array'] = $associated_objects_array;
}

// This function makes customizations to the breadcrumb region
// function lyr_isl_theme_base_breadcrumb($variables) {
// }

//
// Implements islandora_solr_query() hook.
function lyr_isl_theme_base_islandora_solr_query($query_params) {
  // dpm($query_params);
}

/**
 * Implements hook_preprocess_theme().
 */
function lyr_isl_theme_base_preprocess_islandora_book_book(array &$variables) {
  drupal_add_css(path_to_theme().'/islandora_css/islandora-book-book.css');
  drupal_add_js('misc/form.js');
  drupal_add_js('misc/collapse.js');
  $islandora_object = $variables['object'];
  $repository = $islandora_object->repository;
  module_load_include('inc', 'islandora', 'includes/datastream');
  module_load_include('inc', 'islandora', 'includes/utilities');

  if (islandora_datastream_access(FEDORA_VIEW_OBJECTS, $islandora_object['DC'])) {
    try {
      $dc = $islandora_object['DC']->content;
      $dc_object = DublinCore::importFromXMLString($dc);
    }
    catch (Exception $e) {
      drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
    }
  }
  $variables['islandora_dublin_core'] = isset($dc_object) ? $dc_object : NULL;
  $variables['dc_array'] = isset($dc_object) ? $dc_object->asArray() : array();
  $variables['islandora_object_label'] = $islandora_object->label;
  $variables['theme_hook_suggestions'][] = 'islandora_basic_image__' . str_replace(':', '_', $islandora_object->id);
  $variables['parent_collections'] = islandora_get_parents_from_rels_ext($islandora_object);
  
  try {
    $mods = $islandora_object['MODS']->content;
    $mods_object = simplexml_load_string($mods);
  } catch (Exception $e) {
    drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
  }
 
  $variables['mods_array'] = isset($mods_object) ? MODS::as_formatted_array($mods_object) : array();

}
