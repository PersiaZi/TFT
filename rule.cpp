#include "SimpleAudioEngine.h"
#include"rule.h"
#include"wait.h"
USING_NS_CC;

Scene* rule::createScene()
{
	return rule::create();
}


bool rule::init()
{

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->setContentSize(visibleSize);
	auto rules = Sprite::create("rule.png");
	rules->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2));
	this->addChild(rules);
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_0(rule::back,this));
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto start = Sprite::create("start.png");
    start->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 4));
    this->addChild(start);

    auto _mouseListener = EventListenerTouchOneByOne::create();
    _mouseListener->onTouchBegan = CC_CALLBACK_2(rule::touchBeganButtonStart, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, start);


	return true;
}

void rule::back()
{
    Director::getInstance()->popScene();

}

bool rule::touchBeganButtonStart(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if (sprite->getBoundingBox().containsPoint(touPoint)) {
        auto target = wait::create();
        Director::getInstance()->replaceScene(target);

        return true;
    }
    return false;

}