#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include "cocos2d.h"
#include "FinalGame.h"
#include "background.h"

class GameScene : public cocos2d::Layer
{
public:
  GameScene() {};
  ~GameScene() {};
  static cocos2d::Scene* createScene();
  virtual bool init();
  void GoToGameScene(cocos2d::Ref* sender);

  CREATE_FUNC(GameScene);

private:
	Background* bg;
	cocos2d::Label* title;
	cocos2d::Label* instr;
	cocos2d::MenuItemImage* playItem;
};

#endif // __GAMESCENE_H__