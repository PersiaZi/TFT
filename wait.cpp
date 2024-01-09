#include"cocos2d.h"
#include"wait.h"
#include"show.h"

USING_NS_CC;



bool wait::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto cover = Sprite::create("cover.png");
    cover->setContentSize(visibleSize);
    cover->setPosition(Vec2(origin.x / 2 + visibleSize.width / 2, origin.y / 2 + visibleSize.height / 2));
    this->addChild(cover);

    
    auto singleNormalSprite=cocos2d::Sprite::create("single.png");
    auto singleSelectedSprite = cocos2d::Sprite::create("single.png");
    auto singlePlayerItem = cocos2d::MenuItemSprite::create(
        singleNormalSprite,
        singleSelectedSprite,
        [](cocos2d::Ref* sender) {
            Director::getInstance()->replaceScene(DraftSpace::create());
        });

    auto menu = cocos2d::Menu::create(singlePlayerItem, nullptr);
    menu->alignItemsVertically();
    menu->setPosition(Vec2(origin.x / 2 + visibleSize.width / 2, origin.y / 2 + visibleSize.height / 2));

    // Add the menu to the scene
    this->addChild(menu,1);

    return true;
}

