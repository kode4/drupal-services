<?php
/**
 * @file
 * Realizes Eloqua API credentials storage.
 */

/**
 * Eloqua API credentials class.
 */
class EloquaCredentials {
  private $eloquaUsername;
  private $eloquaPassword;
  private $eloquaBaseURL;

  /**
   * Constructor.
   */
  public function __construct($eloqua_username, $eloqua_password, $eloqua_base_url = NULL) {
    $this->eloquaPassword = $eloqua_password;
    $this->eloquaUsername = $eloqua_username;
    $this->eloquaBaseURL = $eloqua_base_url;

    if (empty($eloqua_username) || empty($eloqua_password)) {
      throw new Exception('Empty Eloqua credentials');
    }
  }

  /**
   * Returns Eloqua API URL.
   */
  public function getEloquaBaseURL() {
    return $this->eloquaBaseURL;
  }

  /**
   * Returns Eloqua API password.
   */
  public function getEloquaPassword() {
    return $this->eloquaPassword;
  }

  /**
   * Returns Eloqua API username.
   */
  public function getEloquaUsername() {
    return $this->eloquaUsername;
  }

}
