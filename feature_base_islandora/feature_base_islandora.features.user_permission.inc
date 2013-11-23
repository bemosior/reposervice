<?php
/**
 * @file
 * feature_base_islandora.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function feature_base_islandora_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'Associate XML Forms'.
  $permissions['Associate XML Forms'] = array(
    'name' => 'Associate XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: 'Create XML Forms'.
  $permissions['Create XML Forms'] = array(
    'name' => 'Create XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: 'Delete XML Forms'.
  $permissions['Delete XML Forms'] = array(
    'name' => 'Delete XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: 'Edit XML Forms'.
  $permissions['Edit XML Forms'] = array(
    'name' => 'Edit XML Forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: 'List XML Forms'.
  $permissions['List XML Forms'] = array(
    'name' => 'List XML Forms',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'xml_form_builder',
  );

  // Exported permission: 'add fedora datastreams'.
  $permissions['add fedora datastreams'] = array(
    'name' => 'add fedora datastreams',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: 'administer islandora ip embargoes'.
  $permissions['administer islandora ip embargoes'] = array(
    'name' => 'administer islandora ip embargoes',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_ip_embargo',
  );

  // Exported permission: 'administer islandora solr'.
  $permissions['administer islandora solr'] = array(
    'name' => 'administer islandora solr',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_solr',
  );

  // Exported permission: 'administer masquerade'.
  $permissions['administer masquerade'] = array(
    'name' => 'administer masquerade',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'bypass inactive object state'.
  $permissions['bypass inactive object state'] = array(
    'name' => 'bypass inactive object state',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_simple_workflow',
  );

  // Exported permission: 'control islandora ip embargoes'.
  $permissions['control islandora ip embargoes'] = array(
    'name' => 'control islandora ip embargoes',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_ip_embargo',
  );

  // Exported permission: 'create child collection'.
  $permissions['create child collection'] = array(
    'name' => 'create child collection',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_basic_collection',
  );

  // Exported permission: 'delete fedora objects and datastreams'.
  $permissions['delete fedora objects and datastreams'] = array(
    'name' => 'delete fedora objects and datastreams',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: 'edit fedora metadata'.
  $permissions['edit fedora metadata'] = array(
    'name' => 'edit fedora metadata',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: 'ingest fedora objects'.
  $permissions['ingest fedora objects'] = array(
    'name' => 'ingest fedora objects',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: 'manage collection policy'.
  $permissions['manage collection policy'] = array(
    'name' => 'manage collection policy',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_basic_collection',
  );

  // Exported permission: 'manage inactive objects'.
  $permissions['manage inactive objects'] = array(
    'name' => 'manage inactive objects',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_simple_workflow',
  );

  // Exported permission: 'manage islandora ip embargoes'.
  $permissions['manage islandora ip embargoes'] = array(
    'name' => 'manage islandora ip embargoes',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_ip_embargo',
  );

  // Exported permission: 'manage object properties'.
  $permissions['manage object properties'] = array(
    'name' => 'manage object properties',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora',
  );

  // Exported permission: 'masquerade as admin'.
  $permissions['masquerade as admin'] = array(
    'name' => 'masquerade as admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'masquerade as user'.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'migrate collection members'.
  $permissions['migrate collection members'] = array(
    'name' => 'migrate collection members',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_basic_collection',
  );

  // Exported permission: 'search islandora solr'.
  $permissions['search islandora solr'] = array(
    'name' => 'search islandora solr',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'islandora_solr',
  );

  // Exported permission: 'view fedora repository objects'.
  $permissions['view fedora repository objects'] = array(
    'name' => 'view fedora repository objects',
    'roles' => array(
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'islandora',
  );

  // Exported permission: 'view technical metadata'.
  $permissions['view technical metadata'] = array(
    'name' => 'view technical metadata',
    'roles' => array(
      'Collection Supervisor' => 'Collection Supervisor',
      'Data Entry Supervisor' => 'Data Entry Supervisor',
      'Mediated Data Entry' => 'Mediated Data Entry',
      'Repository Administrator' => 'Repository Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'islandora_fits',
  );

  return $permissions;
}
