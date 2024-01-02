#ifndef __LITTLE_HERO_H__
#define __LITTLE_HERO_H__

#include "cocos2d.h"
#include<iostream>

enum 
{
    KuQi=1
};

class hero
{
public:
    int id;
    std::string name;
    int starlevel;
};

class LittleHero
{
private:
    LittleHero() {};
    static LittleHero* H_instance;
    cocos2d::Size Site_Size;        //场地大小
    cocos2d::Vec2 Site_Orign;       //场地原地
    cocos2d::Size Self_Size;        //自身大小
    cocos2d::Vec2 Self_Orign;       //自身原点
    std::vector<std::map<std::string, int>> Dnphero;
    std::vector<std::map<std::string, int>> Phero;
    int blood;
    int gold;
    int level;
    int exp;
public:
    static LittleHero* getInstance()
    {
        if (H_instance == nullptr)
        {
            H_instance = new LittleHero();
            
        }
        return H_instance;

    }
    void m_init() {
        blood = 20;
        gold = 180;
        level = 1;
        exp = 0;
    }
    //virtual bool init();
    void expup(int num)
    {
    }

    void goldchange(int num)
    {
        gold += num;
    }

    void bloodchange(int num)
    {
        blood -= num;
    }
    LittleHero(cocos2d::Scene* this_scene,cocos2d::Size vSize, cocos2d::Vec2 orign);

    void gethero(std::string ihero)
    {

    }
};
#endif // __LITTLE_HERO_H__