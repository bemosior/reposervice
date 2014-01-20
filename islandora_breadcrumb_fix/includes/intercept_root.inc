<?php

/**
 * @file
 * This file contains helper functions used throughout this module.
 */

/**
 * Callback for interception to root Islandora node.
 */
function islandora_breadcrumb_intercept_root() {
	drupal_goto('<front>');
}