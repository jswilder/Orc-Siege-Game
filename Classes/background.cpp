#include "background.h"

Background::Background() :
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() )
{ }

Background* Background::create(const std::string& filename) {
    Background *backLayer = new Background();
    if (backLayer && backLayer->init(filename)) {
        backLayer->autorelease();
        return backLayer;
    }
    CC_SAFE_DELETE(backLayer);
    return NULL;
}

void Background::setXStationary(){
  bg1->setPosition( viewSize.width/2-4, viewSize.height/2 );
  bg2->setPosition( viewSize.width/2-4, viewSize.height/2 );
}

bool Background::init(const std::string& filename) {

  if ( !Layer::init() ) return false;

  setBackgroundFile( filename );

  bg1 = cocos2d::Sprite::create(backFile);
  bg1->setPosition(0, viewSize.height/2);

  bg2 = cocos2d::Sprite::create(backFile);
  bg2->setPosition(bg1->getContentSize().width - 1,viewSize.height/2);
  addChild(bg1);
  addChild(bg2);

  return true;
}

void Background::update(float dt) {
  bg1->setPositionX(bg1->getPositionX()-scrollSpeed);
  bg2->setPositionX(bg2->getPositionX()-scrollSpeed);

  if (bg1->getPositionX() < -bg1->getContentSize().width/2) {
    bg1->setPositionX( bg2->getPositionX() + bg2->getContentSize().width);
  }
  if (bg2->getPositionX() < -bg2->getContentSize().width/2) {
    bg2->setPositionX(bg1->getPositionX() + bg1->getContentSize().width);
  }
}
