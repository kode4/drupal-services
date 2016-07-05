
-- SUMMARY --

This module is an integration of the video hosting plattform http://www.limelight.com/
It offers a field implementation in Drupal via the filefield module by which videos
can be uploaded in Drupal. The videos then will automatically uploaded to
www.limelight.com into the specified account. The video file itself will be
removed from the local disk of Drupal, so the diskspace is not cramed with the
video files.

The conversion of the video, the hosting, the CDN, the player and
everything is used directly from limelight.
So this module is a full featured video integration within Drupal
but without carying about the video conversion, hosting, delivering
and player offering.



-- REQUIREMENTS --

An account on http://www.limelight.com/ is required.
The credentials will be needed and have to be set in the
backend settings of the module on
admin/config/media/field_limelight


-- INSTALLATION --

* Install the module as usual, see http://drupal.org/node/70151 for further information.
* There will be a new field available you can add in the "manage fields" settings within any entity


-- CONFIGURATION --

* You need an account at http://www.limelight.com/
* There is an admin setting at admin/config/media/field_limelight
* Set the requested Limelight credentials there and choose your player
* Configure the field in the "manage fields" settings of your entity
* Ready to go ...



-- CONTACT --

Current maintainers:
* Carsten Müller (Carsten Müller) - https://drupal.org/user/124707
* Jesús Sánchez Balsera (jsbalsera) - https://drupal.org/user/1483672


This project has been sponsored by:

* Bauer Media Group
  The Bauer Media Group is one of Europe‘s leading media companies.
  The Bauer family has managed the publishing company since its inception 138 years ago.
  This continuity in the corporate management is a unique feature of the family-run company
  and a contributing factor in its stable growth and success.
  https://www.bauermedia.com

* Cocomore AG
  Professional Drupal experts, active in the Drupal community, the largest Drupal shop in Germany and Spain
  http://www.cocomore.com/
  https://drupal.org/marketplace/cocomore



