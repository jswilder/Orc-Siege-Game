#ifndef __FINALGAME__
#define __FINALGAME__

#include <sstream>
#include "cocos2d.h"
#include "Arrow.h"
#include "KillerArrow.h"
#include "CollectingArrow.h"
#include "GameScene.h"
#include "Actor.h"
#include "background.h"

class FinalGame : public cocos2d::Layer
{
public:
  FinalGame();
  ~FinalGame();
  static cocos2d::Scene* createScene();
  virtual bool init();
  void update(float);
  void endGame(bool);

  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);

  CREATE_FUNC(FinalGame);

private:
  float moveTime;
  float dx, dy;
  bool gameOver;
  int arrowsCollected;
  Background* background;
  Background* river;
  Background* foreground;
  mySprite* actor;
  cocos2d::Label* title;
  cocos2d::Label* scoreBoard;
  cocos2d::Label* health;

  std::list<mySprite*> mySprites;
  cocos2d::Size visibleSize;
  cocos2d::Point origin;

  void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
  void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
};

#endif
