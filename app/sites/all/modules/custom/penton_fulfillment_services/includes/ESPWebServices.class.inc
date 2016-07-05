<?php
/**
 * @file
 * ESP Web Services class.
 */

class ESPWebServices {

  /**
   * Constructor.
   */
  public function __construct(&$user_object = NULL) {

    if (!variable_get('esp_web_services_enable', FALSE)) {
      return FALSE;
    }

    $this->pubcode = variable_get('esp_web_services_pubcode', '');

    if (empty($this->pubcode)) {
      return FALSE;
    }

    $this->subaccttype = variable_get('esp_web_services_subaccttype', array());
    $this->cuid = variable_get('esp_web_services_cuid', NULL);
    $this->cpwd = variable_get('esp_web_services_cpwd', NULL);
    $this->sandbox_mode = variable_get('esp_web_services_sandbox_mode', FALSE);

    if (is_object($user_object)) {
      $this->user = $user_object;
    }
    else {
      if (arg(0) == 'user' && is_numeric(arg(1))) {
        $uid = arg(1);
        $this->user = ($GLOBALS['user']->uid != $uid) ? user_load($uid) : $GLOBALS['user'];
      }
      else {
        $this->user = $GLOBALS['user'];
      }
    }
  }

  /**
   * Setup the current instance of the class.
   */
  public static function getInstance(&$user_object = NULL) {
    if (is_object($user_object)) {
      $instance = new ESPWebServices($user_object);
      return $instance;
    }
    else {
      // Static variable to hold the instance of this object
      // when called in a singleton pattern.
      static $instance;
      $instance = (isset($instance)) ? $instance : new ESPWebServices();
      return $instance;
    }

  }

  /**
   * Get Service URL.
   *
   * @return string
   *   Service URL, based on mode.
   */
  public function getServiceUrl() {

    return ($this->sandbox_mode) ? 'https://espdev.espcomp.net/' : 'https://www.pubservice.com/';

  }

  /**
   * Get Service URI.
   *
   * @param string $action
   *   Action.
   *
   * @return string|boolean
   *   Service URI, based on publication code,
   *   or FALSE if action is not "subscribe".
   */
  public function getServiceUri($action = 'subscribe') {

    if ($action != 'subscribe') {
      return FALSE;
    }

    if ($this->pubcode == 'RN') {
      return $this->pubcode . '/subscribe.aspx';
    }
    else {
      // If $this->pubcode is SN, TE or anything else.
      return $this->pubcode . '/subnew.aspx';
    }

  }

  /**
   * Get Valid Rate Keys/Renewal Prices (WS2100).
   *
   * This Web Service is to provide current offers and rates for
   * new and existing subscribers. The rules are established by the client,
   * but are maintained at ESP.
   *
   * @todo This function current returns an empty value, due to a bug
   *   in the ESP API. The developers of the API have been notified,
   *  and they are currently working on a fix.
   *
   * @param string $acctno
   *   Account number.
   * @param string $ratekey
   *   Rate key.
   * @param string $promkey
   *   Promo key.
   *
   * @return string
   *   XML with Valid Rate Keys/Renewal Prices.
   */
  public function getValidRateKeys($acctno, $ratekey = NULL, $promkey = NULL) {

    $request  = '<?xml version="1.0" encoding="utf-8" ?>';
    $request .= '<ws2100request>';
    $request .= "<pubcode>{$this->pubcode}</pubcode>";
    $request .= "<acctno>{$acctno}</acctno>";
    $request .= "<ratekey>{$ratekey}</rratekey>";
    $request .= "<promkey>{$promkey}</promkey>";
    $request .= '</ws2100request>';

    return self::postRequest($request, 'ws2100');

  }

  /**
   * Obtain Current Account Information (WS1400).
   *
   * This Web Service will return the requested account details
   * for the requested account. It will also return information
   * on all accounts that are held by this person.
   *
   * @param string $acctno
   *   Account number.
   *
   * @return string
   *   XML with Current Account Information.
   */
  public function obtainCurrentAccountInformation($acctno) {

    $request  = '<?xml version="1.0" encoding="utf-8" ?>';
    $request .= '<ws1400request>';
    $request .= "<pubcode>{$this->pubcode}</pubcode>";
    $request .= "<acctno>{$acctno}</acctno>";
    $request .= '</ws1400request>';

    return self::postRequest($request, 'ws1400');

  }

  /**
   * Verify Existing Logon Request (WS1000).
   *
   * This Web Service is designed to use very little bandwidth and return
   * the subscriber's status as quickly as possible. Information is returned
   * that is used to determine if the user is authorized to access content.
   * Additional information about the subscriber is provided about the level
   * of access to grant and other useful information such as expiration date
   * of the subscription and credit cards.
   *
   * @param string $uid
   *   Account Number.
   * @param string $upwd
   *   Zip Code.
   *
   * @return array
   *   Array with return code, status, account type,
   *   expire date and access flag.
   */
  public function verifyExistingUserLogonRequest($uid, $upwd) {

    $request  = '<?xml version="1.0" encoding="utf-8" ?>';
    $request .= '<ws1000request>';
    $request .= "<pubcode>{$this->pubcode}</pubcode>";
    $request .= "<uid>{$uid}</uid>";
    $request .= "<upwd>{$upwd}</upwd>";
    $request .= '</ws1000request>';

    $xml = self::postRequest($request, 'ws1000');

    if (is_array($xml)) {
      // Most likely, the ESP Web Services server is temporarily down.
      // Therefore, return the result as FALSE,
      // leaving any current user data intact.
      if ($xml['CURLINFO_HTTP_CODE'] == 0) {
        return FALSE;
      }
    }

    // For more accurate parsing, this node must be trimmed,
    // in order to remove white-space.
    $xml->expiredate->{0} = trim($xml->expiredate->{0});

    if ($xml->returncode->{0} == 0) {
      $xml->expiredate->{0} = date('n/j/Y');
    }

    if (empty($xml->expiredate->{0})) {
      if (($xml->accttype->{0} == 'C' || $xml->accttype->{0} == 'S') && $xml->status->{0} == 'A') {
        $xml->expiredate->{0} = date('n/j/') . (date('Y') + 1);
      }
      else {
        $xml->expiredate->{0} = date('n/j/Y');
      }
    }

    if (strpos($xml->expiredate->{0}, 'AM') !== FALSE || strpos($xml->expiredate->{0}, 'PM') !== FALSE) {
      list($date, $time, $meridiem) = explode(' ', $xml->expiredate->{0});
      $xml->expiredate->{0} = $date;
    }

    list($month, $day, $year) = explode('/', $xml->expiredate->{0});

    // Remove leading "0" from month, if present.
    if (strlen($month) == 2 && substr($month, 0, 1) == 0) {
      $month = substr($month, 1);
    }

    // Remove leading "0" from day, if present.
    if (strlen($day) == 2 && substr($day, 0, 1) == 0) {
      $day = substr($day, 1);
    }

    if ($xml->accttype->{0} == 'C' || $xml->accttype->{0} == 'S') {
      $access_granted = $xml->status->{0} == 'A';
    }
    elseif ($xml->accttype->{0} == 'R') {
      $access_granted = $xml->status->{0} == 'A' || $xml->status->{0} == 'H' || $xml->status->{0} == 'P';
    }
    else {
      $access_granted = FALSE;
    }

    return array(
      'returncode' => trim($xml->returncode->{0}),
      'access_granted' => $access_granted,
      'status' => trim($xml->status->{0}),
      'accttype' => trim($xml->accttype->{0}),
      'expiredate' => array(
        'year' => $year,
        'month' => $month,
        'day' => $day,
      ),
    );

  }

  /**
   * Post a request via cURL.
   *
   * @param string $request
   *   Request to send.
   * @param string $service
   *   Service (read documentation for more information).
   *
   * @return string|NULL
   *   XML if request is successful or NULL otherwise.
   */
  private function postRequest($request = NULL, $service = NULL) {

    if (is_null($request) || is_null($service)) {
      return FALSE;
    }

    $fields = array(
      'CUID' => urlencode($this->cuid),
      'CPWD' => urlencode($this->cpwd),
      'REQ' => urlencode($request),
    );

    $post_fields = '';

    foreach ($fields as $key => $value) {
      $post_fields .= $key . '=' . $value . '&';
    }

    rtrim($post_fields, '&');

    $ch = curl_init();

    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 60);
    curl_setopt($ch, CURLOPT_POST, TRUE);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $post_fields);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_URL, self::getServiceUrl() . 'wsrvc/Listener.asmx/' . $service);

    $curl_exec = curl_exec($ch);

    // Get information regarding the transfer.
    $curl_getinfo = array();
    $curl_getinfo['CURLINFO_HTTP_CODE'] = curl_getinfo($ch, CURLINFO_HTTP_CODE);

    curl_close($ch);

    if ($curl_getinfo['CURLINFO_HTTP_CODE'] != 200) {
      return $curl_getinfo;
    }

    if (!self::isXML($curl_exec)) {
      return NULL;
    }
    else {
      return simplexml_load_string($curl_exec);
    }

  }

  /**
   * Checks if string is xml.
   *
   * @param string $xml
   *   String to check.
   * @param bool $output_errors
   *   TRUE to return errors.
   *
   * @return bool|array
   *   TRUE if string is XML or FALSE otherwise or array of errors.
   */
  private static function isXML($xml = NULL, $output_errors = FALSE) {

    libxml_use_internal_errors(TRUE);
    libxml_clear_errors();

    $string = simplexml_load_string($xml);

    if (!$string) {
      if ($output_errors) {
        $libxml_get_errors = libxml_get_errors();

        $errors = array();

        foreach ($libxml_get_errors as $error) {
          $errors[] = $error->message;
        }

        libxml_clear_errors();

        return $errors;
      }

      return FALSE;
    }

    return TRUE;

  }

}
