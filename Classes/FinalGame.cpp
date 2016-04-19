// Jeremy Wilder
// Omar Mayar

#include "FinalGame.h"
#include "SimpleAudioEngine.h"
#include <sstream>
#include <list>

const int ARROWNUM = 40;  // # of arrows that spawn in game, use multiple of 4
const int WINVAL = 20;    // # of arrows collected needed to win the game
int OLDARROWS = 0;
int OLDHEALTH = 10;

FinalGame::FinalGame() :
  mySprites(),
  moveTime(0.1),
  dx(5),
  dy(5),
  gameOver(false),
  arrowsCollected(0)
{ }

FinalGame::~FinalGame(){
  removeChild( actor->getSprite() );
  std::list<mySprite*>::iterator it = mySprites.begin();
  while( it != mySprites.end()){
    removeChild( (*it)->getSprite() );
    it = mySprites.erase(it);
  }
}

void FinalGame::update(float dt) {
  if(!gameOver){
    background->update(dt);
    river->update(dt);
    foreground->update(dt);
    actor->update(dt);

          // Update all sprites other than the actor
    for(std::list<mySprite*>::iterator it=mySprites.begin(); it!=mySprites.end(); ++it)
      (*it)->update(dt);


    unsigned int i(0); // Counter used to check specific portion of sprite list
    std::list<mySprite*>::iterator ptr = mySprites.begin();
    while ( ptr != mySprites.end() ){
      if( i < 4*((mySprites.size())/5) && i > ((mySprites.size())/5) ){
        if( (actor)->collidedRect(*ptr) ) {
          if( actor->collidedPix((*ptr)->getSprite()) ){
            dynamic_cast<Arrow*>(*ptr)->resetArrow();
            if( dynamic_cast<KillerArrow*>(*ptr) ){     // Lose
              if( static_cast<Actor*>(actor)->decrementHealth() ){
                endGame(true);
              }
            }
            if( dynamic_cast<CollectingArrow*>(*ptr) ){ // Win
              arrowsCollected++;
              if( arrowsCollected >= WINVAL ){
                endGame(true);
              }
            }
          }
        }
      }
      ++ptr;
      ++i;
      }
      if( arrowsCollected > OLDARROWS ){
        std::stringstream s;
        s<<arrowsCollected;
        scoreBoard->setString("SCR " + s.str());
        OLDARROWS = arrowsCollected;
      }
      if( OLDHEALTH > static_cast<Actor*>(actor)->getHealth() ){
        OLDHEALTH = static_cast<Actor*>(actor)->getHealth();
        std::stringstream s2;
        s2<<OLDHEALTH;
        health->setString("HP " + s2.str());
    }
  }
}

void FinalGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event){
  if( !gameOver ){
    switch ( code ) {
      case cocos2d::EventKeyboard::KeyCode::KEY_A:
      case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        (actor->getSprite())->retain();
        removeChild( actor->getSprite() );
        dynamic_cast<Actor*>(actor)->setLeft();
        addChild( actor->getSprite() );
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_D:
      case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        (actor->getSprite())->retain();
        removeChild( actor->getSprite() );
        dynamic_cast<Actor*>(actor)->setRight();
        addChild( actor->getSprite() );
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_W:
      case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        (actor->getSprite())->retain();
        removeChild( actor->getSprite() );
        dynamic_cast<Actor*>(actor)->setUp();
        addChild( actor->getSprite() );
        break;
      case cocos2d::EventKeyboard::KeyCode::KEY_S:
      case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        (actor->getSprite())->retain();
        removeChild( actor->getSprite() );
        dynamic_cast<Actor*>(actor)->setDown();
        addChild( actor->getSprite() );
        break;
      default:
        // Don't do anything
        break;
    }
  }
}

void FinalGame::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event){
  if( !gameOver ){
    (actor->getSprite())->retain();
    removeChild( actor->getSprite() );
    dynamic_cast<Actor*>(actor)->setStop(true);
    addChild( actor->getSprite() );
  }
}

cocos2d::Scene* FinalGame::createScene() {
  cocos2d::Scene* scene = cocos2d::Scene::create();
  cocos2d::Layer* layer = FinalGame::create();
  scene->addChild(layer);
  return scene;
}

bool FinalGame::init() {
  if ( !Layer::init() ) {
    return false;
  }
  /*
    Background Creation
  */
  background = Background::create("mountains.png");
  addChild(background, -2);
  background->setScrollSpeed(0);
  background->setXStationary();

  river = Background::create("river.png");
  addChild(river, -1);
  river->setScrollSpeed(2);

  foreground = Background::create("testground.png");
  addChild(foreground, 0);
  foreground->setScrollSpeed(0);
  foreground->setXStationary();

  cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
  cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

  cocos2d::MenuItemImage* closeItem = cocos2d::MenuItemImage::create(
                      "x.png",
                      "xclose.png",
                      CC_CALLBACK_1(FinalGame::menuCloseCallback, this));

	closeItem->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width ,
         origin.y + closeItem->getContentSize().height)
  );

  cocos2d::Menu* menu = cocos2d::Menu::create(closeItem, NULL);
  menu->setPosition(cocos2d::Vec2::ZERO);
  this->addChild(menu, 1);
  /*
    Title & ScoreBoard & Health
  */
  title = cocos2d::Label::createWithTTF("ORC SIEGE", "fonts/OrchideeLight.ttf", 60);

  title->setPosition(
    cocos2d::Vec2(origin.x + visibleSize.width/2,
         origin.y + visibleSize.height - title->getContentSize().height)
  );
      // R ,G, B, Aplha
  title->setTextColor(cocos2d::Color4B::WHITE);
  addChild(title, 3);

  scoreBoard = cocos2d::Label::createWithTTF("SCR 0", "fonts/Rosemary Roman.ttf", 50);
  scoreBoard->setPosition(
    cocos2d::Vec2(origin.x + 4*(visibleSize.width/5),
         origin.y + visibleSize.height - scoreBoard->getContentSize().height));
  scoreBoard->setTextColor( cocos2d::Color4B::RED );
  addChild( scoreBoard, 3 );

  health = cocos2d::Label::createWithTTF("HP 10", "fonts/Rosemary Roman.ttf", 50);
  health->setPosition(
    cocos2d::Vec2(origin.x + (visibleSize.width/5),
         origin.y + visibleSize.height - health->getContentSize().height));
  health->setTextColor( cocos2d::Color4B::RED );
  addChild( health, 3 );

  /*
    Keyboard Input
  */
  cocos2d::EventListenerKeyboard * listener = cocos2d::EventListenerKeyboard::create();
  listener->onKeyPressed = CC_CALLBACK_2( FinalGame::onKeyPressed, this );
  listener->onKeyReleased = CC_CALLBACK_2( FinalGame::onKeyReleased, this );

  cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
  /*
    Sprite creation
  */
  actor = new Actor();

    // Creates 3 different sizes/speeds of drop sprite
  for( int i(0); i<ARROWNUM; i++){
    mySprite* da;
    if( i < ARROWNUM/5){
      da = new Arrow();
      da->Scale(.8);
    } else if( i < 2*(ARROWNUM/5) ){
      da = new CollectingArrow();
    } else if( i < 4*(ARROWNUM/5) ){
      da = new KillerArrow();
    } else{
      da = new Arrow();
      da->Scale(1.5);
    }
    mySprites.push_back( da );
  }

    // Add the different drops to the appropriate layer
      // The "actor" is on layer 0
  unsigned int i = 0;
  addChild( actor->getSprite(), 0 );
  for(std::list<mySprite*>::iterator it=mySprites.begin(); it!=mySprites.end(); ++it){
    if( static_cast<float>(i-1) < (mySprites.size()-1)/5){
      addChild( (*it)->getSprite(), -2 );
      i++;  // No need to keep incremeting after this point...
    }
    else if( dynamic_cast<KillerArrow*>(*it) || dynamic_cast<CollectingArrow*>(*it) )
      addChild( (*it)->getSprite(), 0 );
    else
      addChild( (*it)->getSprite(), 1 );
  }

  schedule( schedule_selector(FinalGame::update));

//  Music
/*
  CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::
      getInstance();
  audio->playBackgroundMusic("audio/MachinimaSound.com_-_The_End_of_Mankind.mp3", true);
*/
  return true;
}

void FinalGame::endGame(bool b){
  if( b ){
    (actor->getSprite())->retain();
    removeChild( actor->getSprite() );
    dynamic_cast<Actor*>(actor)->setStop(true);
    addChild( actor->getSprite() );
  } else {
    (actor->getSprite())->retain();
    removeChild( actor->getSprite() );
    dynamic_cast<Actor*>(actor)->setDead();
    addChild( actor->getSprite() );
  }
  gameOver = true;
}

void FinalGame::menuCloseCallback(Ref* pSender) {
  cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif
}
