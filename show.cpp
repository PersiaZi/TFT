#include<iostream>
#include "show.h"
#include "SimpleAudioEngine.h"
#include"LittleHero.h"
#include"wait.h"
#include"BeiZhan.h"
USING_NS_CC;


Size visibleSize;     //���������С
Vec2 origin;      //���λ��
Scene* DraftSpace::createScene()
{
    return DraftSpace::create();
}

// ���ļ�������ʱ����ӡ���õĴ�����Ϣ�����Ƿָ����
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DraftSpace.cpp\n");
}

// �ڡ�init���У���Ҫ��ʼ��ʵ��
bool DraftSpace::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    //����ͼ
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
    LoadingBar* top_Bar = LoadingBar::create("loading_blue.png");
    top_Bar->setScale(0.5);
    top_Bar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - top_Bar->getSize().height));
    top_Bar->setDirection(LoadingBar::Direction::LEFT);
    top_Bar->setPercent(100);
    this->addChild(top_Bar, 1);

    top_LoadingBar = LoadingBar::create("loading_red.png");
    top_LoadingBar->setScale(0.5);
    top_LoadingBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - top_LoadingBar->getSize().height));
    top_LoadingBar->setDirection(LoadingBar::Direction::LEFT);
    per = 0.0f;
    top_LoadingBar->setPercent(per);
    this->addChild(top_LoadingBar, 2);

    this->scheduleUpdate(); //Ĭ�ϵ�����
    //���ʾ
    //װ����ʾ

    //�ٻ�ʦ
    //LittleHero* Summoner = new LittleHero(this);
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(DraftSpace::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(DraftSpace::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    auto m_user = Sprite::create("little_hero.png");
    m_user->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    addChild(m_user, 100, 1);//1��tag
    //��תӢ��
    auto Selhero1 = Sprite::create("QiYaNa.png");
    auto Selhero2 = Sprite::create("JiGeSi.png");
    
    Selhero1->setPosition(Vec2(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 2));
    addChild(Selhero1, 0, 10);
    Selhero2->setPosition(Vec2(origin.x + visibleSize.width / 4*3, origin.y + visibleSize.height / 2));
    addChild(Selhero2,0, 20);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(DraftSpace::readytogo), 8.0f);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(DraftSpace::switchToNextScene), 10.0f);

    return true;
}

void DraftSpace::readytogo(float dt) {
    auto hole = Sprite::create("gare.png");
    hole->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(hole);
}

void DraftSpace::switchToNextScene(float dt) {
    auto sprite1 = getChildByTag(1);
    auto cho1 = getChildByTag(10);
    auto cho2 = getChildByTag(20);
    if (sprite1->getPosition().distance(cho1->getPosition()) < 50.0f)
        LittleHero::getInstance()->gethero("QiYaNa");
    else
        LittleHero::getInstance()->gethero("JiGeSi");
    Director::getInstance()->replaceScene(BeiZhan::create());
}


bool DraftSpace::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void DraftSpace::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto s = getChildByTag(1);
    s->stopAllActions();
    s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));

    //auto sprite1 = getChildByTag(2);
    //auto sprite2 = getChildByTag(3);
    //auto sprite3 = getChildByTag(4);
    //auto sprite4 = getChildByTag(5);

    //// ��龫���Ƿ񵽴��ĸ������Ա�
    //if (s->getPosition().distance(sprite1->getPosition()) < 50.0f)
    //{
    //    // ���þ���1Ϊ�ѱ�ѡ�е�״̬
    //    
    //}
    //else if (s->getPosition().distance(sprite2->getPosition()) < 50.0f)
    //{
    //    // ���þ���2Ϊ�ѱ�ѡ�е�״̬
    //    
    //}
    //else if (s->getPosition().distance(sprite3->getPosition()) < 50.0f)
    //{
    //    // ���þ���3Ϊ�ѱ�ѡ�е�״̬
    //    
    //}
    //else if (s->getPosition().distance(sprite4->getPosition()) < 50.0f)
    //{
    //    // ���þ���4Ϊ�ѱ�ѡ�е�״̬
    //    
    //}

}
void DraftSpace::update(float dt)
{

    per += dt * 10;
    if (per > 100)
    {
        per = 0;
    }
    top_LoadingBar->setPercent(per);
}