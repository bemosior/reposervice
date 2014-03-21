<?php
/**
 * @file
 * feature_base_islandora.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function feature_base_islandora_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: navigation_manage-inactive-objects:admin/islandora/simple_workflow/list
  $menu_links['navigation_manage-inactive-objects:admin/islandora/simple_workflow/list'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/islandora/simple_workflow/list',
    'router_path' => 'admin/islandora/simple_workflow/list',
    'link_title' => 'Manage inactive objects',
    'options' => array(
      'attributes' => array(
        'title' => 'List of inactive objects.',
      ),
      'identifier' => 'navigation_manage-inactive-objects:admin/islandora/simple_workflow/list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: navigation_manage-ip-embargo-networks:admin/islandora/ip_embargo
  $menu_links['navigation_manage-ip-embargo-networks:admin/islandora/ip_embargo'] = array(
    'menu_name' => 'navigation',
    'link_path' => 'admin/islandora/ip_embargo',
    'router_path' => 'admin/islandora/ip_embargo',
    'link_title' => 'Manage IP Embargo Networks',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'navigation_manage-ip-embargo-networks:admin/islandora/ip_embargo',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Manage IP Embargo Networks');
  t('Manage inactive objects');


  return $menu_links;
}
