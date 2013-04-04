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

  // Exported role: Islandora Collection Supervisor.
  $roles['Islandora Collection Supervisor'] = array(
    'name' => 'Islandora Collection Supervisor',
    'weight' => '5',
  );

  // Exported role: IslandoraAdmin.
  $roles['IslandoraAdmin'] = array(
    'name' => 'IslandoraAdmin',
    'weight' => '3',
  );

  // Exported role: Mediated Data Entry.
  $roles['Mediated Data Entry'] = array(
    'name' => 'Mediated Data Entry',
    'weight' => '4',
  );

  return $roles;
}
