<?php

/**
 * @file
 * islandora-basic-collection-wrapper.tpl.php
 *
 * @TODO: needs documentation about file and variables
 */
?>

<?php // module_load_include('inc', 'islandora_solr_search', 'blocks'); ?>

<div class="islandora-basic-collection-wrapper">

  <?php
    $object_id=$islandora_object->id;
    print drupal_render(drupal_get_form('islandora_solr_simple_search_form',$object_id));
  ?>
  
  <div class="islandora-basic-collection clearfix">
    <span class="islandora-basic-collection-display-switch">
      <ul class="links inline">
        <?php foreach ($view_links as $link): ?>
          <li>
            <a <?php print drupal_attributes($link['attributes']) ?>><?php print $link['title'] ?></a>
          </li>
        <?php endforeach ?>
      </ul>
    </span>
    <?php print $collection_pager; ?>
    <?php print $collection_content; ?>
    <?php print $collection_pager; ?>
  </div>
</div>
