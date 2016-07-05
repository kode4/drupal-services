<?php
/**
 * @file
 * Realizes Eloqua API REST client.
 */

/**
 * REST client for Eloqua's API.
 */
class EloquaRESTClient {
  private $ch;
  public $baseUrl;
  public $responseInfo;

  const ELOQUA_LOGIN_URL = "https://login.eloqua.com";
  const ELOQUA_DEFAULT_API_VER = "2.0";

  /**
   * Constructor.
   */
  public function __construct($user, $pass, $base_url = NULL) {
    if (empty($base_url)) {
      $base_url = self::getBaseUrl($user, $pass);
    }

    // Basic authentication credentials.
    $credentials = $user . ':' . $pass;

    // Set the base URL for the API endpoint.
    $this->baseUrl = $base_url;

    // Initialize the cURL resource.
    $this->ch = curl_init();

    // Set cURL and credential options.
    curl_setopt($this->ch, CURLOPT_URL, $this->baseUrl);
    curl_setopt($this->ch, CURLOPT_USERPWD, $credentials);

    // Set headers.
    $headers = array('Content-type: application/json');
    curl_setopt($this->ch, CURLOPT_HTTPHEADER, $headers);

    // Return transfer as string.
    curl_setopt($this->ch, CURLOPT_RETURNTRANSFER, TRUE);
  }

  /**
   * Destructor.
   */
  public function __destruct() {
    curl_close($this->ch);
  }

  /**
   * Returns result of GET request.
   */
  public function get($url, $query = array()) {
    $url .= empty($query) ? '' : "?" . http_build_query($query);
    return $this->executeRequest($url, 'GET');
  }

  /**
   * Returns result of POST request.
   */
  public function post($url, $data) {
    return $this->executeRequest($url, 'POST', $data);
  }

  /**
   * Returns result of PUT request.
   */
  public function put($url, $data) {
    return $this->executeRequest($url, 'PUT', $data);
  }

  /**
   * Returns result of DELETE request.
   */
  public function delete($url) {
    return $this->executeRequest($url, 'DELETE');
  }

  /**
   * Executes request with given parameters.
   */
  public function executeRequest($url, $method, $data = NULL) {
    // Set the full URL for the request.
    curl_setopt($this->ch, CURLOPT_URL, $this->baseUrl . '/' . $url);

    switch ($method) {
      case 'GET':
        curl_setopt($this->ch, CURLOPT_CUSTOMREQUEST, 'GET');
        break;

      case 'POST':
        curl_setopt($this->ch, CURLOPT_CUSTOMREQUEST, 'POST');
        curl_setopt($this->ch, CURLOPT_POSTFIELDS, json_encode($data));
        break;

      case 'PUT':
        curl_setopt($this->ch, CURLOPT_CUSTOMREQUEST, 'PUT');
        curl_setopt($this->ch, CURLOPT_POSTFIELDS, json_encode($data));
        break;

      case 'DELETE':
        curl_setopt($this->ch, CURLOPT_CUSTOMREQUEST, 'DELETE');
        break;

      default:
        break;
    }

    // Execute the request.
    $response = curl_exec($this->ch);

    // Store the response info including the HTTP status.
    $this->responseInfo = curl_getinfo($this->ch);
    return json_decode($response);
  }

  /**
   * Returns Eloqua API URL.
   */
  private static function getBaseUrl($user, $pass) {
    $base_url = self::ELOQUA_LOGIN_URL;
    $connection = new EloquaRESTClient($user, $pass, $base_url);

    $response = $connection->get('id');
    if (isset($response->urls)) {
      return str_replace('{version}/', self::ELOQUA_DEFAULT_API_VER, $response->urls->apis->rest->standard);
    }
    else {
      throw new Exception("Invalid Eloqua credentials or network problem");
    }
  }

  /**
   * Returns TRUE is request ended with 400 error.
   */
  public function hasError() {
    if ($this->responseInfo['http_code'] >= 400) {
      return TRUE;
    }

    return FALSE;
  }

}
