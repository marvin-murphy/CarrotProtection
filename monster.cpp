#include "monster.h"

bool Monster:: monster_init(int type)
{
	//创建Monster对象
	Monster my_monster;

	// 创建 Sprite 对象
	Sprite* mySprite = Sprite::create("mysprite.png");//与type有关，还未修改

    if (mySprite) {
        // 给 Carrot 对象的属性赋值
        my_monster.setHealth(10 + 5 * type); // 设置具体的血量值
        my_monster.setHit(1 + type); // 设置具体的攻击力
        my_monster.setLevel(1 + type);   // 设置具体的等级值
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
        return my_monster; // 返回创建的 Monster 对象
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