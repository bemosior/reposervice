<?php
/**
 * @file
 * This is the template file for the pdf object
 *
 * @TODO: Add documentation about this file and the available variables
 */
?>

<?php if (isset($islandora_object_label)): ?>
  <?php drupal_set_title("$islandora_object_label"); ?>
<?php endif; ?>

<div id="tabs">

  <ul>
    <li><a href="#tabs-1">Summary</a></li>
    <li><a href="#tabs-2">Full Description</a></li>
  </ul>

  <div id="tabs-1">

    <div class="islandora-pdf-object islandora">
      <div class="islandora-pdf-content-wrapper clearfix">
        <?php if (isset($islandora_content)): ?>
          <div class="islandora-pdf-content">
            <?php print $islandora_content; ?>
          </div>
          <?php print $islandora_download_link; ?>
        <?php endif; ?>
        <div class="islandora-pdf-sidebar">
          <div class="islandora-definition-row">
            <table class="islandora-table-display">
              <tbody>
                <?php foreach (array('mods:creator', 'mods:contributor', 'mods:subject', 'mods:date') as $key): ?>
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
    <div class="islandora-pdf-sidebar">
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
                      <td class="islandora-pdf-thumbnail" rowspan="4">
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