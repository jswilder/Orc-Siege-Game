#ifndef __ACTOR__
#define __ACTOR__

#include "cocos2d.h"
#include "mySprite.h"

class Actor : public mySprite {
public:
  Actor();
  void update(float);
  void setLeft();
  void setRight();
  void setUp();
  void setDown();
  void setStop(bool);
  void setDead();
  void setWin();
  bool decrementHealth();
  int getHealth();
private:
  const int DW;
  int health;
  bool left, right, up, down, stop;
};
#endif
