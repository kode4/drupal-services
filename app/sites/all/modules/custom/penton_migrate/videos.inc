<?php
/**
 * @file
 * Video migration.
 * The naming is concerned with legacy Video migration into new Articles.
 * This is not one class for migrating all content into new Article
 * content-types.
 */

/**
 * Class PiscesVideoMigration
 *
 * Migrate legacy Videos into Drupal 7.
 *
 * @author James Linnell james.linnell@ixxus.com
 */
class PiscesVideoMigration extends PentonArticleMigration {

  // Where to suck the images and files to.
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
    $this->dependencies[] = 'Galleries';
    $this->dependencies[] = 'Links';
    $this->dependencies[] = 'PressReleases';

    // Set Author ID.
    $this->addFieldMapping('field_penton_author', 'field_author')
      ->sourceMigration('Authors');

    // Gating mapping.
    $this->addFieldMapping('field_penton_privacy_settings', 'gatingLevel');
    $this->addFieldMapping('field_penton_privacy_settings:source_type')
      ->defaultValue('rid');

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

    // Article Type.
    $this->addFieldMapping('field_penton_article_type', 'articleTypes');
    $this->addFieldMapping('field_penton_article_type:source_type')
      ->defaultValue('tid');

    // Image and Video mapping.
    // Image mapping.
    $this->addFieldMapping('field_penton_link_media_feat_img', 'mediaAssets');
    $this->addFieldMapping('field_penton_link_media_feat_img:source_type')
      ->defaultValue('nid');

    $this->addFieldMapping('field_penton_link_media_entity', 'media_assets');
    $this->addFieldMapping('field_penton_link_media_entity:source_type')
      ->defaultValue('nid');

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

    // Set gating level.
    $row->gatingLevel = $this->prepareGating($row);
    // Exclude from lists.
    if (isset($row->field_exclude_from_lists)) {
      $row->rssFlag = $this->includeInRSS($row->field_exclude_from_lists);
    }
    else {
      // Well there is no value so this is like saying it's set to zero and in
      // that case needs to be converted to 1.
      $row->rssFlag = 1;
    }

    // Article Type.
    $row->articleTypes = $this->articleType("Video");

    $media_assets = array();
    if (isset($row->field_video_upload)) {
      $media_assets = $this->videoMigration($row->field_video_upload, $row->nid, $row->title, $row->created, 'file');
    }
    else {
      $media_assets = $this->videoMigration($row->field_embedded_video, $row->nid, $row->title, $row->created, 'embed');
    }

    // Create media asset from image promo.
    $image_assets = array();
    if (isset($row->field_image_promo)) {
      $credits = "";
      if (isset($row->field_image_promo_credits)) {
        $credits = $row->field_image_promo_credits;
      }
      $row->mediaAssets = $this->imagePromoMigration($row->nid, $row->field_image_promo, self::IMAGE_DEST_DIR, variable_get('penton_migrate_asset_host', 'http://waste360legacy.penton.ixxus.com'), $credits, $row->created);
    }

    // In the source db, there might be some data which does not really exist.
    // This results in creating a stub, which we don't need. Crosscheck the node
    // in the source corresponds to a term in destination.
    if (isset($row->field_content_source)) {
      $source_nid = (int) $row->field_content_source[0];
      if (!$this->nodeIsMapped($source_nid)) {
        unset($row->field_content_source);
      }
    }

    $row->media_assets = $media_assets;
    $row->Assets = array_merge($image_assets, $media_assets);
  }

  /**
   * Create a media entity of type video.
   *
   * This will be blank if a file is on the legacy node.
   * Embed code will be included if it is an embedded video.
   *
   * @author James Linnell james.linnell@ixxus.com
   *
   * @param array $video
   *   The video embed code.
   * @param string $title
   *   Title of the media entity.
   * @param null $video_type
   *   Check it's to be embedded.
   *
   * @return array
   *   Return an array of node ids.
   */
  protected function videoMigration($video, $nid, $title, $created, $video_type = 'embed') {
    $nids = array();
    $node = array();
    // Creation date.
    $node['created'] = $created;
    switch ($video_type) {
      case 'embed':
        // Query the database to get video embed details.
        $query = $this->sourceDbConnection()
          ->select('content_type_video', 'ctv')
          ->fields('ctv');
        $query->where('ctv.nid=:nid', array(':nid' => $nid));
        $result = $query->execute();
        $info = $result->fetchObject();

        // Set the node fields.
        if (isset($info->field_embedded_video_title)) {
          $node['title'] = $info->field_embedded_video_title;
        }
        else {
          $node['title'] = $title;
        }

        if (isset($info->field_embedded_video_provider)) {
          $node['mimetype'] = $info->field_embedded_video_provider;
        }
        $node['embed'] = $video;
        if (isset($info->field_embedded_video_description)) {
          $node['description'] = $info->field_embedded_video_description;
        }
        break;

      case 'file':
        // Video files are not being migrated but a placeholder media entity is
        // being created for future embed.
        $node['title'] = $title;
        $node['description'] = t('This is a placeholder media entity for a video embed. It was created from a migration of videos where the video had a physical file');
        break;

      default:
        break;

    }
    $nid = $this->createMediaEntity($node, NULL);
    array_push($nids, $nid);
    return $nids;
  }
}
