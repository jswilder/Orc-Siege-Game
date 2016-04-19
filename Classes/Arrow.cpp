#include <iostream>
#include <cmath>
#include "Arrow.h"

const int YSPEED = -200;
const int XSPEED = -200;

bool randomSet = false;

Arrow::Arrow() : mySprite(XSPEED,YSPEED,"arrow.png", 0, 0), DW(getSpriteWidth()/2){
  cocos2d::Sprite* sprite = getSprite();
  int sx = ( returnRandom() % 1010  ) + DW;
  int sy = 200 + (returnRandom() % 568 );
  sprite->setPosition(sx,sy);
}

  // Constructor called by collectingArrow class
Arrow::Arrow(bool b) : mySprite(XSPEED,YSPEED,"collectingarrow.png", 0, 0), DW(getSpriteWidth()/2){
  cocos2d::Sprite* sprite = getSprite();
  int sx = ( returnRandom() % 1010  ) + DW;
  int sy = 200 + (returnRandom() % 568 );
  sprite->setPosition(sx,sy);
}

  // Constructor called by KillerArrow class
Arrow::Arrow(int i) : mySprite(XSPEED,YSPEED,"killerarrow.png", 0, 0), DW(getSpriteWidth()/2){
  cocos2d::Sprite* sprite = getSprite();
  int sx = ( returnRandom() % 1010  ) + DW;
  int sy = 200 + (returnRandom() % 568 );
  sprite->setPosition(sx,sy);
}

void Arrow::update(float dt) {
  cocos2d::Sprite* sprite = getSprite();
  cocos2d::Point position = sprite->getPosition();

  cocos2d::Vec2 incr = getVel() * dt;
  const cocos2d::Size viewSize = getViewSize();
  sprite->setPosition(position.x + incr.x, position.y + incr.y );

  cocos2d::Point location = sprite->getPosition();

    // Arrows always fall to the bottom left,
    // No need to check right wall / roof collisions
  if ( location.x < DW ) {
    sprite->setPosition(viewSize.width-(DW), position.y);
  }
  else if ( location.y < DW ) {
    sprite->setPosition(position.x, viewSize.height-DW);
  }
  else {
    // Nothing to do here
  }
}

  // This will become exlode
void Arrow::resetArrow(){
  cocos2d::Sprite* sprite = getSprite();
  cocos2d::Point position = sprite->getPosition();
  const cocos2d::Size viewSize = getViewSize();
  sprite->setPosition(viewSize.width-(DW), position.y);
  sprite->setPosition(position.x, viewSize.height-DW);
}

int Arrow::returnRandom(){
  if(!randomSet){
    std::srand( time(NULL ));
    randomSet = true;
  }
  return rand();
}
