/**
 * Events:
 * - penton:gallery:slideshow:prev
 * - penton:gallery:slideshow:after:prev
 * - penton:gallery:slideshow:next
 * - penton:gallery:slideshow:after:next
 * - penton:gallery:slideshow:show
 * - penton:gallery:slideshow:hide
 * - penton:gallery:slideshow:goto
 */
(function($, doc, win) {
  'use script';

  var PentonSlideshow = (function() {
    function PentonSlideshow(el, selector) {
      this.selector = $.extend({
        displayTitle: '.js-penton-slideshow-display-title',
        displayCaption: '.js-penton-slideshow-display-caption',
        items: '.js-penton-slideshow-items',
        item: '.js-penton-slideshow-item',
        current: '.js-penton-slideshow-current',
        next: '.js-penton-slideshow-next',
        thumbItems: '.js-penton-slideshow-navbar-items',
        currSlideNubmer: '.js-penton-slideshow-navbar-current-slide',
        captionScrollTop: '.gallery-shadow.gallery-top',
        captionScrollBot: '.gallery-shadow.gallery-bottom',
        numberNav: '.gallery-slide-number'
      }, selector);

      this.elements = {};
      this.slides = [];
      this.count = 0;
      this.counter = 0;
      this.isActiveSlider = true;
      this.animateTime = 400;
      this.hashSlideParam = 'slide';

      this.el = el;
      this.initElements();
      this.thumbCl = {};
      this.linkEl = null;
      this.adsShowCb = function() {};
      this.adsHideCb = function() {};
      this.isShowAd = false;
      this.hideAdsStatus = false;
      this.isHistory = false;
      this.vector = true;
      this.regslide = new RegExp(/slide=\d*/i);

      this.initSlides();
      this.initThumbs();

      this.initHistory();

      this.goto(this.getHashSlide());
    }

    PentonSlideshow.prototype.initHistory = function(n) {
      if(typeof history.pushState === 'function') {
        this.isHistory = true;
      }
    };
    PentonSlideshow.prototype.setHashSlide = function(n) {
      var currSlide;

      if(n > -1 && n < this.slides.length && this.isHistory) {
        var path = location.protocol + '//' + location.hostname + location.pathname;
        currSlide = this.regslide.exec(location.search);

        if(currSlide !== null) {
          path += location.search.replace(currSlide.join(''), this.hashSlideParam + '=' + (n + 1));
        } else {
          var sep = (location.search.indexOf('?') !== -1) ? '&' : '?';
          path += location.search + sep + this.hashSlideParam + '=' + (n + 1);
        }

        history.pushState({slide: n + 1}, this.slides[n].elements.title.text(), path);
      } else if(n > -1 && n < this.slides.length) {
        location.hash = '#' + this.hashSlideParam + '=' + (n + 1);
      }
    };
    PentonSlideshow.prototype.getHashSlide = function() {
      var currSlide = this.regslide.exec(location.search),
        path = (currSlide !== null) ? parseInt(currSlide.join('').replace(this.hashSlideParam + '=', ''), 10) : 0;

      if(this.isHistory && path) {
        return path - 1;
      } else if(location.hash.indexOf(this.hashSlideParam) !== -1) {
        currSlide = this.regslide.exec(location.hash);
        return (currSlide !== null) ? parseInt(currSlide.join('').replace(this.hashSlideParam + '=', ''), 10) : 0;
      }

      return 0;
    };
    PentonSlideshow.prototype.showAds = function() {
      $('.js-penton-slideshow-wrapper').addClass('min-gallery-height-with-ad');
      this.adsShowCb();
      this.isShowAd = false;
      this.hideAdsStatus = true;
    };
    PentonSlideshow.prototype.hideAds = function() {
      $('.js-penton-slideshow-wrapper').removeClass('min-gallery-height-with-ad');
      this.adsHideCb();
      this.hideAdsStatus = false;
    };
    PentonSlideshow.prototype.setAdsShowCb = function(cb) {
      this.adsShowCb = cb;
    };
    PentonSlideshow.prototype.setAdsHideCb = function(cb) {
      this.adsHideCb = cb;
    };
    PentonSlideshow.prototype.resetScroll = function() {
      this.elements.captionScrollTop.removeClass('gallery-hide').addClass('gallery-hide');
      this.elements.captionScrollBot.removeClass('gallery-hide');
    };
    PentonSlideshow.prototype.getCount = function() {
      return this.count;
    };
    PentonSlideshow.prototype.setNextLink = function(link) {
      this.linkEl = link;

      return this;
    };
    PentonSlideshow.prototype.triggerNextLink = function() {
      location.href = this.linkEl.attr('href');

      return this;
    };
    PentonSlideshow.prototype.initSlides = function() {
      var self = this;

      this.elements.items.find(this.selector.item).each(function() {
        var slide = new PentonSlide($(this));
        self.slides.push(slide);
      });
    };
    PentonSlideshow.prototype.initElements = function() {
      this.elements.items = this.el.find(this.selector.items);
      this.elements.displayTitle = this.el.find(this.selector.displayTitle);
      this.elements.displayCaption = this.el.find(this.selector.displayCaption);
      this.elements.current = this.el.find(this.selector.current);
      this.elements.next = this.el.find(this.selector.next);
      this.elements.thumbItems = this.el.find(this.selector.thumbItems);
      this.elements.currSlideNubmer = $(this.selector.currSlideNubmer);
      this.elements.captionScrollTop = $(this.selector.captionScrollTop);
      this.elements.captionScrollBot = $(this.selector.captionScrollBot);
      this.elements.numberNav = $(this.selector.numberNav);

    };
    PentonSlideshow.prototype.initThumbs = function() {
      this.thumbCl = new PentonThumbs(this.elements.thumbItems);
    };
    PentonSlideshow.prototype.showSlidshow = function() {
      var self = this;

      this.isActiveSlider = true;
      this.elements.numberNav.stop(true, true).animate({opacity: 1}, this.animateTime);
      this.elements.current.stop(true, true).slideDown(this.animateTime);
      this.elements.next.stop(true, true).slideUp(this.animateTime, function() {
        self.el.trigger('penton:gallery:slideshow:show');
      });
    };
    PentonSlideshow.prototype.showNextSlidshow = function() {
      var self = this;

      this.isActiveSlider = false;
      this.elements.numberNav.stop(true, true).animate({opacity: 0}, this.animateTime);
      this.elements.current.stop(true, true).slideUp(this.animateTime);
      this.elements.next.stop(true, true).slideDown(this.animateTime, function() {
        self.el.trigger('penton:gallery:slideshow:hide');
      });
    };
    PentonSlideshow.prototype.isFullscreen = function() {
      return this.elements.items.hasClass('fullscreen');
    };
    PentonSlideshow.prototype.isVisible = function() {
      return this.isActiveSlider;
    };
    PentonSlideshow.prototype.changeDescriptionSlide = function(n) {
      this.elements.displayTitle.html(this.slides[n].elements.title.html());
      this.elements.displayCaption.html(this.slides[n].elements.caption.html());
    };
    PentonSlideshow.prototype.isLastSlide = function() {
      return this.count + 1 === this.slides.length;
    };
    PentonSlideshow.prototype.countCurrentNumberSlide = function(vector) {
      if(vector) {
        if(this.count - 1 === -1) {
          return this.slides.length - 1;
        } else {
          return this.count;
        }
      }

      return (this.slides.length > this.count + 1) ? this.count + 1 : 0;
    };
    PentonSlideshow.prototype.goto = function(n) {
      this.resetScroll();
      this.slides[this.count].hide();

      if(n < 0) {
        n = 0;
      }
      if(n > this.slides.length - 1) {
        n = this.slides.length - 1;
      }

      this.count = n;
      this.hideAds();
      this.setHashSlide(this.count);
      this.slides[this.count].show();
      this.thumbCl.goto(this.count);
      this.changeDescriptionSlide(this.count);
      this.elements.currSlideNubmer.text(this.count + 1);
      this.el.trigger('penton:gallery:slideshow:goto');
    };
    PentonSlideshow.prototype.prev = function() {
      if(!this.isVisible()) {
        this.showSlidshow();
        return;
      }

      this.counter = this.countCurrentNumberSlide(true);
      this.el.trigger('penton:gallery:slideshow:prev', [this.counter, this]);
      if(this.hideAdsStatus) {
        this.hideAds();
        if(this.vector === true) {
          return;
        }
      }
      if(this.isShowAd) {
        this.showAds();
        this.vector = false;
        return false;
      }
      this.resetScroll();
      this.slides[this.count].hide();

      if(this.count - 1 === -1) {
        this.count = this.slides.length - 1;
      } else {
        this.count--;
      }

      this.thumbCl.goto(this.count);
      this.setHashSlide(this.count);
      this.slides[this.count].show();
      this.changeDescriptionSlide(this.count);

      this.elements.currSlideNubmer.text(this.count + 1);
      this.el.trigger('penton:gallery:slideshow:after:prev');
      this.vector = false;
    };
    PentonSlideshow.prototype.next = function() {
      if(!this.isVisible()) {
        this.triggerNextLink();
        return;
      }

      if(this.isLastSlide()) {
        if(this.elements.next.hasClass('js-isset') || this.isFullscreen()) {
          this.counter = this.countCurrentNumberSlide(false);
          this.el.trigger('penton:gallery:slideshow:next', [this.counter, this]);
          if(this.hideAdsStatus) {
            this.hideAds();
            if(this.vector === false) {
              return;
            }
          }
          if(this.isShowAd) {
            this.showAds();
            this.vector = true;
            return false;
          }
          this.slides[this.count].hide();
          this.count = 0;
        } else {
          this.showNextSlidshow();
          return;
        }
      } else {
        this.counter = this.countCurrentNumberSlide(false);
        this.el.trigger('penton:gallery:slideshow:next', [this.counter, this]);
        if(this.hideAdsStatus) {
          this.hideAds();
          if(this.vector === false) {
            return;
          }
        }
        if(this.isShowAd) {
          this.showAds();
          this.vector = true;
          return false;
        }
        this.slides[this.count].hide();
        this.count++;
      }
      this.resetScroll();
      this.setHashSlide(this.count);
      this.thumbCl.goto(this.count);
      this.slides[this.count].show();
      this.changeDescriptionSlide(this.count);
      this.elements.currSlideNubmer.text(this.count + 1);
      this.el.trigger('penton:gallery:slideshow:after:next');
      this.vector = true;
    };

    return PentonSlideshow;
  } ());

  var PentonSlide = (function() {
    function PentonSlide(el, selector) {
      this.selector = $.extend({
        title: '.js-penton-slideshow-item-title',
        caption: '.js-penton-slideshow-item-caption',
        credit: '.js-penton-slideshow-item-credit',
      }, selector);

      this.el = el;
      this.elements = {};
      this.initElements();
    }
    PentonSlide.prototype.initElements = function() {
      for(var k in this.selector) {
        if(this.selector.hasOwnProperty(k)) {
          this.elements[k] = this.el.find(this.selector[k]);
        }
      }
    };
    PentonSlide.prototype.hide = function() {
      this.el.removeClass('active');
    };
    PentonSlide.prototype.show = function() {
      this.el.addClass('active');
    };


    return PentonSlide;
  } ());

  var PentonThumbs = (function() {
    function PentonThumbs(el, selector) {
      this.selector = $.extend({
        thumbItem: '.js-penton-slideshow-navbar-item',
        navbar: '.js-penton-slideshow-navbar',
        prev: '.js-penton-slideshow-navbar-prev',
        next: '.js-penton-slideshow-navbar-next',
        container: '.js-penton-slideshow-navbar-container'
      }, selector);

      this.elements = {};
      this.current = 0;
      this.currentGroup = 0;
      this.thumbs = [];
      this.widthItem = 0;
      this.maxWidth = 0;
      this.el = el;

      this.initElements();
      this.goto(this.current);
    }

    PentonThumbs.prototype.getWidth = function() {
      return this.elements.container.innerWidth();
    };
    PentonThumbs.prototype.initElements = function() {
      var self = this, items, len, width;

      this.elements.prev = $(this.selector.prev);
      this.elements.next = $(this.selector.next);
      this.elements.container = $(this.selector.container);
      this.elements.navbar = $(this.selector.navbar);

      items = this.el.find(this.selector.thumbItem);
      len = items.length + 1;
      width = items.first().outerWidth(true);
      this.widthItem = width;

      items.each(function() {
        self.thumbs.push($(this));
      });

      this.maxWidth = width * len;
      this.el.css({ 'width': width * len });
    };
    PentonThumbs.prototype.resize = function() {
      this.stateNav();
      this.goto(this.current);
    };
    PentonThumbs.prototype.stateNav = function(n) {
      if(Math.floor(this.getWidth() / this.widthItem) >= this.thumbs.length) {
        this.elements.prev.hide();
        this.elements.next.hide();
        this.elements.container.css({'left': -10, 'right': 0});
        this.elements.navbar.css({'padding-left': 0, 'padding-right': 0});

        return;
      }
      if(n === 0) {
        this.elements.prev.hide();
        this.elements.next.show();
        this.elements.container.css({'left': -10, 'right': 60});
        this.elements.navbar.css({'padding-left': 0, 'padding-right': 60});

        return;
      }
      if(this.currentGroup === Math.ceil(this.thumbs.length / (this.getWidth() / this.widthItem) - 1)) {
        this.elements.next.hide();
        this.elements.prev.show();
        this.elements.container.css({'left': 60, 'right': -10});
        this.elements.navbar.css({'padding-left': 60, 'padding-right': 0});

        return;
      }

      this.elements.prev.show();
      this.elements.next.show();
      this.elements.container.css({'left': 60, 'right': 60});
      this.elements.navbar.css({'padding-left': 60, 'padding-right': 60});
    };
    PentonThumbs.prototype.goto = function(n) {
      if(typeof this.thumbs[this.current] === 'undefined') {
        return;
      }
      this.thumbs[this.current].removeClass('active');
      this.current = n;
      this.thumbs[this.current].addClass('active');

      var countSlideInContainer = Math.floor(this.getWidth() / this.widthItem);
      this.currentGroup = Math.floor(this.current / countSlideInContainer);

      this.stateNav(this.currentGroup);

      this.el.css({
        left: - this.currentGroup * this.widthItem * countSlideInContainer
      });
    };
    PentonThumbs.prototype.prev = function() {
      if(this.currentGroup - 1 > -1) {
        this.currentGroup--;

        this.stateNav(this.currentGroup);

        this.el.css({
          left: - this.currentGroup * this.widthItem * Math.floor(this.getWidth() / this.widthItem)
        });
      }
    };
    PentonThumbs.prototype.next = function() {
      var n = Math.ceil(this.thumbs.length / (this.getWidth() / this.widthItem));

      if(this.currentGroup + 1 < n) {
        this.currentGroup++;

        this.stateNav(this.currentGroup);

        this.el.css({
          left: - (this.currentGroup) * this.widthItem * Math.floor(this.getWidth() / this.widthItem)
        });
      }
    };

    return PentonThumbs;
  } ());

  $(function() {
    var slider, numberSlide, navbar, shadow, bg, container, containerHideWithAds, containerNextAds, singleInitNextAds = true,
      isDefinedAds = false, adsContainer, adsContainerInner, NUMBER_SHOW_ADS = 5, xDown = null;

    function dfpAdsRefrash(e, number, self) {
      $('[data-dfp-position=right_rail_rect] .dfp-tags').DFP({refresh: true});
      self.isShowAd = (number === 0 || self.hideAdsStatus) ? false : !(number % NUMBER_SHOW_ADS);
    }

    function resizeAdsContainer() {
      if(adsContainer && slider) {
        adsContainer.height(slider.elements.items.height());
        adsContainer.width(slider.elements.items.width());
      }
    }

    if($('.gallery-pop-up').length === 0) {
      return;
    }

    containerNextAds = $('.up-next-gallery-adblock');
    containerHideWithAds = $('.js-gallery-hide-with-ads');
    adsContainer = $('.js-penton-slideshow-item-ads');
    adsContainerInner = $('.js-penton-slideshow-item-ads-inner');
    slider = new PentonSlideshow($('#js-penton-slideshow'));
    slider.setNextLink($('.js-penton-slideshow-next-now'));
    bg = $('#bg');
    container = $('.gallery-item-block');
    navbar = $('.js-penton-slideshow-navbar-item');
    shadow = $('.gallery-shadow');
    slider.setAdsShowCb(function() {
      resizeAdsContainer();

      if(!isDefinedAds) {
        var div = $('<div>');
        div.attr({'data-dfp-position': 'interstitial'});
        adsContainerInner.append(div);
        dfp_init_ads_by_context(adsContainer);
        isDefinedAds = true;
      } else {
        $('.dfp-tags', adsContainer).DFP({refresh: true});
      }

      adsContainer.css('display', 'table').addClass('js-penton-slideshow-item-ads__show');

      containerHideWithAds.hide();
    });
    var timerId = null;
    slider.setAdsHideCb(function() {
      if(timerId !== null) {
        clearTimeout(timerId);
      }
      if(adsContainer) {
        adsContainer.css('display', 'table')
          .removeClass('js-penton-slideshow-item-ads__show');

        timerId = setTimeout(function( ){
          adsContainer.css('display', 'none');
        }, slider.animateTime);
      }
      containerHideWithAds.show();
    });
    slider.el.on('penton:gallery:slideshow:prev', dfpAdsRefrash);
    slider.el.on('penton:gallery:slideshow:next', dfpAdsRefrash);
    slider.elements.items.on('swipeleft', function() { slider.next(); })
      .on('swiperight', function() { slider.prev(); });

    slider.thumbCl.elements.navbar.on('swipeleft', function() { slider.thumbCl.next(); })
      .on('swiperight', function() { slider.thumbCl.prev(); });

    slider.el.on('penton:gallery:slideshow:hide', function() {
      if(singleInitNextAds) {
        var div = $('<div>');
        div.attr('data-dfp-position', 'right_rail_rect');
        singleInitNextAds = false;
        containerNextAds.append(div);
        dfp_init_ads_by_context(containerNextAds);
      }

    });

    $('body').css('background-color', $('.gallery-pop-up').css('background-color'));

    $(doc).keydown(function (e) {
      if(e.keyCode === 37) {
        slider.prev();
      }
      if(e.keyCode === 39) {
        slider.next();
      }
    });
    $('.js-penton-slideshow-navbar-prev').on('click', function(e) {
      slider.thumbCl.prev();
      e.preventDefault();
    });
    $('.js-penton-slideshow-navbar-next').on('click', function(e) {
      slider.thumbCl.next();
      e.preventDefault();
    });
    navbar.on('click', function(e) {
      var index = navbar.index($(this));
      slider.goto(index);
      e.preventDefault();
    });
    $('.gallery-backward').on('click', function(e) {
      slider.prev();
      e.preventDefault();
    });
    $('.gallery-forward').on('click', function(e) {
      slider.next();
      e.preventDefault();
    });
    $('.js-penton-slideshow-display').on('scroll', function(e) {
      var top, bot;

      top = $('.gallery-shadow.gallery-top');
      bot = $('.gallery-shadow.gallery-bottom');

      if($(this).scrollTop() + $(this).height() >= $(this).prop('scrollHeight')) {
        bot.addClass('gallery-hide');
      } else {
        bot.removeClass('gallery-hide');
      }

      if($(this).scrollTop() > 0) {
        top.removeClass('gallery-hide');
      } else {
        top.addClass('gallery-hide');
      }
    });
    $('.js-penton-slideshow-next-back').on('click', function() {
      slider.showSlidshow();
    });

    $('.js-penton-slideshow-items .nin-prev, .js-penton-slideshow-items .nin-next').on('click', function(e) {
      if($(this).hasClass('nin-prev')) {
        slider.prev();
      } else {
        slider.next();
      }

      e.preventDefault();
    });

    $(win).on('resize', function() {
      slider.thumbCl.resize();
      resizeAdsContainer();
    });

    function updateUrls() {
      shareIcons.each(function(i, e) {
        var href = getUrl(e);
        if (typeof(href.params.url) !== 'undefined') {
          href.params.url = location.href;
        } else if (typeof(href.params.u) !== 'undefined') {
          href.params.u = location.href;
        } else if (typeof(href.params.bkmk) !== 'undefined') {
          href.params.bkmk = location.href;
        }
        setUrl(e, href);
      });
    }

    function getUrl(e) {
      var href = {};

      var assembled = $(e).attr('href');
      href.url = assembled.split('?')[0];

      href.params = {};
      var params = assembled.split('?').slice(1).join().split('&');
      $.each(params, function(i, e) {
        var param = e.split('=');
        href.params[param[0]] = param[1];
      });

      return href;
    }

    function setUrl(e, urlObj) {
      $(e).attr('href', urlObj.url + '?' + decodeURIComponent($.param(urlObj.params)));
    }

    if (slider) {
      var shareIcons = $('.gallery-info-block .share-icons a:not(.ctools-use-modal):not(.print)');

      updateUrls();

      slider.el.on('penton:gallery:slideshow:after:prev penton:gallery:slideshow:after:next penton:gallery:slideshow:goto', function() {
        var descriptionBar = $('.gallery-pop-up-container .gallery-description');
        if (descriptionBar.length) {
          descriptionBar.scrollTop(0);
        }
        if (typeof(_satellite) !== 'undefined') {
          _satellite.track('GALLERY_SLIDE_ADVANCE');
        }
        updateUrls();
      });
    }

    $(win).on('resize', resizeAdsContainer);
    win.addEventListener("deviceorientation", resizeAdsContainer, true);


    function dfp_init_ads_by_context(context, dataType) {
      if (typeof Drupal.settings.penton_custom_dfp === 'undefined' && typeof $.DFPInit === 'undefined') {
        return;
      }

      var data      = Drupal.settings.penton_custom_dfp
        , type      = data.current_type
        , ads       = (dataType && typeof data.dfp_tags[dataType] !== 'undefined') ? data.dfp_tags[dataType]: data.dfp_tags[type]
        ;

      $(context).DFPrender(ads);
      $('.dfp-tags', context).DFP();
    }
  });
} (jQuery, document, window));
