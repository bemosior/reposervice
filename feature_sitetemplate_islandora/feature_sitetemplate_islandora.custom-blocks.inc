<?php
/**
 * Implements hook_block_info().
 */
function feature_sitetemplate_islandora_block_info() {
	$blocks['SITE_SHORTCODE_hours'] = array(
    	'info' => t('SITE_SHORTCODE Hours'),
    	'region' => 'sidebar_first',
	    'weight' => 5,
	);
  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function feature_sitetemplate_islandora_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'SITE_SHORTCODE_hours':
      $block['subject'] = t('Hours');
      $block['content'] = SITE_SHORTCODE_hours_block_contents();
      break;
  }
  return $block;
}

/**
 * custom html block
 * @return string
 */
function SITE_SHORTCODE_hours_block_contents() {
  return '<p>
	Can Fill In Arbitrary HTML Here 
	</p>
	';
}