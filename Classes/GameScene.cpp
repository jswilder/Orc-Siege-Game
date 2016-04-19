#include "GameScene.h"
#include "SimpleAudioEngine.h"

cocos2d::Scene* GameScene::createScene()
{
  cocos2d::Scene *scene = cocos2d::Scene::create();
  cocos2d::Layer *layer = GameScene::create();
  scene->addChild(layer);

  return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init() {
  if ( !Layer::init() ){
  return false;
  }

  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  title = cocos2d::Label::createWithTTF("ORC SIEGE", "fonts/OrchideeLight.ttf", 50);

  title->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
         origin.y + visibleSize.height - title->getContentSize().height)
  );

  title->setTextColor(cocos2d::Color4B::WHITE);
  addChild(title, 3);

  bg = Background::create("bgorc.png");
  addChild(bg, 0);

  playItem = cocos2d::MenuItemImage::create("start0.png", "start1.png",
                                  CC_CALLBACK_1(GameScene::GoToGameScene, this) );
  playItem->setPosition(cocos2d::Point(visibleSize.width/2 + origin.x,
                                       visibleSize.height/2 + origin.y) );

  cocos2d::Menu *play = cocos2d::Menu::create(playItem, NULL);
  play->setPosition( cocos2d::Point::ZERO );
  this->addChild(play);

  instr = cocos2d::Label::createWithTTF(
          "Use arrow or WASD keys to move\nGet twenty silver arrows to win",
          "fonts/OrchideeLight.ttf", 30);

  instr->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
                  origin.y + title->getContentSize().height)
  );

  instr->setTextColor(cocos2d::Color4B::WHITE);
  addChild(instr, 3);

  return true;
}

void GameScene::GoToGameScene( cocos2d::Ref *sender )
{
  cocos2d::Scene *scene = FinalGame::createScene();
  cocos2d::Director::getInstance()->replaceScene(
                     cocos2d::TransitionFade::create(0.5, scene) );
}
