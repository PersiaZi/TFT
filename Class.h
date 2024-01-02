#pragma once

//包（未定义）
class Package {

};

class aid //装备类
{

};

//英雄基类
class Hero
{
	friend class aid;
protected:
	//属性部分
	int blood;//血量
	int defense_wuli;//物理防御
	int defense_fashu;//魔法抗性
	int attack_wuli;//攻击力
	int attack_fashu;//法强
	double attack_speed;//攻速
	int attack_distance;//攻击距离
	int baoji_rate;//暴击率

	int bloodadd;//物理吸血
	int baoji_add;//暴击伤害增加
	//棋盘部分


	

public:
	Node node;
	//tag部分
	int tag_Ali = 0;
	int on_board = 0;//是否被放入战场,0表示没有，1表示有
	int unable_to_attack = 0;
	//功能函数
	virtual void attack(Hero& Hero) {}//实施攻击动作并给出对应的信息

	//棋子的移动
	void move_up(){
		cocos2d::Vec2 currentPosition = node.getPosition();
		currentPosition.y += 200;
		node.setPosition(currentPosition);
	}
	void move_left(){
		cocos2d::Vec2 currentPosition = node.getPosition();
		currentPosition.x += 200;
		node.setPosition(currentPosition);
	}
	void move_right(){
		cocos2d::Vec2 currentPosition = node.getPosition();
		currentPosition.x -= 200;
		node.setPosition(currentPosition);
	}
	void move_down() {
		cocos2d::Vec2 currentPosition = node.getPosition();
		currentPosition.y -= 200;
		node.setPosition(currentPosition);
	}
	virtual void ability(int level, Hero& Hero) {}//棋子对应的技能
	virtual void infm_initialize(int level) {}//信息初始化函数
	void reveal_UI() {}//显示当前棋子的UI信息
	void buff(Package package)
	{
		;
	}//对当前棋子加上装备，羁绊等buff
	virtual void getdamage(int damage)//受到伤害
	{
		blood -= damage;
	}//受到伤害
	//访问函数
	int get_defense_wuli()
	{
		return defense_wuli;
	}
	int get_defense_fashu()
	{
		return defense_fashu;
	}
	int get_attack_distance() {
		return attack_distance;
	}
	int get_attack_speed() {
		return attack_speed;
	}
	int get_blood()
	{
		return blood;
	}
	int get_attack_fashu() {
		return attack_fashu;
	}
	int get_attack_wuli() {
		return attack_wuli;
	}
	int get_baoji_rate() {
		return baoji_rate;
	}
	int get_bloodadd() {
		return bloodadd;
	}
	int get_baoji_add() {
		return baoji_add;
	}
	bool attack_available()
	{
		if (unable_to_attack == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	};//是否可以攻击
};

//设定Board类，用于储存棋盘信息
class Board {
public:
	int num_of_heros;//当前英雄数量
	vector<Hero> Herolist;//存储各个英雄信息
	vector<Hero> Herolist_object;//储存攻击目标的信息
	void initialize(vector<Hero> Herolist2)//初始化board,需要得到信息
	{
		for (int i = 0; i < Herolist2.size(); i++)
		{
			Herolist.push_back(Herolist2[i]);
		}
	}
	void find(Board enemy)//找到被攻击的对象
	{
		for (int i = 0; i <= Herolist.size(); i++)
		{
			Null m;
			m.infm_initialize();
			int mem = -1;
			float distance;
			float min = 100000;
			for (int j = 0; j <= enemy.Herolist.size(); j++)
			{
				if (enemy.Herolist[j].get_blood() <= 0)
				{
					continue;
				}
				distance = Herolist[0].node.getPosition().distance(enemy.Herolist[j].node.getPosition());
				if (distance < min)
				{
					min = distance;
					mem = j;
				}
			}
			//若有目标，将目标传回
			if (mem != -1)
			{
				Herolist_object.push_back(enemy.Herolist[mem]);
			}
			else//无目标，传回空值
			{
				Herolist_object.push_back(m);
			}
		}
	}
};

//class MyScene : public cocos2d::Scene {
//public:
//	CREATE_FUNC(MyScene);
//
//	virtual bool init() {
//		if (!Scene::init()) {
//			return false;
//		}
//
//		// 添加触摸事件监听器
//		auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
//		touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
//		touchListener->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
//		touchListener->onTouchEnded = CC_CALLBACK_2(MyScene::onTouchEnded, this);
//		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
//
//		return true;
//	}
//
//	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
//		// 创建图形精灵
//		auto sprite = cocos2d::Sprite::create("sprite.png");
//		sprite->setPosition(touch->getLocation());
//		addChild(sprite);
//
//		// 将图形精灵保存到数组中
//		_sprites.pushBack(sprite);
//
//		return true;
//	}
//
//	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
//		// 获取当前触摸位置
//		cocos2d::Vec2 touchPos = touch->getLocation();
//
//		// 更新图形精灵的位置
//		for (auto sprite : _sprites) {
//			sprite->setPosition(touchPos);
//		}
//	}
//
//	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
//		// 移除最后一个图形精灵
//		if (!_sprites.empty()) {
//			auto lastSprite = _sprites.back();
//			lastSprite->removeFromParent();
//			_sprites.popBack();
//		}
//	}
//
//private:
//	cocos2d::Vector<cocos2d::Sprite*> _sprites;
//};


//函数的声明部分：
bool divide_double(double a, double b);
Board exe_run();
int exe_fight(Board board1, Board enemy);
void thread_action(Hero& Hero_my, Hero& Hero_enemy);
int exe_all(vector<Hero> Herolist1, vector<Hero> Herolist2);