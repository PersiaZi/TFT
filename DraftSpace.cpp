#include<iostream>
#include "DraftSpace.h"
#include "SimpleAudioEngine.h"

#include "LittleHero.h"

USING_NS_CC;

Scene* DraftSpace::createScene()
{
    return DraftSpace::create();
}

// 当文件不存在时，打印有用的错误信息而不是分割错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DraftSpace.cpp\n");
}

// 在“init”中，需要初始化实例
bool DraftSpace::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();       //可视区域大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();          //起点位置

    //背景图
    Sprite* BackGround = Sprite::create("show.png");
    if (BackGround)
    {
        BackGround->setScale(visibleSize.width / BackGround->getTextureRect().getMaxX(), visibleSize.height / BackGround->getTextureRect().getMaxY());
        BackGround->setPosition(visibleSize / 2);
        this->addChild(BackGround);
    }
    else
    {
        std::cout << "Can not find show.png" << std::endl;
    }
    
    //羁绊显示
    //装备显示

    //召唤师
    //LittleHero* Summoner = new LittleHero(this);

    //旋转英雄

    
    return true;
}
