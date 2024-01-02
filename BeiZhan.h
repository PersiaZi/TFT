#pragma once


#include"network/WebSocket.h"
#include "cocos2d.h"


class BeiZhan : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void readytogo(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BeiZhan);
    bool BeiZhan::touchBeganButtonStart(cocos2d::Touch* touch, cocos2d::Event* event);

};
