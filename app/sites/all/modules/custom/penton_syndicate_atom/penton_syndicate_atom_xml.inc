<?php

/**
 * @file
 * Penton syndicate atom xml.
 */

/**
 *  PentonAtomXmlBase is the base xml feed class.
 */
class PentonAtomXmlBase {
  /**
   * @var DOMElement
   */
  public $dom;
  /**
   * @var DOMDocument
   */
  public $root;

  /**
   * PentonAtomXmlBase constructor.
   * 
   * @param string $rootname
   *   Document rootname.
   * 
   * @param string $root
   *   Document root.
   * 
   * @param DOMDocument $dom
   *   Document object.
   */
  public function __construct($rootname = '', $root = NULL, $dom = NULL) {
    if ($dom === NULL) {
      $dom = new DOMDocument('1.0', 'UTF-8');
    }
    $this->dom = $dom;
    if ($root === NULL) {
      $root = $this->addNode($this->dom, $rootname);
    }
    $this->root = $root;
  }
  /**
   * Adds node to the feed.
   * 
   * @param DOMDocument $parent
   *   DOM Document.
   * 
   * @param string $tag
   *   Node's tag.
   * 
   * @param string $content
   *   Node's content.
   * 
   * @param array $atts
   *   Node's attributes.
   * 
   * @return DOMElement
   *   Retruns DOM element.
   */
  public function addNode($parent = NULL, $tag = NULL, $content = NULL, $atts = array()) {
    if ($parent === NULL) {
      $parent = $this->root;
    }
    $node = $this->dom->createElement($tag);
    $parent->appendChild($node);
    if ($content) {
      $content_node = $this->dom->createTextNode($content);
      $node->appendChild($content_node);
    }
    foreach ($atts as $k => $v) {
      $v = (string) $v;
      $node->setAttribute($k, $v);
    }
    return $node;
  }
  /**
   * Adds link to the feed.
   * 
   * @param string $rel
   *   Link rel.
   * @param string $href
   *   Link path.
   * @param string $type
   *   Link type.
   */
  public function addLink($rel, $href, $type = NULL) {
    $atts = array();
    $atts['rel'] = $rel;
    $atts['href'] = $href;
    if ($type !== NULL) {
      $atts['type'] = $type;
    }
    $this->addNode($this->root, 'link', '', $atts);
  }
  /**
   * Adds page title to the feed.
   * 
   * @param string $title
   *   Page title.
   */
  public function addTitle($title) {
    $this->addNode($this->root, 'title', $title, array('type' => 'text'));
  }
  /**
   * Adds page url to the feed.
   * 
   * @param string $id
   *   Page url.
   */
  public function addId($id) {
    $this->addNode($this->root, 'id', $id);
  }
  /**
   * Adds `updated` entry to the feed.
   * 
   * @param string $updated
   *   Last update time.
   */
  public function addUpdated($updated) {
    $this->addNode($this->root, 'updated', $updated);
  }
  /**
   * Dumps the internal XML tree into a string.
   * 
   * @return string|FALSE
   *   Returns string the XML, or FALSE if an error occurred.
   */
  public function toxml() {
    return $this->dom->saveXML($this->root);
  }
}

/**
 * PentonAtomXmlFeed class used for creating xml feed.
 */
class PentonAtomXmlFeed extends PentonAtomXmlBase {
  /**
   * PentonAtomXmlFeed constructor.
   */
  public function __construct() {
    parent::__construct('feed');
    $this->root->setAttribute('xmlns', 'http://www.w3.org/2005/Atom');
    $this->dom->formatOutput = TRUE;
  }
  /**
   * Adds self link to feed.
   * 
   * @param string $link
   *   Self link.
   */
  public function addSelfLink($link) {
    $this->addLink('self', $link, 'application/atom+xml');
  }
  /**
   * Adds an entry to the feed.
   * 
   * @return \PentonAtomXmlEntry
   *   Xml entry.
   */
  public function addEntry() {
    $entry = $this->addNode($this->root, 'entry');
    return new PentonAtomXmlEntry($entry, $this->dom);
  }
}

/**
 * PentonAtomXmlEntry class used for creating feed entry.
 */
class PentonAtomXmlEntry extends PentonAtomXmlBase {
  /**
   * PentonAtomXmlEntry constructor.
   * 
   * @param DOMElement $root
   *   DOMElement obejct.
   * 
   * @param DOMDocument $dom
   *   DOMDocument object.
   */
  public function __construct($root, $dom) {
    parent::__construct('entry', $root, $dom);
    $this->dom->formatOutput = TRUE;
  }
  /**
   * Adds url to the entry. 
   * 
   * @param string $url
   *   Entry's url.
   */
  public function addUrl($url) {
    $this->root->setAttribute('xml:base', $url);
    $this->addLink('alternate', $url, 'text/html');
  }
  /**
   * Adds categories to the entry.
   * 
   * @param string $term
   *   The name of the category.
   *   
   * @param string $scheme
   *   The category scheme.
   */
  public function addCategory($term, $scheme) {
    $this->addNode($this->root, 'category', '', array('term' => $term, 'scheme' => $scheme));
  }
  /**
   * Adds authors to the entry.
   * 
   * @param array $authlist
   *   A list of contributors.
   */
  public function addAuthors($authlist) {
    if (!$authlist) {
      $authlist = array('');
    }
    foreach ($authlist as $author) {
      $auth_element = $this->addNode($this->root, 'author');
      $this->addNode($auth_element, 'name', $author);
    }
  }
  /**
   * Adds content to the entry.
   * 
   * @param string $body
   *   Main content.
   * 
   * @param string $type
   *   An entry type.
   */
  public function addContent($body, $type = 'html') {
    $this->addNode($this->root, 'content', $body, array('type' => $type));
  }
}
