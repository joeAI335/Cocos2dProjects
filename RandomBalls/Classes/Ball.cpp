//
//  Ball.cpp
//  RandomBalls
//
//  Created by 李正宁 on 5/28/15.
//
//

#include "Ball.h"

bool Ball::init(){
    
    Sprite::initWithFile("ball.jpg");
    
    speedX = CCRANDOM_0_1()*10 - 5;
    speedY = CCRANDOM_0_1()*10 - 5;
    
    scheduleUpdate();
    return true;
}

void Ball::update(float dt) {
    
    setPosition(getPositionX() + speedX, getPositionY() + speedY);
    
}