#include<iostream>
#include "LittleHero.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


//创建小小英雄(场景、大小、原点)
LittleHero::LittleHero(cocos2d::Scene* this_scene, cocos2d::Size vSize, cocos2d::Vec2 orign)
{
    auto Little_Hero = Sprite::create("little_hero.png");
    if (Little_Hero)
    {
        Site_Size = vSize;
        Site_Orign = orign;

        Self_Size = Site_Size / 3000;
        Little_Hero->setScale(Self_Size.width, Self_Size.height);
        Little_Hero->setPosition(Site_Size.width * 3 / 16, Site_Size.height * 1 / 6);
       // Little_Hero->setPosition(1200, 675);
//        Little_Hero->setPosition(450, 100);
        this_scene->addChild(Little_Hero);
    }
    else
    {
        std::cout << "Can not find little_hero.png" << std::endl;
    }
    
}
