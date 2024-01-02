#include "SimpleAudioEngine.h"
#include"BattleField.h"
#include"wait.h"
#include"BeiZhan.h"
USING_NS_CC;

Scene* BeiZhan::createScene()
{
    return BeiZhan::create();
}



bool BeiZhan::init()
{
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto cover = Sprite::create("battlefield.png");
    cover->setContentSize(visibleSize);
    cover->setPosition(Vec2(origin.x / 2 + visibleSize.width / 2, origin.y / 2 + visibleSize.height / 2));
    this->addChild(cover);
    auto golden = Sprite::create("golden.png");
    auto con = Sprite::create("con.png");
    auto upgrade = Sprite::create("upgrade.png");
    golden->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 4));
    con->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    upgrade->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.33));

    this->addChild(golden, 0, 1);
    this->addChild(con, 0, 2);
    this->addChild(upgrade, 0, 3);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(BeiZhan::readytogo), 2.0f);


    return true;
}


bool BeiZhan::touchBeganButtonStart(cocos2d::Touch* touch, cocos2d::Event* event)
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

void BeiZhan::readytogo(float dt) {
    Director::getInstance()->replaceScene(BattleField::create());
}
