<?php
/**
 * @file
 * Penton Content Pillar implementations of MailSystemInterface.
 */

/**
 * Modify the Drupal mail system to send HTML emails through SMTP server.
 */
class PentonMailSystem implements MailSystemInterface {
  protected $formatClass;
  protected $mailClass;

  /**
   * Constructor.
   */
  public function __construct() {
    if (drupal_autoload_class('MimeMailSystem')) {
      $this->formatClass = new MimeMailSystem();
    }
    else {
      $this->formatClass = new DefaultMailSystem();
    }
    if (drupal_autoload_class('SmtpMailSystem')) {
      $this->mailClass = new SmtpMailSystem();
    }
    else {
      $this->mailClass = new DefaultMailSystem();
    }
  }

  /**
   * Concatenate and wrap the e-mail body for HTML mails.
   *
   * @param array $message
   *   A message array, as described in hook_mail_alter() with optional
   *   parameters described in mimemail_prepare_message().
   *
   * @return array
   *   The formatted $message.
   */
  public function format(array $message) {
    return $this->formatClass->format($message);
  }

  /**
   * Send the e-mail message.
   *
   * @see drupal_mail()
   *
   * @param array $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return bool
   *   TRUE if the mail was successfully accepted, otherwise FALSE.
   */
  public function mail(array $message) {
    return $this->mailClass->mail($message);
  }
}
