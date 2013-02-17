<?php
/**
 * @file
 * lyr_base_islandora.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lyr_base_islandora_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_toolkit';
  $strongarm->value = 'imagemagick';
  $export['image_toolkit'] = $strongarm;

  return $export;
}
