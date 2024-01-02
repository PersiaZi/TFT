#pragma once

#include "cocos2d.h"

class rule: public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(rule);
    bool rule::touchBeganButtonStart(cocos2d::Touch* touch, cocos2d::Event* event);
    void rule::back();// pop the rule
};

