#pragma once



#include "cocos2d.h"
#include"ui/CocosGUI.h"


using namespace cocos2d::ui;


class DraftSpace : public cocos2d::Scene
{
public:
    void DraftSpace::readytogo(float dt);
    void switchToNextScene(float dt);
    static cocos2d::Scene* createScene();
    float per = 0.0f;
    LoadingBar* top_LoadingBar = NULL;
    virtual void update(float dt)override;
    virtual bool init();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    //手动实现"static create()"方法
    CREATE_FUNC(DraftSpace);
};
