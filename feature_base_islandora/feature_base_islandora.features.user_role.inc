<?php
/**
 * @file
 * feature_base_islandora.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function feature_base_islandora_user_default_roles() {
  $roles = array();

  // Exported role: Islandora Administrator.
  $roles['Islandora Administrator'] = array(
    'name' => 'Islandora Administrator',
    'weight' => '3',
  );

  // Exported role: Islandora Collection Supervisor.
  $roles['Islandora Collection Supervisor'] = array(
    'name' => 'Islandora Collection Supervisor',
    'weight' => '5',
  );

  // Exported role: Mediated Data Entry.
  $roles['Mediated Data Entry'] = array(
    'name' => 'Mediated Data Entry',
    'weight' => '4',
  );

  return $roles;
}
