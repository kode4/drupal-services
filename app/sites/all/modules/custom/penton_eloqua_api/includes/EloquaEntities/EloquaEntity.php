<?php
/**
 * @file
 * Realizes Eloqua entity class.
 */

/**
 * Class for Eloqua entity.
 */
class EloquaEntity {

  private static $apiClient;
  private static $cachedData;

  /**
   * Initialize.
   */
  public static function initialize($api_client) {
    self::$apiClient = $api_client;
    self::$cachedData = array();
  }

  /**
   * Returns cached data.
   */
  public static function getCachedData($name) {
    $value = array();

    if (isset(self::$cachedData[$name])) {
      $value = self::$cachedData[$name];
    }

    return $value;
  }

  /**
   * Puts data into cache.
   */
  public static function setCachedData($name, $value) {
    if (!self::getCachedData($name)) {
      self::$cachedData[$name] = $value;
    }
  }

  /**
   * Returns API client.
   */
  public static function apiClient() {
    return self::$apiClient;
  }

  /**
   * Returns true if API client has errors.
   */
  public static function checkForErrors() {
    return self::$apiClient->hasError();
  }

}
