#ifndef MY_CARROT_H
#define MY_CARROT_H

#include "cocos2d.h"

#define CARROT_LEVEL 4

USING_NS_CC;

class Carrot : public cocos2d::Sprite {
public:
    virtual ~Carrot() {};

    // ���������� health �� level ���Ե� getter �� setter ����
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, level, Level);

    // ��ʼ����������
    bool carrot_init();

    // ��̬������������
    Carrot* carrot_create();

    // ������������
    bool if_upgrate(int& money);

    // Ѫ�����ٷ�������
    bool health_decrease(int num);
};

#endif

