#include<iostream>
#include "DraftSpace.h"
#include "SimpleAudioEngine.h"

#include "LittleHero.h"

USING_NS_CC;

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

    Size visibleSize = Director::getInstance()->getVisibleSize();       //���������С
    Vec2 origin = Director::getInstance()->getVisibleOrigin();          //���λ��

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
    
    //���ʾ
    //װ����ʾ

    //�ٻ�ʦ
    //LittleHero* Summoner = new LittleHero(this);

    //��תӢ��

    
    return true;
}
