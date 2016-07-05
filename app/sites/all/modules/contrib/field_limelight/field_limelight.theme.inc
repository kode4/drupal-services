<?php
/**
 * @file
 * Theme the field using the Field Types AP to integrate videos from http://field_limelight.com
 */


/**
 * Formats a limelight link to display the video.
 *  @see http://www.limelightvideoplatform.com/support/docs/player_api/
 */
function theme_field_limelight_formatter_limelight_link($vars) {
  $content = '';

  if (!empty($vars['media_id']) && !empty($vars['player']) && !empty($vars['width']) && !empty($vars['height'])) {
    // limelight.com video embed code
    $content .= '<span class="LimelightEmbeddedPlayer">';
    $content .= '<script src="http://assets.delvenetworks.com/player/embed.js"></script>';
    $content .= '<object type="application/x-shockwave-flash" id="limelight_player_ ' . $vars['player_id'] . ' "
                name="limelight_player_ ' . $vars['player_id'] . ' " class="LimelightEmbeddedPlayerFlash"
                width="' . $vars['width'] . '" height=" ' . $vars['height'] . ' "
                data="http://assets.delvenetworks.com/player/loader.swf">';
    $content .= '<param name="movie" value="http://assets.delvenetworks.com/player/loader.swf"/>';
    $content .= '<param name="wmode" value="window"/>';
    $content .= '<param name="allowScriptAccess" value="always"/>';
    $content .= '<param name="allowFullScreen" value="true"/>';
    $content .= '<param name="flashVars" value="mediaId=' . $vars['media_id'] . '&playerForm=' . $vars['player_id'] . '&autoplay=false"/>';
    $content .= '</object>';
    $content .= '<script>LimelightPlayerUtil.initEmbed(\'player_' . $vars['player_id'] . ' \');</script>';
    $content .= '</span>';
  }

  return $content;
}


function theme_field_limelight_form_upload_title($vars) {
  $content = '';

  $content .= '<div class="form-upload-field-title" style="font-weight:bold;padding-top:10px;">';
  $content .= t('Videoupload');
  $content .= '</div>';

  return $content;
}
