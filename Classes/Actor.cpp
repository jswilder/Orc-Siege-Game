#include <iostream>
#include <cmath>
#include "Actor.h"

  // Bounds of the play area
const int PLAYTOP = 400;
const int PLAYBOT = 180;
const int PLAYRIGHT = 1024;
const int PLAYLEFT = 0;

const int HEALTH = 10;  // # of Health Points actor has
const int SPEED = 175;  // Actor's max movement speed in any direction

Actor::Actor() : mySprite(0,0,"orc", 1, 5), DW(getSpriteWidth()/2), health(HEALTH),
  left(false), right(false), up(false), down(false), stop(true){
  cocos2d::Sprite* sprite = getSprite();
  int sx = PLAYRIGHT/2;
  int sy = ( PLAYTOP-((PLAYTOP-PLAYBOT)/2) );
  sprite->setPosition(sx,sy);
}

void Actor::update(float dt) {

  if( !stop ){
    cocos2d::Sprite* sprite = getSprite();
    cocos2d::Point position = sprite->getPosition();

    cocos2d::Vec2 incr = getVel() * dt;
    sprite->setPosition(position.x + incr.x, position.y + incr.y );

    cocos2d::Point location = sprite->getPosition();

  // Check bounds
    if( location.x < PLAYLEFT ){
      setStop(false);
      sprite->setPosition( location.x+5, location.y );
    } else if ( location.x > PLAYRIGHT ){
      setStop(false);
      sprite->setPosition( location.x-5, location.y );
    } else if ( location.y < PLAYBOT ){
      setStop(false);
      sprite->setPosition( location.x, location.y+5 );
    } else if ( location.y > PLAYTOP ){
      setStop(false);
      sprite->setPosition( location.x, location.y-5 );
    } else {
      // Do nothing
    }

  } else {
    setVel( 0,0 );
  }
}

bool Actor::decrementHealth(){
  health -= 1;
  std::cout << health << std::endl;
  if(health <= 0){
    std::cout << "Actor died" << std::endl;
    return true;
  } else {
    return false;
  }
}

int Actor::getHealth(){
  return health;
}

void Actor::setLeft(){
  if( !left ){
    if( up ){
      setStop(false);
      runAnimLeft();
      stop = false;
      up = true;
      left = true;
      setVel( SPEED*(-1) , SPEED );
    } else if ( down ){
      setStop(false);
      runAnimLeft();
      stop = false;
      down = true;
      left = true;
      setVel( SPEED*(-1) , SPEED*(-1) );
    } else {
      setStop(false);
      runAnimLeft();
      stop = false;
      left = true;
      setVel( SPEED*(-1) , 0 );
    }
  }
}

void Actor::setRight(){
  if( !right ){
    if( up ){
      setStop(false);
      runAnimRight();
      stop = false;
      right = true;
      up = true;
      setVel( SPEED , SPEED );
    } else if ( down ){
      setStop(false);
      runAnimRight();
      stop = false;
      down = true;
      right = true;
      setVel( SPEED , SPEED*(-1) );
    } else {
      setStop(false);
      runAnimRight();
      right = true;
      stop = false;
      setVel( SPEED, 0 );
    }
  }
}

void Actor::setUp(){
  if( !up ){
    if( left ){
      setStop(false);
      runAnimUp();
      stop = false;
      up = true;
      left = true;
      setVel( SPEED*(-1) , SPEED );
    } else if ( right ){
      setStop(false);
      runAnimUp();
      stop = false;
      up = true;
      right = true;
      setVel( SPEED , SPEED );
    } else {
      setStop(false);
      runAnimUp();
      up = true;
      stop = false;
      setVel( 0, SPEED );
    }
  }
}

void Actor::setDown(){
  if( !down ){
    if( left ){
      setStop(false);
      runAnimDown();
      stop = false;
      down = true;
      left = true;
      setVel( SPEED*(-1) , SPEED );
    } else if ( right ){
      setStop(false);
      runAnimDown();
      stop = false;
      down = true;
      right = true;
      setVel( SPEED*(-1) , SPEED*(-1) );
    } else {
      setStop(false);
      runAnimDown();
      stop = false;
      down = true;
      setVel( 0 , SPEED*(-1) );
    }
  }
}

void Actor::setDead(){
  setStop(false);
  runAnimDeath();
  stop = true;
}

void Actor::setStop(bool anim){
  if( !stop ){
    stop = true;
    left = false;
    right = false;
    up = false;
    down = false;
    setVel( 0, 0 );
    if( anim ){
      runAnimIdle();
    }
  }
}
