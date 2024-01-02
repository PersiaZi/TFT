#include<iostream>
#include "BattleField.h"
#include "SimpleAudioEngine.h"

#include "LittleHero.h"

USING_NS_CC;

Scene* BattleField::createScene()
{
    return BattleField::create();
}

// 当文件不存在时，打印有用的错误信息而不是分割错误。
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BattleField.cpp\n");
}

// 在“init”中，需要初始化实例
bool BattleField::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Field_Size = Director::getInstance()->getVisibleSize();       //可视区域大小
    Field_Origin = Director::getInstance()->getVisibleOrigin();          //起点位置

    //背景图
    Sprite* BackGround = Sprite::create("battlefield.png");
    if (BackGround)
    {
        BackGround->setScale(Field_Size.width / BackGround->getTextureRect().getMaxX(), Field_Size.height / BackGround->getTextureRect().getMaxY());
        BackGround->setPosition(Field_Size / 2);
        this->addChild(BackGround);
    }
    else
    {
        std::cout << "Can not find battlefield.png" << std::endl;
    }


    // 状态提示
    rund_label = Label::createWithTTF("Rund: 1/2", "fonts/Marker Felt.ttf", Field_Size.height / 25);
    rund_label->setTag(1);
    if (rund_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 放商店按钮上
        rund_label->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 26 / 27));
        rund_label->setColor(Color3B::WHITE);

        // 添加标签作为子图层
        this->addChild(rund_label);

    }

    // 进度条
    LoadingBar* top_Bar = LoadingBar::create("loading_blue.png");
    top_Bar->setScale(0.5);
    top_Bar->setPosition(Vec2(Field_Size.width / 2, Field_Size.height - top_Bar->getSize().height));
    top_Bar->setDirection(LoadingBar::Direction::LEFT);
    top_Bar->setPercent(100);
    this->addChild(top_Bar, 1);

    top_LoadingBar = LoadingBar::create("loading_red.png");
    top_LoadingBar->setScale(0.5);
    top_LoadingBar->setPosition(Vec2(Field_Size.width / 2, Field_Size.height - top_LoadingBar->getSize().height));
    top_LoadingBar->setDirection(LoadingBar::Direction::LEFT);
    per = 0.0f;
    top_LoadingBar->setPercent(per);
    this->addChild(top_LoadingBar, 2);

    this->scheduleUpdate(); //默认调度器
    // 多方血条
    // 轮次提醒-》传送门
    

    // 退出按钮
    Button* ext_button = Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
    ext_button->ignoreContentAdaptWithSize(false);
    Size ext_size;
    ext_size.width = Field_Size.width / 30;
    ext_size.height = Field_Size.width / 30;
    ext_button->setSize(ext_size);
    ext_button->setPosition(Vec2(Field_Size.width * 17 / 18, Field_Size.height * 25 / 27));
    ext_button->addTouchEventListener(CC_CALLBACK_2(BattleField::Ext_ButtonCallBack, this));
    this->addChild(ext_button);

    
    //羁绊显示
    //装备显示
    CheckBox* fetter = CheckBox::create("fetter_2.png", "fetter.png");
    fetter->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 19 / 27));
    fetter->addEventListener(CC_CALLBACK_2(BattleField::Fetter_CheckBoxCallBack, this));
    this->addChild(fetter);

    CheckBox* equipment = CheckBox::create("eq2.png", "eq1.png");
    equipment->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 16 / 27));
    equipment->addEventListener(CC_CALLBACK_2(BattleField::Equipment_CheckBoxCallBack, this));
    this->addChild(equipment);




    //召唤师
    LittleHero* Summoner = new LittleHero(this, Field_Size, Field_Origin);

    //金币系统（金币点数、利息显示）-》买卡区、刷新
    void num_to_char(int num, char ch_flash[3]);
    char ch_money[5] = { 0 };
    int num_flash = Summoner->goldsum();
    num_to_char(num_flash, ch_money); //读取金币数

    Button* button = Button::create("normal_store.png", "selected_image.png", "normal_store.png");
    button->ignoreContentAdaptWithSize(false);
    Size button_size;
    button_size.width = Field_Size.width / 16;
    button_size.height = Field_Size.width / 16;
    button->setSize(button_size);
    button->setPosition(Vec2(Field_Size.width * 8 / 9, Field_Size.height * 4 / 27));
    Label* sort_label = Label::createWithTTF(ch_money, "fonts/Marker Felt.ttf", button_size.height / 3);
    if (sort_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 放商店按钮上
        sort_label->setPosition(Vec2(Field_Size.width * 8 / 9 + button_size.width / 7, Field_Size.height * 4 / 27));
        sort_label->setColor(Color3B::ORANGE);

        // 添加标签作为子图层
        this->addChild(sort_label, 2);
    }
    button->addTouchEventListener(CC_CALLBACK_2(BattleField::Store_ButtonCallBack, this));
    this->addChild(button);

    //购买经验->升级进度条、等级显示
    Button* upgrade_button = Button::create("upgrade1.png", "upgrade2.png", "upgrade2.png");
    upgrade_button->ignoreContentAdaptWithSize(false);
    Size upgrade_button_size;
    upgrade_button_size.width = Field_Size.width / 12;
    upgrade_button_size.height = Field_Size.width / 12;
    upgrade_button->setSize(upgrade_button_size);
    upgrade_button->setPosition(Vec2(Field_Size.width * 1 / 15, Field_Size.height * 4 / 27));
    Label* upgrade_label = Label::createWithTTF("10", "fonts/Marker Felt.ttf", upgrade_button_size.height / 7);
    if (upgrade_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 放升级按钮上
        upgrade_label->setPosition(Vec2(Field_Size.width * 1 / 15 + upgrade_button_size.width / 3, 
                                        Field_Size.height * 4 / 27- upgrade_button_size.height / 3));
        upgrade_label->setColor(Color3B::WHITE);

        // 添加标签作为子图层
        this->addChild(upgrade_label, 2);
    }
    upgrade_button->addTouchEventListener(CC_CALLBACK_2(BattleField::Upgrade_ButtonCallBack, this));
    this->addChild(upgrade_button);

    //准备区-》出售系统
    //准备区宽度125像素每格

    return true;
}

//时间更新
void BattleField::update(float dt)
{
    //4*6=240发180块、六件装备---->进店买东西、选海克斯
    //打架50秒第一轮
    //10秒备战、选海克斯
    //打架50秒第二轮
    //结束

    static int step = 1;

    switch (step)
    {
    case 1:     //准备阶段
    {
        per += dt * 100 / 240;
        break;
    }
    case 2:     //打第一轮
    {
        per += dt * 100 / 60;
        break;
    }
    case 3:     //选海克斯
    {
        per += dt * 100 / 10;
        break;
    }
    case 4:     //打第二轮
    {
        per += dt * 100 / 60;
        break;
    }
    case 5:     //结束
    {
        Director::getInstance()->end();
        break;
    }

    }
    if (per > 100)
    {
        per = 0;
        step++;

        this->removeChildByTag(1);
        auto rund_label = getChildByTag(1);
        char char_rund_label[20] = "Rund:  /2";
        if (step < 3)
        {
            char_rund_label[6] = '1';
        }
        else
        {
            char_rund_label[6] = '2';
        }
        rund_label = Label::createWithTTF(char_rund_label, "fonts/Marker Felt.ttf", Field_Size.height / 25);
        rund_label->setTag(1);
        rund_label->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 26 / 27));
        rund_label->setColor(Color3B::WHITE);
        this->addChild(rund_label);
    }

    top_LoadingBar->setPercent(per);   
}

//商店
void BattleField::Store_ButtonCallBack(Ref* ref, Widget::TouchEventType type)
{
    //1费*27张，2费*31，3费*18,4费*15，5费*11（每人)
    // 1库奇          1
    // 2塔姆          1
    // 3娜美          1
    // 4盖伦          2
    // 5贾克斯        2  
    // 6古拉加斯      2
    // 7莫德凯撒      2
    // 8莎米拉        2
    // 9厄运小姐      3
    // 10阿狸         4
    // 11凯特琳       4
    // 12布里茨       4
    // 13奇亚娜       5
    // 14娜美         5
    // NULL
    //

    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::ENDED:    //放开按钮
        CCLOG("Store\n");

        //创建刷新按钮
        //Button* button = Button::create("normal_store.png", "selected_image.png", "normal_store.png");
        //button->ignoreContentAdaptWithSize(false);
        //Size button_size;
        //button_size.width = Field_Size.width / 16;
        //button_size.height = Field_Size.width / 16;
        //button->setSize(button_size);
        //button->setPosition(Vec2(Field_Size.width * 8 / 9, Field_Size.height * 4 / 27));
        //Label* sort_label = Label::createWithTTF("10", "fonts/Marker Felt.ttf", button_size.height / 3);
        //if (sort_label == nullptr)
        //{
        //    problemLoading("'fonts/Marker Felt.ttf'");
        //}
        //else
        //{
        //    // 放商店按钮上
        //    sort_label->setPosition(Vec2(Field_Size.width * 8 / 9 + button_size.width / 7, Field_Size.height * 4 / 27));
        //    sort_label->setColor(Color3B::ORANGE);

        //    // 添加标签作为子图层
        //    this->addChild(sort_label, 2);
        //}
        //button->addTouchEventListener(CC_CALLBACK_2(BattleField::Store_ButtonCallBack, this));
        //this->addChild(button);

        //创建等待表










        break;
    }
}

void BattleField::Ext_ButtonCallBack(Ref* ref, Widget::TouchEventType type)     //退出
{
    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::ENDED:    //放开按钮
        Director::getInstance()->end();
        CCLOG("Ext\n");
        break;
    }
}

void BattleField::Upgrade_ButtonCallBack(Ref* ref, Widget::TouchEventType type)
{
    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::ENDED:    //放开按钮
        CCLOG("Upgrade\n");
        break;
    }
}
void BattleField::Fetter_CheckBoxCallBack(Ref* ref, CheckBox::EventType type)
{
    switch (type)
    {
    case cocos2d::ui::CheckBox::EventType::SELECTED :    //选中
        CCLOG("Fetter_SELECTED\n");
        break;
    case cocos2d::ui::CheckBox::EventType::UNSELECTED :    //未选中
        CCLOG("Fetter_UNSELECTED\n");
        break;
    }
}

void BattleField::Equipment_CheckBoxCallBack(Ref* ref, CheckBox::EventType type)
{
    switch (type)
    {
    case cocos2d::ui::CheckBox::EventType::SELECTED:    //选中
        CCLOG("Equipment_SELECTED\n");
        break;
    case cocos2d::ui::CheckBox::EventType::UNSELECTED:    //未选中
        CCLOG("Equipment_UNSELECTED\n");
        break;
    }
}

void num_to_char(int num, char ch_flash[3])
{
    if (num < 1000)
    {
        ch_flash[0] = num / 100%10+'0';
        ch_flash[1] = num / 10%10+'0';
        ch_flash[2] = num % 10+'0';
    }
}