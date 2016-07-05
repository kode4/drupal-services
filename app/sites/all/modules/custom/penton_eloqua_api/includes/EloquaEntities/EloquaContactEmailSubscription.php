<?php
/**
 * @file
 * Realizes Eloqua email subscription class.
 */

/**
 * Class for Eloqua contact subscription.
 */
class EloquaContactEmailSubscription {
  public $isSubscribed;

  /**
   * Constructor.
   */
  private function __construct($raw_subscription) {
    foreach ($raw_subscription as $key => $value) {
      $this->$key = $value;
    }
  }

  /**
   * Fetches contact from Eloqua.
   */
  public static function fetch($contact_id, $email_group_id) {
    $url = self::getApiUrl($contact_id, $email_group_id);
    $raw_subscription = EloquaEntity::apiClient()->get($url);

    if (EloquaEntity::checkForErrors() || empty($raw_subscription)) {
      throw new Exception('Contact with given id=' . $contact_id . ' or email group with id=' . $email_group_id . ' do not exist in Eloqua');
    }

    return new EloquaContactEmailSubscription($raw_subscription);
  }

  /**
   * Subscribes contact.
   */
  public function subscribe() {
    if (!$this->isContactSubscribed()) {
      $this->subscribeAndPushContactEmailSubscription();
    }
  }

  /**
   * Subscribes contact and pushes subscription to Eloqua.
   */
  private function subscribeAndPushContactEmailSubscription() {
    $this->setSubscribed();
    $url = self::getApiUrl($this->contactId, $this->emailGroup->id);
    $contact_email_subscription = EloquaEntity::apiClient()->put($url, $this);
    if (EloquaEntity::checkForErrors() || empty($contact_email_subscription)) {
      throw new Exception('Error while subscribing contact #' . $this->contactId . ' to email group #' . $this->emailGroupId->id);
    }
  }

  /**
   * Sets subscribed property.
   */
  private function setSubscribed() {
    $this->isSubscribed = TRUE;
  }

  /**
   * Returns TRUE if contact is subscribed.
   */
  private function isContactSubscribed() {
    return $this->isSubscribed == "TRUE";
  }

  /**
   * Returns Eloqua API URL.
   */
  private static function getApiUrl($contact_id, $email_group_id) {
    return '/data/contact/' . $contact_id . '/email/group/' . $email_group_id . '/subscription';
  }

}
