#include "HelloWorldScene.h"
#include "Ball.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    float speedX;
    float speedY;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
  
    for (int i = 0; i < 30; i++) {
        speedX = CCRANDOM_0_1()*10 - 5;
        speedY = CCRANDOM_0_1()*10 - 5;

        auto b = Sprite::create("ball.jpg");
        b->setPosition(CCRANDOM_0_1() * 200 + 100, CCRANDOM_0_1() * 200 + 100);
        addChild(b);
        setPosition(getPositionX() + speedX, getPositionY() + speedY);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
