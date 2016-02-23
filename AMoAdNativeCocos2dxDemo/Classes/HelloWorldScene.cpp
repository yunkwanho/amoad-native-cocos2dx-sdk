#include "HelloWorldScene.h"
#include "AMoAdNativeCocos2dxModule.h"  // [SDK] Cocos2d-xモジュール

USING_NS_CC;

// [SDK] 管理画面から取得したsidを入力してください
#define AD_SID "62056d310111552c000000000000000000000000000000000000000000000000"
#define AD_TAG "Ad01"

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
#if 0
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
#endif

    /////////////////////////////
    // 4. [SDK] 広告

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //  AMoAdNativeCocos2dxModule::load(AD_SID, AD_TAG, 20, 100, 140, 120, "{\"border\": \"dotted 2px #0000ff\"}");
    AMoAdNativeCocos2dxModule::load(AD_SID, AD_TAG, 20, 100, 140, 120);
#else
    //  AMoAdNativeCocos2dxModule::load(AD_SID, AD_TAG, 20, 100, 140, 120, "{\"border\": \"dotted 2px #0000ff\"}");
    AMoAdNativeCocos2dxModule::load(AD_SID, AD_TAG, 20, 100, 140, 120);
#endif

    // メニュー
    auto showLabel = Label::createWithSystemFont("表示", "Arial", 9);
    auto showBtnItem = MenuItemLabel::create(showLabel, [this](Ref *sender){
      AMoAdNativeCocos2dxModule::show(AD_SID, AD_TAG);
    });
    showBtnItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto hideLabel = Label::createWithSystemFont("非表示", "Arial", 9);
    auto hideBtnItem = MenuItemLabel::create(hideLabel, [this](Ref *sender){
      AMoAdNativeCocos2dxModule::hide(AD_SID, AD_TAG);
    });
    hideBtnItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 20));

    auto rotationStartLabel = Label::createWithSystemFont("ローテーション開始(10秒)", "Arial", 9);
    auto rotationStartBtnItem = MenuItemLabel::create(rotationStartLabel, [this](Ref *sender){
      AMoAdNativeCocos2dxModule::startRotation(AD_SID, AD_TAG, 9);
    });
    rotationStartBtnItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 20 - 20));

    auto rotationStopLabel = Label::createWithSystemFont("ローテーション停止", "Arial", 9);
    auto rotationStopBtnItem = MenuItemLabel::create(rotationStopLabel, [this](Ref *sender){
      AMoAdNativeCocos2dxModule::stopRotation(AD_SID, AD_TAG);
    });
    rotationStopBtnItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 20 - 20 - 20));

    auto reloadLabel = Label::createWithSystemFont("リロード", "Arial", 9);
    auto reloadBtnItem = MenuItemLabel::create(reloadLabel, [this](Ref *sender){
      AMoAdNativeCocos2dxModule::reload(AD_SID, AD_TAG);
    });
    reloadBtnItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 20 - 20 - 20 - 20));

    auto removeLabel = Label::createWithSystemFont("remove", "Arial", 9);
    auto removeBtnItem = MenuItemLabel::create(removeLabel, [this](Ref *sender){
      AMoAdNativeCocos2dxModule::remove(AD_SID, AD_TAG);
    });
    removeBtnItem->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 20 - 20 - 20 - 20 - 20));

    Menu* adMenu = Menu::create(showBtnItem, hideBtnItem, rotationStartBtnItem, rotationStopBtnItem, reloadBtnItem, removeBtnItem, NULL);
    adMenu->setPosition(Point::ZERO);
    this->addChild(adMenu);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
