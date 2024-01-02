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
// ����黤����Kda����ˣ�ҫ��ʹ���񶷼ң�����
// 1�����ӣ�6��
// ��ɣ�ᣬ���棬����ˣ����������ϣ���ķ
// 2�����ӣ�6��
// 
// 3�����ӣ�5��
// 
// 4�����ӣ�4��
// 
// 5�����ӣ�3��
// 


//ȫ�ֱ������崦///////////////////////////////////////////////////////////////////////////////
double time_all;//ȫ��ʱ��ο�������ȷ������Ƶ��

//�ඨ�岿��//////////////////////////////////////////////////////////////////////////////////


//���ӵ�ʵ�ֲ���///////////////////////////////////////////////////////////////////////////////
//1
class KuQi :public Hero 
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 1;
	//�����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 450;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 48;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 60;//�����ֵ
		}
		if (level == 2)
		{
			blood = 810;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 63;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 60;//�����ֵ
		}
		if (level == 3)
		{
			blood = 1458;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 95;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 60;//�����ֵ
		}
	}
	void ability(int level, Hero &Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class TaMu :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 2;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 650;//Ѫ��
			defense_wuli = 35;//�������
			defense_fashu = 35;//ħ������
			attack_wuli = 60;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.55;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 0;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1170;//Ѫ��
			defense_wuli = 35;//�������
			defense_fashu = 35;//ħ������
			attack_wuli = 90;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.55;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 0;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2106;//Ѫ��
			defense_wuli = 35;//�������
			defense_fashu = 35;//ħ������
			attack_wuli = 135;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.55;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 0;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class NaMei :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 3;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 450;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 40;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
		if (level == 2)
		{
			blood = 810;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 60;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
		if (level == 3)
		{
			blood = 1458;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 90;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};


//2
class Gailun :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 4;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 750;//Ѫ��
			defense_wuli = 45;//�������
			defense_fashu = 45;//ħ������
			attack_wuli = 55;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 40;//��ʼ����ֵ
			mana_max = 90;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1350;//Ѫ��
			defense_wuli = 45;//�������
			defense_fashu = 45;//ħ������
			attack_wuli = 83;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 40;//��ʼ����ֵ
			mana_max = 90;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2430;//Ѫ��
			defense_wuli = 45;//�������
			defense_fashu = 45;//ħ������
			attack_wuli = 124;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 40;//��ʼ����ֵ
			mana_max = 90;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Jiakesi :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 5;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 750;//Ѫ��
			defense_wuli = 35;//�������
			defense_fashu = 35;//ħ������
			attack_wuli = 55;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.85;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 50;//��ʼ����ֵ
			mana_max = 120;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1350;//Ѫ��
			defense_wuli = 35;//�������
			defense_fashu = 35;//ħ������
			attack_wuli = 83;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.85;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 50;//��ʼ����ֵ
			mana_max = 120;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2430;//Ѫ��
			defense_wuli = 35;//�������
			defense_fashu = 35;//ħ������
			attack_wuli = 124;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.85;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 50;//��ʼ����ֵ
			mana_max = 120;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Gulajiasi :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 6;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 750;//Ѫ��
			defense_wuli = 45;//�������
			defense_fashu = 45;//ħ������
			attack_wuli = 50;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.6;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 40;//��ʼ����ֵ
			mana_max = 80;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1350;//Ѫ��
			defense_wuli = 45;//�������
			defense_fashu = 45;//ħ������
			attack_wuli = 75;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.6;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 40;//��ʼ����ֵ
			mana_max = 80;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2430;//Ѫ��
			defense_wuli = 45;//�������
			defense_fashu = 45;//ħ������
			attack_wuli = 113;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.6;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 40;//��ʼ����ֵ
			mana_max = 80;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};


//3

//class Modekaisa :public Hero
//{
//protected:
//	int mana_begin;//��ʼ����ֵ
//	int mana_max;//�����ֵ
//	int grade;
//public:
//	int index = 7;
//	// �����Ǽ����г�ʼ��
//	void infm_initialize(int level)
//	{
//		grade = level;
//		if (level == 1)
//		{
//			blood = 850;//Ѫ��
//			defense_wuli = 55;//�������
//			defense_fashu = 55;//ħ������
//			attack_wuli = 60;//������
//			attack_fashu = 100;//��ǿ
//			attack_speed = 0.65;//����
//			attack_distance = 1;//��������
//			baoji_rate = 25;//������
//			mana_begin = 70;//��ʼ����ֵ
//			mana_max = 120;//�����ֵ
//		}
//		if (level == 2)
//		{
//			blood = 1530;//Ѫ��
//			defense_wuli = 55;//�������
//			defense_fashu = 55;//ħ������
//			attack_wuli = 60;//������
//			attack_fashu = 100;//��ǿ
//			attack_speed = 0.65;//����
//			attack_distance = 1;//��������
//			baoji_rate = 25;//������
//			mana_begin = 70;//��ʼ����ֵ
//			mana_max = 120;//�����ֵ
//		}
//		if (level == 3)
//		{
//			blood = 2754;//Ѫ��
//			defense_wuli = 55;//�������
//			defense_fashu = 55;//ħ������
//			attack_wuli = 135;//������
//			attack_fashu = 100;//��ǿ
//			attack_speed = 0.65;//����
//			attack_distance = 1;//��������
//			baoji_rate = 25;//������
//			mana_begin = 70;//��ʼ����ֵ
//			mana_max = 120;//�����ֵ
//		}
//	}
//
//};

class Shamila :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;

	int judge_level = 0;
public:
	int index = 8;
	//�����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 600;//Ѫ��
			defense_wuli = 20;//�������
			defense_fashu = 20;//ħ������
			attack_wuli = 60;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 100;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1080;//Ѫ��
			defense_wuli = 20;//�������
			defense_fashu = 20;//ħ������
			attack_wuli = 90;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 100;//�����ֵ
		}
		if (level == 3)
		{
			blood = 1944;//Ѫ��
			defense_wuli = 20;//�������
			defense_fashu = 20;//ħ������
			attack_wuli = 135;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.7;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 100;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
				judge_level++;
			}
		}
	}
};

class Eyunxiaojie :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 9;
	//�����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 650;//Ѫ��
			defense_wuli = 20;//�������
			defense_fashu = 20;//ħ������
			attack_wuli = 60;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 60;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1170;//Ѫ��
			defense_wuli = 20;//�������
			defense_fashu = 20;//ħ������
			attack_wuli = 90;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 60;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2106;//Ѫ��
			defense_wuli = 20;//�������
			defense_fashu = 20;//ħ������
			attack_wuli = 124;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 60;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};


//4
class Ali : public Hero{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 10;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 700;//Ѫ��
			defense_wuli = 30;//�������
			defense_fashu = 30;//ħ������
			attack_wuli = 40;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 30;//�����ֵ
		}
		if (level == 2)
		{
			blood = 810;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 60;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
		if (level == 3)
		{
			blood = 1458;//Ѫ��
			defense_wuli = 15;//�������
			defense_fashu = 15;//ħ������
			attack_wuli = 90;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.75;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 15;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Kaitelin :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 11;
	//�����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 700;//Ѫ��
			defense_wuli = 30;//�������
			defense_fashu = 30;//ħ������
			attack_wuli = 70;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 90;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1260;//Ѫ��
			defense_wuli = 30;//�������
			defense_fashu = 30;//ħ������
			attack_wuli = 105;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 90;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2268;//Ѫ��
			defense_wuli = 30;//�������
			defense_fashu = 30;//ħ������
			attack_wuli = 158;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 90;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Bulici :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 12;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 1000;//Ѫ��
			defense_wuli = 60;//�������
			defense_fashu = 60;//ħ������
			attack_wuli = 60;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.6;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 60;//��ʼ����ֵ
			mana_max = 120;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1800;//Ѫ��
			defense_wuli = 60;//�������
			defense_fashu = 60;//ħ������
			attack_wuli = 90;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.6;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 60;//��ʼ����ֵ
			mana_max = 120;//�����ֵ
		}
		if (level == 3)
		{
			blood = 3240;//Ѫ��
			defense_wuli = 60;//�������
			defense_fashu = 60;//ħ������
			attack_wuli = 135;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.6;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 60;//��ʼ����ֵ
			mana_max = 120;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

//5
class Qiyana :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 13;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 1000;//Ѫ��
			defense_wuli = 60;//�������
			defense_fashu = 60;//ħ������
			attack_wuli = 75;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.9;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 40;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1900;//Ѫ��
			defense_wuli = 60;//�������
			defense_fashu = 60;//ħ������
			attack_wuli = 120;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.9;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 40;//�����ֵ
		}
		if (level == 3)
		{
			blood = 7500;//Ѫ��
			defense_wuli = 60;//�������
			defense_fashu = 60;//ħ������
			attack_wuli = 170;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.9;//����
			attack_distance = 1;//��������
			baoji_rate = 25;//������
			mana_begin = 0;//��ʼ����ֵ
			mana_max = 40;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

class Zhadanren : public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 14;
	// �����Ǽ����г�ʼ��
	void infm_initialize(int level)
	{
		grade = level;
		if (level == 1)
		{
			blood = 800;//Ѫ��
			defense_wuli = 40;//�������
			defense_fashu = 40;//ħ������
			attack_wuli = 45;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 30;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
		if (level == 2)
		{
			blood = 1440;//Ѫ��
			defense_wuli = 40;//�������
			defense_fashu = 40;//ħ������
			attack_wuli = 68;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 30;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
		if (level == 3)
		{
			blood = 2592;//Ѫ��
			defense_wuli = 40;//�������
			defense_fashu = 40;//ħ������
			attack_wuli = 101;//������
			attack_fashu = 100;//��ǿ
			attack_speed = 0.8;//����
			attack_distance = 4;//��������
			baoji_rate = 25;//������
			mana_begin = 30;//��ʼ����ֵ
			mana_max = 75;//�����ֵ
		}
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
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
			//�����ж�
			if (mana_begin >= mana_max)
			{
				ability(grade, Hero);
				mana_begin -= mana_max;
			}
			else
			{
				//�չ��ظ�����ֵ
				mana_begin += 10;
				//����չ��˺�
				Hero.getdamage(attack_wuli - Hero.get_defense_wuli());
			}
		}
	}
};

//������
class Null :public Hero
{
protected:
	int mana_begin;//��ʼ����ֵ
	int mana_max;//�����ֵ
	int grade;
public:
	int index = 0;
	//�����Ǽ����г�ʼ��
	void infm_initialize()
	{
		blood = 0;//Ѫ��
		defense_wuli = 0;//�������
		defense_fashu = 0;//ħ������
		attack_wuli = 0;//������
		attack_fashu = 0;//��ǿ
		attack_speed = 0;//����
		attack_distance = 0;//��������
		baoji_rate = 0;//������
		mana_begin = 0;//��ʼ����ֵ
		mana_max = 0;//�����ֵ
	}
	void ability(int level, Hero& Hero)//����Ĳ����Ǽ��ܵȼ����ܵ��˺���Ŀ��
	{
		;
	}
	void attack(Hero& Hero)
	{
		;
	}
};



//��������////////////////////////////////////////////////////////////////////////////////////

//���в��ֺ���
//׼���׶����к���
//Board exe_run()
//{
//	Board me;
//	
//	//������������ʾ������һ������Hero_x
//	Hero Hero_x;
//	//���뱸ս���ж��Ƿ�����
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
//	//������������ʾ������һ������Hero_y
//	Hero Hero_y;
//	//��������
//	
//
//	//������������ʾ������һ�����ӵ�ս����
//	Hero Hero_z;
//	//�ŵ�ս����
//
//
//
//	//
//	return me;
//}

//��ս�׶����к���
int exe_fight(Board board1, Board enemy)//���ж�ս����
{
	// ����ѭ����
	//���ǹ������⣬�趨��Сʱ�䵥λ0.01s,ϣ��ʵ��û��0.01s����һ�����ݵĴ���ʹ���
	const std::chrono::milliseconds loopDuration(100);  // 100 ���� = 0.1 ��

	while (true) {
		auto startTime = std::chrono::steady_clock::now();
		//ȫ��ʱ������
		time_all = time_all + 0.1;
		// ִ��ѭ������
		//���¸�������
		board1.refresh();
		board1.find(enemy);
		//�ֶ��߳�ִ�й�������
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

		// ����ʵ��ִ��ʱ��
		auto endTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		// �ȴ�ʣ���ʱ��
		auto remainingTime = loopDuration - elapsedTime;
		if (remainingTime > std::chrono::milliseconds::zero()) {
			std::this_thread::sleep_for(remainingTime);
		}
	}

}//����ʤ�����



//�̺߳���
//�����ж�Ӣ�۴治���ڣ����ڽ�����һ��
//����ǰ������Χ����Ӣ�ۣ����й�����
//��û��Ӣ�ۣ��򳯾����Լ�����ĶԷ�Ӣ�۷����ƶ�һ�������������⣺�ƶ���Ҫ�ķ�ʱ��
void thread_action(Hero& Hero_my, Hero& Hero_enemy)
{
	
	//�����ҷ�Ӣ�ۡ���һ����ڣ��˴��ù���Ϊ����б�ʾ���������й���
	if (Hero_my.get_attack_speed() == 0)
	{
		return;
	}

	//���з�Ӣ�۲��ڷ�Χ�ڣ��ƶ�
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
		//����ʱ��ȫ��ʱ��ﵽ���ټ���������������й���
		if (divide_double(time_all, Hero_my.get_attack_speed()))
		{
			Hero_my.attack(Hero_enemy);
		}
	}
}

//������������
//���ڼ�������С��֮���ܲ��ܱ��������ܷ���true�����ܷ���false
//a��bС
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
	consequence = exe_fight(me, enemy);//����ս�������ܵз�������������ʾ�Եз���ɵ��˺��������򷵻ظ�������ʾ�ܵ����˺���
	return consequence;
}



