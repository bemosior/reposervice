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
  $strongarm->name = 'clean_url';
  $strongarm->value = '1';
  $export['clean_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imagemagick_convert';
  $strongarm->value = '/Applications/mampstack-5.3.22-0/common/bin/convert';
  $export['imagemagick_convert'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_toolkit';
  $strongarm->value = 'imagemagick';
  $export['image_toolkit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_kakadu_url';
  $strongarm->value = '/Users/peter/reposervice/binaries/adore-djatoka/bin/Mac-x86/kdu_compress';
  $export['islandora_kakadu_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_large_image_uncompress_tiff';
  $strongarm->value = 1;
  $export['islandora_large_image_uncompress_tiff'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_lossless';
  $strongarm->value = 0;
  $export['islandora_lossless'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_allow_text_upload';
  $strongarm->value = 0;
  $export['islandora_pdf_allow_text_upload'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_create_fulltext';
  $strongarm->value = 1;
  $export['islandora_pdf_create_fulltext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_path_to_pdftotext';
  $strongarm->value = '/usr/local/bin/pdftotext';
  $export['islandora_pdf_path_to_pdftotext'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_preview_height';
  $strongarm->value = '700';
  $export['islandora_pdf_preview_height'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_preview_width';
  $strongarm->value = '500';
  $export['islandora_pdf_preview_width'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_thumbnail_height';
  $strongarm->value = '200';
  $export['islandora_pdf_thumbnail_height'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_thumbnail_width';
  $strongarm->value = '200';
  $export['islandora_pdf_thumbnail_width'] = $strongarm;

  return $export;
}
