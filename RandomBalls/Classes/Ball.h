//
//  Ball.h
//  RandomBalls
//
//  Created by 李正宁 on 5/28/15.
//
//

#ifndef __RandomBalls__Ball__
#define __RandomBalls__Ball__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class Ball:public Sprite {

public:
    virtual bool init();
    virtual void update(float dt);
    CREATE_FUNC(Ball);
    
private:
    float speedX,speedY;
};

#endif /* defined(__RandomBalls__Ball__) */
