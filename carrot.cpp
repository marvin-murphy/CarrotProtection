#include "carrot.h"

bool Carrot::carrot_init()
{
    // 创建 Carrot 对象
    Carrot myCarrot;

    // 创建 Sprite 对象
    Sprite* mySprite = Sprite::create("mysprite.png");

    if (mySprite) {
        // 给 Carrot 对象的属性赋值
        myCarrot.setHealth(10); // 设置具体的血量值
        myCarrot.setLevel(1);   // 设置具体的等级值
        return 0;
    }
    return 1;
}

Carrot* Carrot::carrot_create()
{
    Carrot* mycarrot = new Carrot();
    if (!mycarrot->carrot_init())
    {
        mycarrot->autorelease();
        return mycarrot; // 返回创建的 Carrot 对象
    }
    else
    {
        delete mycarrot;
        return NULL;
    }
}

bool Carrot::if_upgrate(int& money)
{
    Carrot myCarrot;
    int level = myCarrot.getLevel();
    int health = myCarrot.getHealth();
    if (money - 20 * level >= 0 && level <= CARROT_LEVEL)
    {
        money = money - 20 * level;
        myCarrot.setLevel(level + 1);
        myCarrot.setHealth(health + 5);
    }
}

bool Carrot::health_decrease(int num)
{
    Carrot myCarrot;
    int health = myCarrot.getHealth();
    health = health - num;
    if (health < 0)
        return 0;
    else
    {
        myCarrot.setHealth(health);
        return 1;
    }
}


