#ifndef __BACKGROUND__
#define __BACKGROUND__

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "cocos2d.h"

class Background : public cocos2d::Layer {
public:
  Background();
  void update(float dt);
  virtual bool init(const std::string&);
  void setScrollSpeed( int s ){ scrollSpeed = s; }
  void setXStationary();
  static Background* create(const std::string&);

  void setBackgroundFile(const std::string& bf) { backFile = bf; }

private:
  cocos2d::Vec2 origin;
  cocos2d::Size viewSize;
  std::string backFile;

  cocos2d::Sprite* bg1;
  cocos2d::Sprite* bg2;

  int scrollSpeed = 1;
};

#endif
