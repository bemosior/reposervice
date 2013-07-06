<?php
/**
 * @file
 * feature_base_islandora.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_base_islandora_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
