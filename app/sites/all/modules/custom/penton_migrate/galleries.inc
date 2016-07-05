<?php
/**
 * @file
 * Gallery migration.
 * The naming  is concerned with legacy Gallery migration into new Articles.
 */

/**
 * Class PiscesGalleryMigration
 *
 * Migrate legacy Galleries into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesGalleryMigration extends PentonArticleMigration {

  // Where to suck the image & files to.
  const IMAGE_DEST_DIR = 'public://';
  const FILES_DEST_DIR = 'public://';

  /**
   * Map fields.
   *
   * @param array $arguments
   *   Array from migration setup.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    // Set dependencies.
    if (!empty($arguments['author_migration'])) {
      $this->authorMigration = $arguments['author_migration'];
      $this->dependencies[] = $this->authorMigration;
    }

    $this->dependencies[] = 'Articles';
    $this->dependencies[] = 'Blogs';
    $this->dependencies[] = 'Datasheets';
    $this->dependencies[] = 'DataTables';

    // Set Author ID.
    $this->addFieldMapping('field_penton_author', 'field_author')
      ->sourceMigration('Authors');

    // Program mapping.
    $this->addFieldMapping('field_penton_program', 'field_content_source')
      ->sourceMigration('Program');
    $this->addFieldMapping('field_penton_program:source_type')
      ->defaultValue('tid');

    // Publication date.
    $this->addFieldMapping('field_penton_published_datetime', 'field_pubdate');
    $this->addFieldMapping('field_penton_published_datetime:timezone', 'field_pubdate:timezone');

    // Exclude from lists.
    $this->addFieldMapping('field_penton_allow_in_rss_feed', 'rssFlag');

    // Related Galleries.
    $this->addFieldMapping('field_penton_related_content', 'relatedContent')
      ->sourceMigration(
        array(
          'Articles',
          'Blogs',
          'Datasheets',
          'DataTables',
          'Galleries',
          'PressReleases',
          'Videos',
          'Links',
        )
      );

    // Image mapping.
    $this->addFieldMapping('field_penton_link_image_gallery', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_image_gallery:source_type')
      ->defaultValue('nid');

    // Image mapping.
    $this->addFieldMapping('field_penton_link_media_feat_img', 'promoAssets');
    $this->addFieldMapping('field_penton_link_media_feat_img:source_type')
      ->defaultValue('nid');

    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // Insert Byline if it exists.
    $this->addFieldMapping('field_penton_byline', 'field_byline');

    // Set the asset migration fields.
    $this->createFileMigrateDirectory(self::IMAGE_DEST_DIR);
    $this->createFileMigrateDirectory(self::FILES_DEST_DIR);
  }

  /**
   * Prepare any migration is a field to field migration won't do.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $row
   *   Source data.
   *
   * @return bool
   *   Returns any changes to source data.
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    // Create media asset from image.
    if (isset($row->field_images)) {
      $image_data = $this->getImageDetails($row->field_images);
      $image_titles = array();
      $image_descriptions = array();
      $image_credits = array();
      $image_alt = array();
      foreach ($image_data as $data) {
        $u_data = unserialize($data);
        array_push($image_titles, $u_data['title']);
        array_push($image_descriptions, $u_data['description']);
        array_push($image_credits, $u_data['gallery_image_credit']);
        if ($u_data['alt'] != "") {
          array_push($image_alt, strip_tags($u_data['alt']));
        }
        else {
          array_push($image_alt, strip_tags($u_data['description']));
        }
      }
      $row->mediaAssets = $this->galleryMigration($row->field_images, self::IMAGE_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $row->created, $image_titles, $image_descriptions, $image_credits, $image_alt);
    }

    // Exclude from lists.
    if (isset($row->field_exclude_from_lists)) {
      $row->rssFlag = $this->includeInRSS($row->field_exclude_from_lists);
    }
    else {
      // Well there is no value so this is like saying it's set to zero and in
      // that case needs to be converted to 1.
      $row->rssFlag = 1;
    }

    // Related Galleries.
    $row->relatedContent = array();
    if (isset($row->field_gallery_related_media)) {
      $row->relatedContent = $row->field_gallery_related_media;
    }

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);

    // Article Type.
    $row->articleTypes = $this->articleType("Gallery");

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        unset($row->field_content_source);
      }
    }

    // Create media asset from image promo.
    if (isset($row->field_image_promo)) {
      $credits = "";
      if (isset($row->field_image_promo_credits)) {
        $credits = $row->field_image_promo_credits;
      }
      $row->promoAssets = $this->imagePromoMigration($row->nid, $row->field_image_promo, self::IMAGE_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $credits, $row->created);
    }
  }

  /**
   * Gallery migration.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $images
   *   Array of images.
   * @param string $local_dir
   *   The local directory to store files.
   * @param string $prod
   *   The production environment.
   * @param null $titles
   *   Array of image titles.
   * @param null $descriptions
   *   Array of image descriptions.
   * @param null $image_credits
   *   Array of image credits.
   *
   * @return array
   *   Return an array of node ids.
   */
  protected function galleryMigration($images, $local_dir, $prod, $created, $titles = NULL, $descriptions = NULL, $image_credits = NULL, $image_alts = NULL) {
    $nids = array();
    if (isset($images)) {
      // Get all the fids.
      foreach ($images as $key => $item) {
        $fid = $item;
        // Query the source db for the file.
        $file_info = $this->fileDetails($fid, $local_dir, $prod);
        $title = $file_info['title'];
        $newfile = $file_info['newfile'];

        $_node = array();
        // Creation date.
        $_node['created'] = $created;
        // Node title.
        if ($titles != NULL) {
          $_node['metatitle'] = $titles[$key];
          if ($titles[$key] != "") {
            $_node['title'] = $titles[$key];
          }
          else {
            $_node['title'] = $title;
          }
        }
        else {
          $_node['title'] = $title;
        }
        if ($descriptions[$key] != NULL) {
          $_node['summary'] = $descriptions[$key];
        }
        // Set the media type.
        $_node['mimetype'] = 'image';
        // Image credits.
        if ($image_credits[$key] != NULL) {
          $_node['image_credits'] = $image_credits[$key];
        }
        // Image alt.
        if ($image_alts[$key] != NULL) {
          if (strlen($image_alts[$key]) > 512) {
            $image_alts[$key] = substr($image_alts[$key], 0, 511);
          }
          $_node['alt'] = preg_replace("/[^A-Za-z0-9 ]/", '', $image_alts[$key]);
        }
        // Prepare node for saving.
        $nid = $this->createMediaEntity($_node, $newfile);
        array_push($nids, $nid);
      }
    }
    // Return the new node IDs.
    return $nids;
  }

}
