#ifndef __ARROW__
#define __ARROW__

#include "cocos2d.h"
#include "mySprite.h"

class Arrow : public mySprite {
public:
  Arrow();
  Arrow(bool);
  Arrow(int);
  void update(float);
  void resetArrow();
  int returnRandom();
private:
  const int DW;
};
#endif
