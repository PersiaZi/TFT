#ifndef __BATTLE_FILED_H__
#define __BATTLE_FILED_H__

#include "cocos2d.h"

#include"ui\CocosGUI.h"
using namespace cocos2d::ui;

class BattleField : public cocos2d::Scene
{
private:
    float per=0.0f;
    LoadingBar* top_LoadingBar = NULL;

public:
    cocos2d::Size Field_Size;
    cocos2d::Vec2 Field_Origin;

    cocos2d::Label* rund_label = NULL;

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    //手动实现"static create()"方法
    CREATE_FUNC(BattleField);

    virtual void update(float dt)override;


    //按钮回调
    void Store_ButtonCallBack(Ref* ref, Widget::TouchEventType type);
    void Ext_ButtonCallBack(Ref* ref, Widget::TouchEventType type);
    void Upgrade_ButtonCallBack(Ref* ref, Widget::TouchEventType type);
    void Fetter_CheckBoxCallBack(Ref* ref, CheckBox::EventType type); 
    void Equipment_CheckBoxCallBack(Ref* ref, CheckBox::EventType type);
};

#endif // __BATTLE_FILED_H__