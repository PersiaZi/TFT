#pragma once

#include "cocos2d.h"

class wait : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(wait);
    bool wait::touchBeganButtonStart(cocos2d::Touch* touch, cocos2d::Event* event);
};