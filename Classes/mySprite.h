#ifndef __MYSPRITE__
#define __MYSPRITE__

#include "cocos2d.h"
#include <cstring>
#include <cmath>
#include <iostream>
#include <ctime>

class mySprite {
public:
  mySprite(const int, const int, const std::string, bool, int);
    // Getter
  cocos2d::Vec2& getVel() {return velocity; }
  cocos2d::Size getViewSize() const { return viewSize; }
  cocos2d::Sprite* getSprite() const { return sprite; }
  int getSpriteWidth() const { return mySpriteWidth; }
  void setVel( int x, int y);

  void Scale(float val);

  virtual void update(float) = 0;

    // Collision
  bool collidedRect(const mySprite*);
  cocos2d::Rect getIntersection(const cocos2d::Rect &r1, const cocos2d::Rect &r2) const;
  bool collidedPix(cocos2d::Sprite *sprite1);

    // Animation
  void runAnimRight();
  void runAnimLeft();
  void runAnimUp();
  void runAnimDown();
  void runAnimIdle();
  void runAnimDeath();

  cocos2d::Vector<cocos2d::SpriteFrame*> getFrames(const char *, int);

private:
  cocos2d::Vec2 velocity;
  cocos2d::Size viewSize;
  cocos2d::Point origin;
  cocos2d::Sprite* sprite;

  cocos2d::Vector<cocos2d::SpriteFrame*>frames;
  int mySpriteWidth;
  bool speedScaled;
};

#endif
