#include "SimpleAudioEngine.h"
#include"rule.h"


USING_NS_CC;

Scene* rule::createScene()
{
	return rule::create();
}
Vec2 origin = Director::getInstance()->getVisibleOrigin();

bool rule::init()
{
	auto rules = Sprite::create("rule.png");
	rules->setPosition(origin);
	this->addChild(rules);
	return true;
}