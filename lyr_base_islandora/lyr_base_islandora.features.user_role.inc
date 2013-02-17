<?php
/**
 * @file
 * lyr_base_islandora.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lyr_base_islandora_user_default_roles() {
  $roles = array();

  // Exported role: IslandoraAdmin.
  $roles['IslandoraAdmin'] = array(
    'name' => 'IslandoraAdmin',
    'weight' => '3',
  );

  return $roles;
}
