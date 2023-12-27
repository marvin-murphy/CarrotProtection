#ifndef MY_CARROT_H
#define MY_CARROT_H

#include "cocos2d.h"

#define CARROT_LEVEL 3

USING_NS_CC;

class Carrot : public cocos2d::Sprite {
public:
    Carrot(); // ���캯��

    // ��ʼ����������
    bool init() override;

    // ���ɷ�������
    static Carrot* create();

    // ������������
    bool if_upgrade();

    // Ѫ�����ٷ�������
    bool health_decrease(int num);

    // ��ȡѪ���͵ȼ��ķ���
    int getHealth() const { return health; }
    int getLevel() const { return level; }

    CREATE_FUNC(Carrot); //Carrot* myCarrot = Carrot::create();

private:
    int health;
    int level;
    
};

#endif

