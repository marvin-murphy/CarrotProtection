#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"

USING_NS_CC;

class Monster : public cocos2d::Sprite {
public:
    // ��ʼ����������
    bool monster_init(int type);

    // ���ɷ�������
    static Monster* monster_create(int type);

    // Ѫ�����ٷ�������
    bool health_decrease(int num);

    // ��ȡѪ���ķ���
    int getHealth() const;

    // ����Ѫ���ķ���
    void setHealth(int value);

    // ��ȡ�ȼ��ķ���
    int getLevel() const;

    // ���õȼ��ķ���
    void setLevel(int value);

    // ��ȡ���͵ķ���
    int getType() const;

    // �������͵ķ���
    void setType(int value);

    // ��ȡ�������ķ���
    int getHit() const;

    // ���ù������ķ���
    void setHit(int value);

    void die();

    CREATE_FUNC(Monster);//Monster* myMonster = Monster::create(type);

private:
    int health;
    int level;
    int type;
    int hit;
};

#endif

