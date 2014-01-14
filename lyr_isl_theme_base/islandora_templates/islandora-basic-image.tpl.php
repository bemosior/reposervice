<?php
/*
 * islandora-basic-image.tpl.php
 * 
 *
 * 
 * This file overrides the default template provided by the islandora basic image module.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with the program.  If not, see <http ://www.gnu.org/licenses/>.
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

    <div class="islandora-basic-image-object islandora">
      <div class="islandora-basic-image-content-wrapper clearfix">
        <?php if (isset($islandora_medium_img)): ?>
          <div class="islandora-basic-image-content">
            <?php if (isset($islandora_full_url)): ?>
              <?php print l($islandora_medium_img, $islandora_full_url, array('html' => TRUE)); ?>
            <?php elseif (isset($islandora_medium_img)): ?>
              <?php print $islandora_medium_img; ?>
            <?php endif; ?>
          </div>
        <?php endif; ?>
        <div class="islandora-basic-image-sidebar">
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