//
//  MoveBalls.h
//  MoveBall
//
//  Created by 李正宁 on 5/27/15.
//
//

#ifndef __MoveBall__MoveBalls__
#define __MoveBall__MoveBalls__

#include <stdio.h>
#include "cocos2d.h"
#include "Ball.h"

USING_NS_CC;

class MoveBalls :public LayerColor {

public:
    virtual bool init();
    CREATE_FUNC(MoveBalls);
    
    virtual void update(float dt);
    static Scene * createScene();

private:
//    Ball * ball;
    cocos2d::Vector<Ball*> balls;
    
    void addBall(float x, float y);
};

#endif /* defined(__MoveBall__MoveBalls__) */
