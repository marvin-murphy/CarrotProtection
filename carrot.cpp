#include "carrot.h"

bool Carrot::carrot_init()
{
    // ���� Carrot ����
    Carrot myCarrot;

    // ���� Sprite ����
    Sprite* mySprite = Sprite::create("mysprite.png");

    if (mySprite) {
        // �� Carrot ��������Ը�ֵ
        myCarrot.setHealth(10); // ���þ����Ѫ��ֵ
        myCarrot.setLevel(1);   // ���þ���ĵȼ�ֵ
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
        return mycarrot; // ���ش����� Carrot ����
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


