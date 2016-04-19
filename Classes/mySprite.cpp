#include <iostream>
#include <cmath>
#include "mySprite.h"

                  // velocity x & y,  file name , 1 if plist/0 if not, num of frames
mySprite::mySprite(const int vx, const int vy, const std::string file, bool pl, int fnum) :
  velocity(vx,vy),
  viewSize( cocos2d::Director::getInstance()->getVisibleSize() ),
  origin( cocos2d::Director::getInstance()->getVisibleOrigin() ),
  speedScaled(false)
{
  if(pl){
        // Add all frames the cache for later use
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( (file+"right.plist").c_str() );
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( (file+"left.plist").c_str() );
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( (file+"up.plist").c_str() );
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( (file+"down.plist").c_str() );
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( (file+"stand.plist").c_str() );
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( (file+"die.plist").c_str() );

    cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames( (file + "stand%1d.png").c_str() , fnum);
    sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
    float newX = viewSize.width/2 + origin.x;
    float newY = viewSize.height/2 + origin.y;
    sprite->setPosition( cocos2d::Point(newX, newY) );

    cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/5);
    sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));

  }else{
    sprite = cocos2d::Sprite::create(file);
    float newX = viewSize.width/2 + origin.x;
    float newY = viewSize.height/2 + origin.y;
    sprite->setPosition( cocos2d::Point(newX, newY) );
  }
  mySpriteWidth = sprite->getContentSize().width;
}

float getVelocity() {
  float x = rand() % 5 + 1;
  x = (rand()%2?-1:1)*x;
  return x;
}

cocos2d::Rect mySprite::getIntersection(const cocos2d::Rect &r1, const cocos2d::Rect &r2) const {
	float tempX;
	float tempY;
	float tempWidth;
	float tempHeight;

	if (r1.getMaxX() > r2.getMinX()) {
		tempX = r2.getMinX();
		tempWidth = r1.getMaxX() - r2.getMinX();
	} else {
		tempX = r1.getMinX();
		tempWidth = r2.getMaxX() - r1.getMinX();
	}
	if (r2.getMaxY() < r1.getMaxY()) {
		tempY = r1.getMinY();
		tempHeight = r2.getMaxY() - r1.getMinY();
	} else {
		tempY = r2.getMinY();
		tempHeight = r1.getMaxY() - r2.getMinY();
	}

	return cocos2d::Rect( tempX * CC_CONTENT_SCALE_FACTOR(), tempY * CC_CONTENT_SCALE_FACTOR(),
		tempWidth * CC_CONTENT_SCALE_FACTOR(), tempHeight * CC_CONTENT_SCALE_FACTOR() );
}

bool mySprite::collidedPix(cocos2d::Sprite *sprite1) {
  cocos2d::Sprite* orc = getSprite();
  cocos2d::Rect r1 = sprite1->getBoundingBox();
  cocos2d::Rect r2 = orc->getBoundingBox();

  cocos2d::Rect intersection = this->getIntersection(r1, r2);
  unsigned int numPixels = intersection.size.width * intersection.size.height;

  if (numPixels > 5 ) return true;

  /*else*/ return false;
}



bool mySprite::collidedRect(const mySprite* otherSprite){
  int myWidth = sprite->getContentSize().width;
  int myHeight = sprite->getContentSize().height;
  int oWidth = otherSprite->getSprite()->getContentSize().width;
  int oHeight = otherSprite->getSprite()->getContentSize().height;

  cocos2d::Point myPos = sprite->getPosition();
  cocos2d::Point oPos  = otherSprite->getSprite()->getPosition();

  if ( myPos.x+myWidth/2 < oPos.x-oWidth/2 ) return false;
  if ( myPos.x-myWidth/2 > oPos.x+oWidth/2 ) return false;
  if ( myPos.y-myHeight/2 > oPos.y+oHeight/2 ) return false;
  if ( myPos.y+myHeight/2 < oPos.y-oHeight/2 ) return false;
  return true;
}

cocos2d::Vector<cocos2d::SpriteFrame*> mySprite::getFrames(const char *format, int count) {
  cocos2d::SpriteFrameCache*
  spritecache = cocos2d::SpriteFrameCache::getInstance();
  cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
  char str[100];
  for(int i = 1; i <= count; i++) {
    sprintf(str, format, i);
    animFrames.pushBack(spritecache->getSpriteFrameByName(str));
  }
  return animFrames;
}

void mySprite::setVel(int x, int y){
  velocity.x = x;
  velocity.y = y;
}

void mySprite::Scale(float val){
    // Scales Image size
  sprite->setScale(val);
    // Scales velocity
  if(val > 1.6){
    if( !speedScaled ){
      speedScaled = true;
      velocity.x = static_cast<int>(velocity.x * (val*.7));
      velocity.y = static_cast<int>(velocity.y * (val*.7));
    }
  }
  else{
    if(!speedScaled){
      speedScaled = true;
      velocity.x = static_cast<int>(velocity.x * val);
      velocity.y = static_cast<int>(velocity.y * val);
    }
  }
}

void mySprite::runAnimRight(){
  cocos2d::Point position = sprite->getPosition();
  cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames("orcright%1d.png", 9);
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/9);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  sprite->setPosition( cocos2d::Point(position.x, position.y) );
}

void mySprite::runAnimLeft(){
  cocos2d::Point position = sprite->getPosition();
  cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames("orcleft%1d.png", 9);
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/9);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  sprite->setPosition( cocos2d::Point(position.x, position.y) );
}

void mySprite::runAnimUp(){
  cocos2d::Point position = sprite->getPosition();
  cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames("orcup%1d.png", 9);
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/9);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  sprite->setPosition( cocos2d::Point(position.x, position.y) );
}

void mySprite::runAnimDown(){
  cocos2d::Point position = sprite->getPosition();
  cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames("orcdown%1d.png", 9);
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/9);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  sprite->setPosition( cocos2d::Point(position.x, position.y) );
}

void mySprite::runAnimIdle(){
  cocos2d::Point position = sprite->getPosition();
  cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames("orcstand%1d.png", 5);
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/5);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  sprite->setPosition( cocos2d::Point(position.x, position.y) );
}

void mySprite::runAnimDeath(){
  cocos2d::Point position = sprite->getPosition();
  cocos2d::Vector<cocos2d::SpriteFrame*>frames = getFrames("orcdie%1d.png", 6);
  sprite = cocos2d::Sprite::createWithSpriteFrame(frames.front());
  cocos2d::Animation*animation = cocos2d::Animation::createWithSpriteFrames(frames, 1.0f/6);
  sprite->runAction(cocos2d::RepeatForever::create(cocos2d::Animate::create(animation)));
  sprite->setPosition( cocos2d::Point(position.x, position.y) );
}
