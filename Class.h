#pragma once

//����δ���壩
class Package {

};

class aid //װ����
{

};

//Ӣ�ۻ���
class Hero
{
	friend class aid;
protected:
	//���Բ���
	int blood;//Ѫ��
	int defense_wuli;//�������
	int defense_fashu;//ħ������
	int attack_wuli;//������
	int attack_fashu;//��ǿ
	double attack_speed;//����
	int attack_distance;//��������
	int baoji_rate;//������

	int bloodadd;//������Ѫ
	int baoji_add;//�����˺�����
	//���̲���


	

public:
	Node node;
	//tag����
	int tag_Ali = 0;
	int on_board = 0;//�Ƿ񱻷���ս��,0��ʾû�У�1��ʾ��
	int unable_to_attack = 0;
	//���ܺ���
	virtual void attack(Hero& Hero) {}//ʵʩ����������������Ӧ����Ϣ

	//���ӵ��ƶ�
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
	virtual void ability(int level, Hero& Hero) {}//���Ӷ�Ӧ�ļ���
	virtual void infm_initialize(int level) {}//��Ϣ��ʼ������
	void reveal_UI() {}//��ʾ��ǰ���ӵ�UI��Ϣ
	void buff(Package package)
	{
		;
	}//�Ե�ǰ���Ӽ���װ������buff
	virtual void getdamage(int damage)//�ܵ��˺�
	{
		blood -= damage;
	}//�ܵ��˺�
	//���ʺ���
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
	};//�Ƿ���Թ���
};

//�趨Board�࣬���ڴ���������Ϣ
class Board {
public:
	int num_of_heros;//��ǰӢ������
	vector<Hero> Herolist;//�洢����Ӣ����Ϣ
	vector<Hero> Herolist_object;//���湥��Ŀ�����Ϣ
	void initialize(vector<Hero> Herolist2)//��ʼ��board,��Ҫ�õ���Ϣ
	{
		for (int i = 0; i < Herolist2.size(); i++)
		{
			Herolist.push_back(Herolist2[i]);
		}
	}
	void find(Board enemy)//�ҵ��������Ķ���
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
			//����Ŀ�꣬��Ŀ�괫��
			if (mem != -1)
			{
				Herolist_object.push_back(enemy.Herolist[mem]);
			}
			else//��Ŀ�꣬���ؿ�ֵ
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
//		// ��Ӵ����¼�������
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
//		// ����ͼ�ξ���
//		auto sprite = cocos2d::Sprite::create("sprite.png");
//		sprite->setPosition(touch->getLocation());
//		addChild(sprite);
//
//		// ��ͼ�ξ��鱣�浽������
//		_sprites.pushBack(sprite);
//
//		return true;
//	}
//
//	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
//		// ��ȡ��ǰ����λ��
//		cocos2d::Vec2 touchPos = touch->getLocation();
//
//		// ����ͼ�ξ����λ��
//		for (auto sprite : _sprites) {
//			sprite->setPosition(touchPos);
//		}
//	}
//
//	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
//		// �Ƴ����һ��ͼ�ξ���
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


//�������������֣�
bool divide_double(double a, double b);
Board exe_run();
int exe_fight(Board board1, Board enemy);
void thread_action(Hero& Hero_my, Hero& Hero_enemy);
int exe_all(vector<Hero> Herolist1, vector<Hero> Herolist2);