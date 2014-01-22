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

  // Exported role: Collection Supervisor.
  $roles['Collection Supervisor'] = array(
    'name' => 'Collection Supervisor',
    'weight' => 4,
  );

  // Exported role: Data Entry Supervisor.
  $roles['Data Entry Supervisor'] = array(
    'name' => 'Data Entry Supervisor',
    'weight' => 5,
  );

  // Exported role: Mediated Data Entry.
  $roles['Mediated Data Entry'] = array(
    'name' => 'Mediated Data Entry',
    'weight' => 6,
  );

  // Exported role: Repository Administrator.
  $roles['Repository Administrator'] = array(
    'name' => 'Repository Administrator',
    'weight' => 3,
  );

  return $roles;
}
