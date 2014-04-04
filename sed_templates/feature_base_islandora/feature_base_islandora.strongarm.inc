<?php
/**
 * @file
 * feature_base_islandora.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function feature_base_islandora_strongarm() {
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
  $strongarm->value = '${PATH_IMAGEMAGICK_CONVERT}';
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
  $strongarm->name = 'islandora_book_ingest_derivatives';
  $strongarm->value = array(
    'pdf' => 'pdf',
    'image' => 'image',
    'ocr' => 'ocr',
  );
  $export['islandora_book_ingest_derivatives'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_book_page_viewers';
  $strongarm->value = array(
    'name' => array(
      'none' => 'none',
      'islandora_openseadragon' => 'islandora_openseadragon',
    ),
    'default' => 'islandora_openseadragon',
  );
  $export['islandora_book_page_viewers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_book_parent_book_solr_field';
  $strongarm->value = 'RELS_EXT_isMemberOf_uri_ms';
  $export['islandora_book_parent_book_solr_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_book_viewers';
  $strongarm->value = array(
    'name' => array(
      'none' => 'none',
      'islandora_internet_archive_bookreader' => 'islandora_internet_archive_bookreader',
    ),
    'default' => 'islandora_internet_archive_bookreader',
  );
  $export['islandora_book_viewers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_fits_executable_path';
  $strongarm->value = '${PATH_FITS}';
  $export['islandora_fits_executable_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_fits_techmd_dsid';
  $strongarm->value = 'TECHMD';
  $export['islandora_fits_techmd_dsid'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_internet_archive_bookreader_compression';
  $strongarm->value = '4';
  $export['islandora_internet_archive_bookreader_compression'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_internet_archive_bookreader_ocr_filter_field';
  $strongarm->value = 'RELS_EXT_isMemberOf_uri_mt';
  $export['islandora_internet_archive_bookreader_ocr_filter_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_kakadu_url';
  $strongarm->value = '${PATH_KAKADU}';
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
  $strongarm->name = 'islandora_large_image_viewers';
  $strongarm->value = array(
    'name' => array(
      'none' => 'none',
      'islandora_openseadragon' => 'islandora_openseadragon',
    ),
    'default' => 'islandora_openseadragon',
  );
  $export['islandora_large_image_viewers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_lossless';
  $strongarm->value = 1;
  $export['islandora_lossless'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_newspaper_ingest_derivatives';
  $strongarm->value = array(
    'pdf' => 'pdf',
    'image' => 'image',
    'ocr' => 'ocr',
  );
  $export['islandora_newspaper_ingest_derivatives'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_newspaper_page_viewers';
  $strongarm->value = array(
    'name' => array(
      'none' => 'none',
      'islandora_openseadragon' => 'islandora_openseadragon',
    ),
    'default' => 'islandora_openseadragon',
  );
  $export['islandora_newspaper_page_viewers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_ocr_solr_hocr_highlighting_field';
  $strongarm->value = 'text_nodes_HOCR_hlt';
  $export['islandora_ocr_solr_hocr_highlighting_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_ocr_solr_hocr_highlighting_use_fast';
  $strongarm->value = 1;
  $export['islandora_ocr_solr_hocr_highlighting_use_fast'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_ocr_solr_hocr_result_count';
  $strongarm->value = '32';
  $export['islandora_ocr_solr_hocr_result_count'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_ocr_tesseract';
  $strongarm->value = '${PATH_TESSERACT}';
  $export['islandora_ocr_tesseract'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_ocr_tesseract_enabled_languages';
  $strongarm->value = array(
    'eng' => 'eng',
  );
  $export['islandora_ocr_tesseract_enabled_languages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_paged_content_gs';
  $strongarm->value = '${PATH_GS}';
  $export['islandora_paged_content_gs'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_pdf_allow_text_upload';
  $strongarm->value = 1;
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
  $strongarm->value = '${PATH_PDFTOTEXT}';
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

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_base_filter';
  $strongarm->value = '';
  $export['islandora_solr_base_filter'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_base_query';
  $strongarm->value = 'timestamp:[* TO NOW]';
  $export['islandora_solr_base_query'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_base_sort';
  $strongarm->value = 'score asc';
  $export['islandora_solr_base_sort'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_content_model_field';
  $strongarm->value = 'RELS_EXT_hasModel_uri_ms';
  $export['islandora_solr_content_model_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_datastream_id_field';
  $strongarm->value = 'fedora_datastreams_ms';
  $export['islandora_solr_datastream_id_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_debug_mode';
  $strongarm->value = 0;
  $export['islandora_solr_debug_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_dismax_allowed';
  $strongarm->value = '';
  $export['islandora_solr_dismax_allowed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_facet_max_limit';
  $strongarm->value = '20';
  $export['islandora_solr_facet_max_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_facet_min_limit';
  $strongarm->value = '2';
  $export['islandora_solr_facet_min_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_facet_soft_limit';
  $strongarm->value = '10';
  $export['islandora_solr_facet_soft_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_limit_result_fields';
  $strongarm->value = 1;
  $export['islandora_solr_limit_result_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_num_of_results';
  $strongarm->value = '20';
  $export['islandora_solr_num_of_results'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_object_label_field';
  $strongarm->value = 'dc.title';
  $export['islandora_solr_object_label_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_primary_display';
  $strongarm->value = 'default';
  $export['islandora_solr_primary_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_primary_display_table';
  $strongarm->value = array(
    'weight' => array(
      'default' => '0',
      'grid' => '0',
      'table' => '0',
    ),
    'default' => 'default',
    'enabled' => array(
      'grid' => 'grid',
      'table' => 'table',
      'default' => 'default',
    ),
  );
  $export['islandora_solr_primary_display_table'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_query_fields';
  $strongarm->value = 'dc.title^5 dc.subject^2 dc.description^2 dc.creator^2 dc.contributor^1 ds.OCR^3 ds.FULL_TEXT^3 dc.type';
  $export['islandora_solr_query_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_request_handler';
  $strongarm->value = 'standard';
  $export['islandora_solr_request_handler'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_search_boolean';
  $strongarm->value = 'user';
  $export['islandora_solr_search_boolean'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_secondary_display';
  $strongarm->value = array(
    'csv' => 0,
  );
  $export['islandora_solr_secondary_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'islandora_solr_url';
  $strongarm->value = 'http://localhost:8080/solr/';
  $export['islandora_solr_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'masquerade_admin_roles';
  $strongarm->value = array(
    3 => '3',
    1 => 0,
    2 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $export['masquerade_admin_roles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'masquerade_quick_switches';
  $strongarm->value = array(
    0 => '12',
    1 => '13',
    2 => '0',
  );
  $export['masquerade_quick_switches'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'masquerade_test_user';
  $strongarm->value = '';
  $export['masquerade_test_user'] = $strongarm;

  return $export;
}
