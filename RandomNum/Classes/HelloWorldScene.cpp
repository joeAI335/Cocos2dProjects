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
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    return true;
}

void HelloWorld::buildUI()
{
    auto label = Label::create();
    label->setString("Please input a number between 0 - 100");
    addChild(label);
    label->setPosition(visibleSize.width / 2, visibleSize.height - label->getContentSize().height / 2 - 20);
    
    auto tf = TextFieldTTF::textFieldWithPlaceHolder("Input number here", "Courier", 16);
    
    tf->setPosition(visibleSize.width / 2, label->getPositionY() - 50);
    
    addChild(tf);
    
    auto submitBtn = Label::create();
    submitBtn->setPosition(visibleSize.width / 2, tf->getPositionY() - 50);
    submitBtn->setString("Submit");
    addChild(submitBtn);

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
