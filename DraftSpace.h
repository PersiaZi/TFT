#ifndef __DRAFT_SPACE_H__
#define __DRAFT_SPACE_H__

#include "cocos2d.h"

class DraftSpace : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    //�ֶ�ʵ��"static create()"����
    CREATE_FUNC(DraftSpace);
};

#endif // __DRAFT_SPACE_H__