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
}

function lyr_isl_theme_base_process_html(&$vars) {
}
// */

/**
 * Override the Islandora Basic Image preprocess function
 */
function lyr_isl_theme_base_preprocess_islandora_basic_image(&$variables) {
  
  drupal_add_css(drupal_get_path('theme', 'islandoratheme') . '/css/basic-image.css', array('group' => CSS_THEME, 'type' => 'file'));
  
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
  $variables['islandora_view_link'] = str_replace("download", "view", $variables['islandora_download_link']);
  $variables['islandora_view_link'] = str_replace("Download pdf", "Full Screen View", $variables['islandora_view_link']);
  
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

/**
 * Override the Islandora Collection preprocess function
 */
function lyr_isl_theme_base_preprocess_islandora_basic_collection(&$variables) {  
  // base url
  global $base_url;
  // base path
  global $base_path;
  $islandora_object = $variables['islandora_object'];
  
  $page_number = (empty($_GET['page'])) ? 0 : $_GET['page'];
  $page_size = (empty($_GET['pagesize'])) ? variable_get('islandora_basic_collection_page_size', '10') : $_GET['pagesize'];
  $results = $variables['collection_results']; //islandora_basic_collection_get_objects($islandora_object, $page_number, $page_size); 
  $total_count = count($results);

  $associated_objects_mods_array = array(); 
  $start = $page_size * ($page_number);
  $end = min($start + $page_size, $total_count);

  for ($i = $start; $i < $end; $i++) {
    $pid = $results[$i]['object']['value'];
    $fc_object = islandora_object_load($pid);
    if (!isset($fc_object)) {
      continue; //null object so don't show in collection view;
    }
    $associated_objects_mods_array[$pid]['object'] = $fc_object;

    if (isset($fc_object['MODS']))
    {
      try {
        $mods = $fc_object['MODS']->content;
        $mods_object = simplexml_load_string($mods);
        $associated_objects_mods_array[$pid]['mods_array'] = isset($mods_object) ? MODS::as_formatted_array($mods_object) : array();
      } catch (Exception $e) {
        drupal_set_message(t('Error retrieving object %s %t', array('%s' => $islandora_object->id, '%t' => $e->getMessage())), 'error', FALSE);
      }
    }
      
    $object_url = 'islandora/object/' . $pid;
    $thumbnail_img = '<img src="' . $base_path . $object_url . '/datastream/TN/view"' . '/>';
    $title = $results[$i]['title']['value'];
    
    //If the object is a collection, get description information.
    $collection_description = false;
    if (isset($fc_object['DESC-TEXT']))
    {
        $collection_description = $fc_object['DESC-TEXT']->content;
    }
    //end of obtaining collection description
    
    $associated_objects_mods_array[$pid]['pid'] = $pid;
    $associated_objects_mods_array[$pid]['path'] = $object_url;
    $associated_objects_mods_array[$pid]['title'] = $title;
    $associated_objects_mods_array[$pid]['class'] = drupal_strtolower(preg_replace('/[^A-Za-z0-9]/', '-', $pid));
    if (isset($fc_object['TN'])) {
      $thumbnail_img = '<img src="' . $base_path . $object_url . '/datastream/TN/view"' . '/>';
    }
    else {
      $image_path = drupal_get_path('module', 'islandora');
      $thumbnail_img = '<img src="' . $base_path . $image_path . '/images/Crystal_Clear_action_filenew.png"/>';
    }
    $associated_objects_mods_array[$pid]['thumbnail'] = $thumbnail_img;
    $associated_objects_mods_array[$pid]['title_link'] = l($title, $object_url, array('html' => TRUE, 'attributes' => array('title' => $title)));
    $associated_objects_mods_array[$pid]['thumb_link'] = l($thumbnail_img, $object_url, array('html' => TRUE, 'attributes' => array('title' => $title)));
    
    if($collection_description)
    {
      $associated_objects_mods_array[$pid]['collection_description'] = $collection_description;
    }
  }
  $variables['associated_objects_mods_array'] = $associated_objects_mods_array;
}

// This function makes customizations to the breadcrumb region
function lyr_isl_theme_base_breadcrumb($variables) {
  if (!empty($variables['breadcrumb'][1])) {
    //Append title if it's a search
    if (strpos($variables['breadcrumb'][1], 'islandora-solr-breadcrumb-super') !== false)
    {
      unset($variables['breadcrumb'][0]);
      return '<p><strong>Current Search: </strong>&nbsp;' . implode(' &raquo; ', $variables['breadcrumb']) . '</p>';
    }
    else
    {
      unset($variables['breadcrumb'][0]);
      return theme_breadcrumb($variables);
    }
  }
}

//
// Implements islandora_solr_query() hook.
function lyr_isl_theme_base_islandora_solr_query($query_params) {
  // dpm($query_params);
}
