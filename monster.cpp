#include "monster.h"

bool Monster:: monster_init(int type)
{
	//����Monster����
	Monster my_monster;

	// ���� Sprite ����
	Sprite* mySprite = Sprite::create("mysprite.png");//��type�йأ���δ�޸�

    if (mySprite) {
        // �� Carrot ��������Ը�ֵ
        my_monster.setHealth(10 + 5 * type); // ���þ����Ѫ��ֵ
        my_monster.setHit(1 + type); // ���þ���Ĺ�����
        my_monster.setLevel(1 + type);   // ���þ���ĵȼ�ֵ
        return 0;
    }
    return 1;
}
Monster* Monster::monster_create(int type)
{
    Monster *my_monster = new Monster();
    if (my_monster->monster_init(type))
    {
        my_monster->autorelease();
        return my_monster; // ���ش����� Monster ����
    }
    else
    {
        delete my_monster;
        return NULL;
    }
}
bool health_decrease(int num)
{
    Monster my_monster;
    int health = my_monster.getHealth();
    health = health - num;
    if (health < 0)
        return 0;
    else
    {
        my_monster.setHealth(health);
        return 1;
    }
}