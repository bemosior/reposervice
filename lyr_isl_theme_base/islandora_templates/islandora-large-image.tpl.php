<?php
/**
 * @file
 * This is the template file for the object page for large image
 *
 * Available variables:
 * - $islandora_object: The Islandora object rendered in this template file
 * - $islandora_dublin_core: The DC datastream object
 * - $dc_array: The DC datastream object values as a sanitized array. This
 *   includes label, value and class name.
 * - $islandora_object_label: The sanitized object label.
 * - $parent_collections: An array containing parent collection(s) info.
 *   Includes collection object, label, url and rendered link.
 * - $islandora_thumbnail_img: A rendered thumbnail image.
 * - $islandora_content: A rendered image. By default this is the JPG datastream
 *   which is a medium sized image. Alternatively this could be a rendered
 *   viewer which displays the JP2 datastream image.
 *
 * @see template_preprocess_islandora_large_image()
 * @see theme_islandora_large_image()
 */
?>

<div id="tabs">

  <ul>
    <li><a href="#tabs-1">Summary</a></li>
    <li><a href="#tabs-2">Full Description</a></li>
  </ul>

  <div id="tabs-1">

    <div class="islandora-large-image-object islandora">
      <div class="islandora-large-image-content-wrapper clearfix">
        <?php if ($islandora_content): ?>
          <?php if (isset($image_clip)): ?>
            <?php print $image_clip; ?>
          <?php endif; ?>
          <div class="islandora-large-image-content">
            <?php print $islandora_content; ?>
          </div>
        <?php endif; ?>
        <div class="islandora-large-image-sidebar">
          <div class="islandora-definition-row">
            <table class="islandora-table-display">
              <tbody>
                <?php foreach (array('mods:description', 'mods:creator', 'mods:contributor', 'mods:subject', 'mods:date') as $key): ?>
                  <?php if (array_key_exists($key, $mods_array)): ?>
                    <?php $mods_element = $mods_array[$key]; ?>
                    <?php if (isset($mods_element['value'])): ?>
                      <tr>
                        <th class="full-description-heading"><?php print $mods_element['label']; ?>:</th>
                        <td class="<?php print $mods_element['class']; ?>"><?php print $mods_element['value']; ?></td>
                      </tr>
                    <?php endif; ?>
                  <?php endif; ?>
                <?php endforeach; ?>
              </tbody>
            </table>
          </div>
        </div>

      </div>
    </div>
  </div>
  <div id="tabs-2">
    <div class="islandora-basic-image-sidebar">
      <div>
        <table class="islandora-table-display">
          <tbody>
            <?php $row_field = 0; ?>
            <?php foreach ($mods_array as $key => $value): ?>

              <?php if (trim($value['value']) != ''): ?>

                <tr class="islandora-definition-row">
                  <th class="full-description-heading<?php print $row_field == 0 ? ' first' : ''; ?>">
                    <?php print $value['label']; ?>:
                  </th>
                  <td class="<?php print $value['class']; ?><?php print $row_field == 0 ? ' first' : ''; ?>">
                    <?php print $value['value']; ?>
                  </td>

                  <?php if ($row_field == 0): ?>
                    <?php if (isset($islandora_thumbnail_img)): ?>
                      <td class="islandora-basic-image-thumbnail" rowspan="4">
                        <?php print $islandora_thumbnail_img; ?>
                      </td>
                    <?php endif; ?>
                  <?php endif; ?>
                  <?php if (($row_field >= 8) && isset($islandora_thumbnail_img)): ?>
                    <td></td>
                  <?php endif; ?>
                </tr>

                <?php $row_field++; ?>

              <?php endif; ?>

            <?php endforeach; ?>
            <?php if ($parent_collections): ?>
              <tr class="islandora-definition-row">
                <th class="full-description-heading">
                  In Collections:
                </th>
                <td>
                  <ul>
                    <?php foreach ($parent_collections as $collection): ?>
                      <li><?php print l($collection->label, "islandora/object/{$collection->id}"); ?></li>
                    <?php endforeach; ?>
                  </ul>
                </td>
                <td></td>
              </tr>
            <?php endif; ?>

          </tbody>
        </table>
      </div>
    </div>
  </div>
</div>