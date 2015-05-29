//
//  Ball.cpp
//  MoveBall
//
//  Created by 李正宁 on 5/27/15.
//
//

#include "Ball.h"

bool Ball::init() {
    
    Sprite::initWithFile("ball.jpg");
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    speedX = 3;
    
    return true;
}

void Ball::move(){
    setPositionX(getPositionX() + speedX);
    
    if (getPositionX() > visibleSize.width) {
        setPositionX(0);
    }
}