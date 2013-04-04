<?php
/**
 * @file
 * lyr_base_islandora.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lyr_base_islandora_user_default_permissions() {
  $permissions = array();

  // Exported permission: Associate XML Forms.
  $permissions['Associate XML Forms'] = array(
    'name' => 'Associate XML Forms',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: Create XML Forms.
  $permissions['Create XML Forms'] = array(
    'name' => 'Create XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: Delete XML Forms.
  $permissions['Delete XML Forms'] = array(
    'name' => 'Delete XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: Edit XML Forms.
  $permissions['Edit XML Forms'] = array(
    'name' => 'Edit XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: List XML Forms.
  $permissions['List XML Forms'] = array(
    'name' => 'List XML Forms',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: add fedora datastreams.
  $permissions['add fedora datastreams'] = array(
    'name' => 'add fedora datastreams',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: administer islandora solr.
  $permissions['administer islandora solr'] = array(
    'name' => 'administer islandora solr',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_solr',
  );

  // Exported permission: administer masquerade.
  $permissions['administer masquerade'] = array(
    'name' => 'administer masquerade',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: bypass inactive object state.
  $permissions['bypass inactive object state'] = array(
    'name' => 'bypass inactive object state',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_simple_workflow',
  );

  // Exported permission: create child collection.
  $permissions['create child collection'] = array(
    'name' => 'create child collection',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_basic_collection',
  );

  // Exported permission: delete fedora objects and datastreams.
  $permissions['delete fedora objects and datastreams'] = array(
    'name' => 'delete fedora objects and datastreams',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: edit fedora metadata.
  $permissions['edit fedora metadata'] = array(
    'name' => 'edit fedora metadata',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: ingest fedora objects.
  $permissions['ingest fedora objects'] = array(
    'name' => 'ingest fedora objects',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: manage collection policy.
  $permissions['manage collection policy'] = array(
    'name' => 'manage collection policy',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_basic_collection',
  );

  // Exported permission: manage inactive objects.
  $permissions['manage inactive objects'] = array(
    'name' => 'manage inactive objects',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_simple_workflow',
  );

  // Exported permission: manage object properties.
  $permissions['manage object properties'] = array(
    'name' => 'manage object properties',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: masquerade as admin.
  $permissions['masquerade as admin'] = array(
    'name' => 'masquerade as admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: masquerade as user.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(
      'IslandoraAdmin' => 'IslandoraAdmin',
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: migrate collection members.
  $permissions['migrate collection members'] = array(
    'name' => 'migrate collection members',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_basic_collection',
  );

  // Exported permission: search islandora solr.
  $permissions['search islandora solr'] = array(
    'name' => 'search islandora solr',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'islandora_solr',
  );

  // Exported permission: view fedora repository objects.
  $permissions['view fedora repository objects'] = array(
    'name' => 'view fedora repository objects',
    'roles' => array(
      'Islandora Collection Supervisor' => 'Islandora Collection Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'islandora',
  );

  return $permissions;
}
