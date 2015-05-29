#include "HelloWorldScene.h"

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
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//    auto b = Sprite::create("ball.jpg");
//    b->setPosition(200, 200);
//    addChild(b);
    
//    b->runAction(RepeatForever::create(MoveBy::create(1, Vec2(100, 0))));
    
    ball = Sprite::create("ball.jpg");
    addChild(ball);
    ball->setPosition(200, 200);
    
    scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt){
    ball->setPositionX(ball->getPositionX() + 5);
    
    if (ball->getPositionX() > visibleSize.width) {
        ball->setPositionX(0);
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
