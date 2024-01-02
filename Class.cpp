/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include <vector>
#include <iostream>
#include <chrono>
#include "Class.h"
using namespace std;
using namespace cocos2d;
// 羁绊：秘书护卫，Kda，朋克，耀光使，格斗家，舞者
// 1星棋子：6个
// 奎桑提，库奇，塔里克，娜美，凯南，塔姆
// 2星棋子：6个
// 
// 3星棋子：5个
// 
// 4星棋子：4个
// 
// 5星棋子：3个
// 


//全局变量定义处///////////////////////////////////////////////////////////////////////////////
double time_all;//全局时间参考，用于确定攻击频率

//类定义部分//////////////////////////////////////////////////////////////////////////////////


//棋子的实现部分///////////////////////////////////////////////////////////////////////////////
//1
class KuQi :public Hero 
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 1;
	//根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 450;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 48;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 60;//最大法力值
		}
		if (level == 2)
		{
			blood = 810;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 63;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 60;//最大法力值
		}
		if (level == 3)
		{
			blood = 1458;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 95;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 60;//最大法力值
		}
	}
	void ability(int level, Hero &Hero)//传入的参数是技能等级和受到伤害的目标
	{
		Hero.getdamage(134 + get_attack_wuli() - Hero.get_defense_wuli());
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class TaMu :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 2;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 650;//血量
			defense_wuli = 35;//物理防御
			defense_fashu = 35;//魔法抗性
			attack_wuli = 60;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.55;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 0;//最大法力值
		}
		if (level == 2)
		{
			blood = 1170;//血量
			defense_wuli = 35;//物理防御
			defense_fashu = 35;//魔法抗性
			attack_wuli = 90;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.55;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 0;//最大法力值
		}
		if (level == 3)
		{
			blood = 2106;//血量
			defense_wuli = 35;//物理防御
			defense_fashu = 35;//魔法抗性
			attack_wuli = 135;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.55;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 0;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		;
	}
	void getdamage(int damage)
	{
		blood = blood - damage + int(min(12 * get_attack_fashu() / 100, damage));
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class NaMei :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 3;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 450;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 40;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 75;//最大法力值
		}
		if (level == 2)
		{
			blood = 810;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 60;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 75;//最大法力值
		}
		if (level == 3)
		{
			blood = 1458;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 90;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 75;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		Hero.getdamage(300 * get_attack_fashu() / 100 - Hero.get_defense_fashu());
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};


//2
class Gailun :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 4;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 750;//血量
			defense_wuli = 45;//物理防御
			defense_fashu = 45;//魔法抗性
			attack_wuli = 55;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 40;//初始法力值
			mana_max = 90;//最大法力值
		}
		if (level == 2)
		{
			blood = 1350;//血量
			defense_wuli = 45;//物理防御
			defense_fashu = 45;//魔法抗性
			attack_wuli = 83;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 40;//初始法力值
			mana_max = 90;//最大法力值
		}
		if (level == 3)
		{
			blood = 2430;//血量
			defense_wuli = 45;//物理防御
			defense_fashu = 45;//魔法抗性
			attack_wuli = 124;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 40;//初始法力值
			mana_max = 90;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			blood += 200;
			Hero.getdamage(163 + get_attack_wuli() - Hero.get_defense_wuli());
		}
		if (level == 2)
		{
			blood += 215;
			Hero.getdamage(267 + get_attack_wuli() - Hero.get_defense_wuli());
		}
		if (level == 3)
		{
			blood += 230;
			Hero.getdamage(441 + get_attack_wuli() - Hero.get_defense_wuli());
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Jiakesi :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 5;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 750;//血量
			defense_wuli = 35;//物理防御
			defense_fashu = 35;//魔法抗性
			attack_wuli = 55;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.85;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 50;//初始法力值
			mana_max = 120;//最大法力值
		}
		if (level == 2)
		{
			blood = 1350;//血量
			defense_wuli = 35;//物理防御
			defense_fashu = 35;//魔法抗性
			attack_wuli = 83;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.85;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 50;//初始法力值
			mana_max = 120;//最大法力值
		}
		if (level == 3)
		{
			blood = 2430;//血量
			defense_wuli = 35;//物理防御
			defense_fashu = 35;//魔法抗性
			attack_wuli = 124;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.85;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 50;//初始法力值
			mana_max = 120;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			attack_fashu += 10;
			attack_wuli += 10;
			Hero.getdamage(230 * get_attack_fashu() / 100 - Hero.get_defense_fashu());
		}
		if (level == 2)
		{
			attack_fashu += 10;
			attack_wuli += 10;
			Hero.getdamage(345 * get_attack_fashu() / 100 - Hero.get_defense_fashu());
		}
		if (level == 3)
		{
			attack_fashu += 10;
			attack_wuli += 10;
			Hero.getdamage(520 * get_attack_fashu() / 100 - Hero.get_defense_fashu());
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Gulajiasi :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 6;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 750;//血量
			defense_wuli = 45;//物理防御
			defense_fashu = 45;//魔法抗性
			attack_wuli = 50;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.6;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 40;//初始法力值
			mana_max = 80;//最大法力值
		}
		if (level == 2)
		{
			blood = 1350;//血量
			defense_wuli = 45;//物理防御
			defense_fashu = 45;//魔法抗性
			attack_wuli = 75;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.6;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 40;//初始法力值
			mana_max = 80;//最大法力值
		}
		if (level == 3)
		{
			blood = 2430;//血量
			defense_wuli = 45;//物理防御
			defense_fashu = 45;//魔法抗性
			attack_wuli = 113;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.6;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 40;//初始法力值
			mana_max = 80;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			blood += 500;
		}
		if (level == 2)
		{
			blood += 575;
		}
		if (level == 3)
		{
			blood += 650;
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};


//3

//class Modekaisa :public Hero
//{
//protected:
//	int mana_begin;//初始法力值
//	int mana_max;//最大法力值
//	int grade;
//public:
//	int index = 7;
//	// 根据星级进行初始化
//	void infm_initialize(int level)
//	{
//		grade = level;
//		if (level == 1)
//		{
//			blood = 850;//血量
//			defense_wuli = 55;//物理防御
//			defense_fashu = 55;//魔法抗性
//			attack_wuli = 60;//攻击力
//			attack_fashu = 100;//法强
//			attack_speed = 0.65;//攻速
//			attack_distance = 1;//攻击距离
//			baoji_rate = 25;//暴击率
//			mana_begin = 70;//初始法力值
//			mana_max = 120;//最大法力值
//		}
//		if (level == 2)
//		{
//			blood = 1530;//血量
//			defense_wuli = 55;//物理防御
//			defense_fashu = 55;//魔法抗性
//			attack_wuli = 60;//攻击力
//			attack_fashu = 100;//法强
//			attack_speed = 0.65;//攻速
//			attack_distance = 1;//攻击距离
//			baoji_rate = 25;//暴击率
//			mana_begin = 70;//初始法力值
//			mana_max = 120;//最大法力值
//		}
//		if (level == 3)
//		{
//			blood = 2754;//血量
//			defense_wuli = 55;//物理防御
//			defense_fashu = 55;//魔法抗性
//			attack_wuli = 135;//攻击力
//			attack_fashu = 100;//法强
//			attack_speed = 0.65;//攻速
//			attack_distance = 1;//攻击距离
//			baoji_rate = 25;//暴击率
//			mana_begin = 70;//初始法力值
//			mana_max = 120;//最大法力值
//		}
//	}
//
//};

class Shamila :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;

	int judge_level = 0;
public:
	int index = 8;
	//根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 600;//血量
			defense_wuli = 20;//物理防御
			defense_fashu = 20;//魔法抗性
			attack_wuli = 60;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 100;//最大法力值
		}
		if (level == 2)
		{
			blood = 1080;//血量
			defense_wuli = 20;//物理防御
			defense_fashu = 20;//魔法抗性
			attack_wuli = 90;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 100;//最大法力值
		}
		if (level == 3)
		{
			blood = 1944;//血量
			defense_wuli = 20;//物理防御
			defense_fashu = 20;//魔法抗性
			attack_wuli = 135;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.7;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 100;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			Hero.getdamage((70 + get_attack_wuli() - Hero.get_defense_wuli()) * judge_level);
			judge_level = 0;
		}
		if (level == 2)
		{
			Hero.getdamage((100 + get_attack_wuli() - Hero.get_defense_wuli()) * judge_level);
			judge_level = 0;
		}
		if (level == 3)
		{
			Hero.getdamage((150 + get_attack_wuli() - Hero.get_defense_wuli()) * judge_level);
			judge_level = 0;
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
				judge_level++;
			}
		}
	}
};

class Eyunxiaojie :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 9;
	//根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 650;//血量
			defense_wuli = 20;//物理防御
			defense_fashu = 20;//魔法抗性
			attack_wuli = 60;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 60;//最大法力值
		}
		if (level == 2)
		{
			blood = 1170;//血量
			defense_wuli = 20;//物理防御
			defense_fashu = 20;//魔法抗性
			attack_wuli = 90;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 60;//最大法力值
		}
		if (level == 3)
		{
			blood = 2106;//血量
			defense_wuli = 20;//物理防御
			defense_fashu = 20;//魔法抗性
			attack_wuli = 124;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 60;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			Hero.getdamage(250 + get_attack_wuli() - Hero.get_defense_wuli());
		}
		if (level == 2)
		{
			Hero.getdamage(323 + get_attack_wuli() - Hero.get_defense_wuli());
		}
		if (level == 3)
		{
			Hero.getdamage(440 + get_attack_wuli() - Hero.get_defense_wuli());
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};


//4
class Ali : public Hero{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 10;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 700;//血量
			defense_wuli = 30;//物理防御
			defense_fashu = 30;//魔法抗性
			attack_wuli = 40;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 30;//最大法力值
		}
		if (level == 2)
		{
			blood = 810;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 60;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 75;//最大法力值
		}
		if (level == 3)
		{
			blood = 1458;//血量
			defense_wuli = 15;//物理防御
			defense_fashu = 15;//魔法抗性
			attack_wuli = 90;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.75;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 15;//初始法力值
			mana_max = 75;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			if (Hero.tag_Ali == 0)
			{
				Hero.getdamage(2.7 * get_attack_fashu() - Hero.get_defense_fashu());
				tag_Ali = 1;
			}
			if (Hero.tag_Ali == 1)
			{
				Hero.getdamage(2.7 * get_attack_fashu() - Hero.get_defense_fashu());
				tag_Ali = 1;
			}
		}
		if (level == 2)
		{
			if (Hero.tag_Ali == 0)
			{
				Hero.getdamage(4.1 * get_attack_fashu() - Hero.get_defense_fashu());
				tag_Ali = 1;
			}
			if (Hero.tag_Ali == 1)
			{
				Hero.getdamage(4.1 * get_attack_fashu() - Hero.get_defense_fashu());
				tag_Ali = 1;
			}
		}
		if (level == 3)
		{
			if (Hero.tag_Ali == 0)
			{
				Hero.getdamage(8.2 * get_attack_fashu() - Hero.get_defense_fashu());
				tag_Ali = 1;
			}
			if (Hero.tag_Ali == 1)
			{
				Hero.getdamage(8.2 * get_attack_fashu() - Hero.get_defense_fashu());
				tag_Ali = 1;
			}
		}

	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Kaitelin :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 11;
	//根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 700;//血量
			defense_wuli = 30;//物理防御
			defense_fashu = 30;//魔法抗性
			attack_wuli = 70;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 90;//最大法力值
		}
		if (level == 2)
		{
			blood = 1260;//血量
			defense_wuli = 30;//物理防御
			defense_fashu = 30;//魔法抗性
			attack_wuli = 105;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 90;//最大法力值
		}
		if (level == 3)
		{
			blood = 2268;//血量
			defense_wuli = 30;//物理防御
			defense_fashu = 30;//魔法抗性
			attack_wuli = 158;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 90;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			Hero.getdamage(238 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(238 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(238 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(238 + get_attack_wuli() - Hero.get_defense_wuli());
		}
		if (level == 2)
		{
			Hero.getdamage(357 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(357 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(357 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(357 + get_attack_wuli() - Hero.get_defense_wuli());
		}
		if (level == 3)
		{
			Hero.getdamage(1071 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(1071 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(1071 + get_attack_wuli() - Hero.get_defense_wuli());
			Hero.getdamage(1071 + get_attack_wuli() - Hero.get_defense_wuli());
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Bulici :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 12;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 1000;//血量
			defense_wuli = 60;//物理防御
			defense_fashu = 60;//魔法抗性
			attack_wuli = 60;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.6;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 60;//初始法力值
			mana_max = 120;//最大法力值
		}
		if (level == 2)
		{
			blood = 1800;//血量
			defense_wuli = 60;//物理防御
			defense_fashu = 60;//魔法抗性
			attack_wuli = 90;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.6;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 60;//初始法力值
			mana_max = 120;//最大法力值
		}
		if (level == 3)
		{
			blood = 3240;//血量
			defense_wuli = 60;//物理防御
			defense_fashu = 60;//魔法抗性
			attack_wuli = 135;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.6;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 60;//初始法力值
			mana_max = 120;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			blood += 600;
			Hero.getdamage(400 * Hero.get_attack_fashu() / 100 - Hero.get_defense_fashu());
		}
		if (level == 2)
		{
			blood += 750;
			Hero.getdamage(600 * Hero.get_attack_fashu() / 100 - Hero.get_defense_fashu());
		}
		if (level == 3)
		{
			blood += 2000;
			Hero.getdamage(1500 * Hero.get_attack_fashu() / 100 - Hero.get_defense_fashu());
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

//5
class Qiyana :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 13;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 1000;//血量
			defense_wuli = 60;//物理防御
			defense_fashu = 60;//魔法抗性
			attack_wuli = 75;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.9;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 40;//最大法力值
		}
		if (level == 2)
		{
			blood = 1900;//血量
			defense_wuli = 60;//物理防御
			defense_fashu = 60;//魔法抗性
			attack_wuli = 120;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.9;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 40;//最大法力值
		}
		if (level == 3)
		{
			blood = 7500;//血量
			defense_wuli = 60;//物理防御
			defense_fashu = 60;//魔法抗性
			attack_wuli = 170;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.9;//攻速
			attack_distance = 1;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 0;//初始法力值
			mana_max = 40;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			Hero.unable_to_attack = 10;
			Hero.getdamage(281 + get_attack_wuli());
		}
		if (level == 2)
		{
			Hero.unable_to_attack = 10;
			Hero.getdamage(424 + get_attack_wuli());
		}
		if (level == 3)
		{
			Hero.unable_to_attack = 15;
			Hero.getdamage(8450);
		}
	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else 
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Zhadanren : public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 14;
	// 根据星级进行初始化
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 800;//血量
			defense_wuli = 40;//物理防御
			defense_fashu = 40;//魔法抗性
			attack_wuli = 45;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 30;//初始法力值
			mana_max = 75;//最大法力值
		}
		if (level == 2)
		{
			blood = 1440;//血量
			defense_wuli = 40;//物理防御
			defense_fashu = 40;//魔法抗性
			attack_wuli = 68;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 30;//初始法力值
			mana_max = 75;//最大法力值
		}
		if (level == 3)
		{
			blood = 2592;//血量
			defense_wuli = 40;//物理防御
			defense_fashu = 40;//魔法抗性
			attack_wuli = 101;//攻击力
			attack_fashu = 100;//法强
			attack_speed = 0.8;//攻速
			attack_distance = 4;//攻击距离
			baoji_rate = 25;//暴击率
			mana_begin = 30;//初始法力值
			mana_max = 75;//最大法力值
		}
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		if (level == 1)
		{
			;
		}
		if (level == 2)
		{
			;
		}
		if (level == 3)
		{
			;
		}

	}
	void attack(Hero& Hero)
	{
		if (unable_to_attack == 0)
		{
			unable_to_attack--;
		}
		else
		{
			//技能判定
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//普攻回复法力值
				mana_begin += 10;
				//造成普攻伤害
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

//空棋子
class Null :public Hero
{
protected:
	int mana_begin;//初始法力值
	int mana_max;//最大法力值
	int grade;
public:
	int index = 0;
	//根据星级进行初始化
	void infm_initialize()
	{
		blood = 0;//血量
		defense_wuli = 0;//物理防御
		defense_fashu = 0;//魔法抗性
		attack_wuli = 0;//攻击力
		attack_fashu = 0;//法强
		attack_speed = 0;//攻速
		attack_distance = 0;//攻击距离
		baoji_rate = 0;//暴击率
		mana_begin = 0;//初始法力值
		mana_max = 0;//最大法力值
	}
	void ability(int level, Hero& Hero)//传入的参数是技能等级和受到伤害的目标
	{
		;
	}
	void attack(Hero& Hero)
	{
		;
	}
};



//函数部分////////////////////////////////////////////////////////////////////////////////////

//运行部分函数
//准备阶段运行函数
//Board exe_run()
//{
//	Board me;
//	
//	//监听函数，表示购买了一个棋子Hero_x
//	Hero Hero_x;
//	//放入备战，判断是否三连
//	if (!me.merge())
//	{
//		me.Herolist_beizhan.push_back(Hero_x);
//		me.num_of_heros_aid++;
//	}
//	else
//	{
//		me.levelup(Hero_x);
//	}
//
//	//监听函数，表示卖出了一个棋子Hero_y
//	Hero Hero_y;
//	//卖出棋子
//	
//
//	//监听函数，表示放置了一个棋子到战场上
//	Hero Hero_z;
//	//放到战场上
//
//
//
//	//
//	return me;
//}

//对战阶段运行函数
int exe_fight(Board board1, Board enemy)//运行对战程序
{
	// 进入循环：
	//考虑攻速问题，设定最小时间单位0.01s,希望实现没过0.01s进行一次数据的传入和传出
	const std::chrono::milliseconds loopDuration(100);  // 100 毫秒 = 0.1 秒

	while (true) {
		auto startTime = std::chrono::steady_clock::now();
		//全局时间增加
		time_all = time_all + 0.1;
		// 执行循环函数
		//更新各个对象
		board1.refresh();
		board1.find(enemy);
		//分多线程执行攻击操作
		thread thread0(thread_action, board1.Herolist[0], board1.Herolist_object[0]);
		thread thread1(thread_action, board1.Herolist[1], board1.Herolist_object[1]);
		thread thread2(thread_action, board1.Herolist[2], board1.Herolist_object[2]);
		thread thread3(thread_action, board1.Herolist[3], board1.Herolist_object[3]);
		thread thread4(thread_action, board1.Herolist[4], board1.Herolist_object[4]);
		thread thread5(thread_action, board1.Herolist[5], board1.Herolist_object[5]);
		thread thread6(thread_action, board1.Herolist[6], board1.Herolist_object[6]);
		thread thread7(thread_action, board1.Herolist[7], board1.Herolist_object[7]);
		thread thread8(thread_action, board1.Herolist[8], board1.Herolist_object[8]);
		thread thread9(thread_action, board1.Herolist[9], board1.Herolist_object[9]);

		thread0.join();
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
		thread5.join();
		thread6.join();
		thread7.join();
		thread8.join();
		thread9.join();

		// 计算实际执行时间
		auto endTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		// 等待剩余的时间
		auto remainingTime = loopDuration - elapsedTime;
		if (remainingTime > std::chrono::milliseconds::zero()) {
			std::this_thread::sleep_for(remainingTime);
		}
	}

}//返回胜利与否



//线程函数
//首先判断英雄存不存在，存在进入下一步
//若当前攻击范围内有英雄，进行攻击；
//若没有英雄，则朝距离自己最近的对方英雄方向移动一步————问题：移动需要耗费时间
void thread_action(Hero& Hero_my, Hero& Hero_enemy)
{
	
	//若“我方英雄”这一项不存在（此处用攻速为零进行表示），不进行攻击
	if (Hero_my.get_attack_speed() == 0)
	{
		return;
	}

	//若敌方英雄不在范围内，移动
	int Distance = Hero_my.node.getPosition().distance(Hero_enemy.node.getPosition());
	int Distance_base = Distance;
	if (Distance > Hero_my.get_attack_distance() * 100)
	{
		Hero_my.move_up();
		if (Distance_base > Distance)
		{
			Hero_my.move_down();
		}
		else 
		{
			Distance_base = Distance;
		}

		Hero_my.move_left();
		if (Distance_base > Distance)
		{
			Hero_my.move_right();
		}
		else
		{
			Distance_base = Distance;
		}

		Hero_my.move_right();
		if (Distance_base > Distance)
		{
			Hero_my.move_left();
		}
		else
		{
			Distance_base = Distance;
		}

		Hero_my.move_down();
		if (Distance_base > Distance)
		{
			Hero_my.move_up();
		}
		else
		{
			Distance_base = Distance;
		}
	}
	else 
	{
		//若此时的全局时间达到攻速间隔的整数倍，进行攻击
		if (divide_double(time_all, Hero_my.get_attack_speed()))
		{
			Hero_my.attack(Hero_enemy);
		}
	}
}

//辅助函数部分
//用于计算两个小数之间能不能被整除，能返回true，不能返回false
//a大b小
bool divide_double(double a, double b)
{
	int num;
	while (1)
	{
		num = a - b;
		if (num == 0)
		{
			return true;
		}
		if (num < 0)
		{
			return false;
		}
	}
}


int exe_all(vector<Hero> Herolist1, vector<Hero> Herolist2)
{
	int consequence;
	Board me, enemy;
	me.initialize(Herolist1);
	enemy.initialize(Herolist2);
	consequence = exe_fight(me, enemy);//运行战斗，击败敌方返回正数（表示对敌方造成的伤害），否则返回负数（表示受到的伤害）
	return consequence;
}



