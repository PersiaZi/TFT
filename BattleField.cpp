#include<iostream>
#include "BattleField.h"
#include "SimpleAudioEngine.h"

#include "LittleHero.h"

USING_NS_CC;

Scene* BattleField::createScene()
{
    return BattleField::create();
}

// ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿָ����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in BattleField.cpp\n");
}

// �ڡ�init���У���Ҫ��ʼ��ʵ��
bool BattleField::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    Field_Size = Director::getInstance()->getVisibleSize();       //���������С
    Field_Origin = Director::getInstance()->getVisibleOrigin();          //���λ��

    //����ͼ
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


    // ״̬��ʾ
    rund_label = Label::createWithTTF("Rund: 1/2", "fonts/Marker Felt.ttf", Field_Size.height / 25);
    rund_label->setTag(1);
    if (rund_label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // ���̵갴ť��
        rund_label->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 26 / 27));
        rund_label->setColor(Color3B::WHITE);

        // ��ӱ�ǩ��Ϊ��ͼ��
        this->addChild(rund_label);

    }

    // ������
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

    this->scheduleUpdate(); //Ĭ�ϵ�����
    // �෽Ѫ��
    // �ִ�����-��������
    

    // �˳���ť
    Button* ext_button = Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
    ext_button->ignoreContentAdaptWithSize(false);
    Size ext_size;
    ext_size.width = Field_Size.width / 30;
    ext_size.height = Field_Size.width / 30;
    ext_button->setSize(ext_size);
    ext_button->setPosition(Vec2(Field_Size.width * 17 / 18, Field_Size.height * 25 / 27));
    ext_button->addTouchEventListener(CC_CALLBACK_2(BattleField::Ext_ButtonCallBack, this));
    this->addChild(ext_button);

    
    //���ʾ
    //װ����ʾ
    CheckBox* fetter = CheckBox::create("fetter_2.png", "fetter.png");
    fetter->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 19 / 27));
    fetter->addEventListener(CC_CALLBACK_2(BattleField::Fetter_CheckBoxCallBack, this));
    this->addChild(fetter);

    CheckBox* equipment = CheckBox::create("eq2.png", "eq1.png");
    equipment->setPosition(Vec2(Field_Size.width * 1 / 18, Field_Size.height * 16 / 27));
    equipment->addEventListener(CC_CALLBACK_2(BattleField::Equipment_CheckBoxCallBack, this));
    this->addChild(equipment);




    //�ٻ�ʦ
    LittleHero* Summoner = new LittleHero(this, Field_Size, Field_Origin);

    //���ϵͳ����ҵ�������Ϣ��ʾ��-��������ˢ��
    void num_to_char(int num, char ch_flash[3]);
    char ch_money[5] = { 0 };
    int num_flash = Summoner->goldsum();
    num_to_char(num_flash, ch_money); //��ȡ�����

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
        // ���̵갴ť��
        sort_label->setPosition(Vec2(Field_Size.width * 8 / 9 + button_size.width / 7, Field_Size.height * 4 / 27));
        sort_label->setColor(Color3B::ORANGE);

        // ��ӱ�ǩ��Ϊ��ͼ��
        this->addChild(sort_label, 2);
    }
    button->addTouchEventListener(CC_CALLBACK_2(BattleField::Store_ButtonCallBack, this));
    this->addChild(button);

    //������->�������������ȼ���ʾ
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
        // ��������ť��
        upgrade_label->setPosition(Vec2(Field_Size.width * 1 / 15 + upgrade_button_size.width / 3, 
                                        Field_Size.height * 4 / 27- upgrade_button_size.height / 3));
        upgrade_label->setColor(Color3B::WHITE);

        // ��ӱ�ǩ��Ϊ��ͼ��
        this->addChild(upgrade_label, 2);
    }
    upgrade_button->addTouchEventListener(CC_CALLBACK_2(BattleField::Upgrade_ButtonCallBack, this));
    this->addChild(upgrade_button);

    //׼����-������ϵͳ
    //׼�������125����ÿ��

    return true;
}

//ʱ�����
void BattleField::update(float dt)
{
    //4*6=240��180�顢����װ��---->����������ѡ����˹
    //���50���һ��
    //10�뱸ս��ѡ����˹
    //���50��ڶ���
    //����

    static int step = 1;

    switch (step)
    {
    case 1:     //׼���׶�
    {
        per += dt * 100 / 240;
        break;
    }
    case 2:     //���һ��
    {
        per += dt * 100 / 60;
        break;
    }
    case 3:     //ѡ����˹
    {
        per += dt * 100 / 10;
        break;
    }
    case 4:     //��ڶ���
    {
        per += dt * 100 / 60;
        break;
    }
    case 5:     //����
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

//�̵�
void BattleField::Store_ButtonCallBack(Ref* ref, Widget::TouchEventType type)
{
    //1��*27�ţ�2��*31��3��*18,4��*15��5��*11��ÿ��)
    // 1����          1
    // 2��ķ          1
    // 3����          1
    // 4����          2
    // 5�ֿ�˹        2  
    // 6������˹      2
    // 7Ī�¿���      2
    // 8ɯ����        2
    // 9����С��      3
    // 10����         4
    // 11������       4
    // 12�����       4
    // 13������       5
    // 14����         5
    // NULL
    //

    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::ENDED:    //�ſ���ť
        CCLOG("Store\n");

        //����ˢ�°�ť
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
        //    // ���̵갴ť��
        //    sort_label->setPosition(Vec2(Field_Size.width * 8 / 9 + button_size.width / 7, Field_Size.height * 4 / 27));
        //    sort_label->setColor(Color3B::ORANGE);

        //    // ��ӱ�ǩ��Ϊ��ͼ��
        //    this->addChild(sort_label, 2);
        //}
        //button->addTouchEventListener(CC_CALLBACK_2(BattleField::Store_ButtonCallBack, this));
        //this->addChild(button);

        //�����ȴ���










        break;
    }
}

void BattleField::Ext_ButtonCallBack(Ref* ref, Widget::TouchEventType type)     //�˳�
{
    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::ENDED:    //�ſ���ť
        Director::getInstance()->end();
        CCLOG("Ext\n");
        break;
    }
}

void BattleField::Upgrade_ButtonCallBack(Ref* ref, Widget::TouchEventType type)
{
    switch (type)
    {
    case cocos2d::ui::Widget::TouchEventType::ENDED:    //�ſ���ť
        CCLOG("Upgrade\n");
        break;
    }
}
void BattleField::Fetter_CheckBoxCallBack(Ref* ref, CheckBox::EventType type)
{
    switch (type)
    {
    case cocos2d::ui::CheckBox::EventType::SELECTED :    //ѡ��
        CCLOG("Fetter_SELECTED\n");
        break;
    case cocos2d::ui::CheckBox::EventType::UNSELECTED :    //δѡ��
        CCLOG("Fetter_UNSELECTED\n");
        break;
    }
}

void BattleField::Equipment_CheckBoxCallBack(Ref* ref, CheckBox::EventType type)
{
    switch (type)
    {
    case cocos2d::ui::CheckBox::EventType::SELECTED:    //ѡ��
        CCLOG("Equipment_SELECTED\n");
        break;
    case cocos2d::ui::CheckBox::EventType::UNSELECTED:    //δѡ��
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