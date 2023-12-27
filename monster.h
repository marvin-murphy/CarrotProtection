#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"

#define MONSTER_LEVEL 4

USING_NS_CC;
class Monster : public cocos2d::Sprite
{
    // ���������� health �� level��type��hit ���Ե� getter �� setter ����
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, level, Level);
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(int, hit, Hit);

    // ��ʼ����������
    bool monster_init(int type);

    // ���ɷ�������
    Monster* monster_create(int type);

    // Ѫ�����ٷ�������
    bool health_decrease(int num);
};
#endif

