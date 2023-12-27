#ifndef MY_CARROT_H
#define MY_CARROT_H

#include "cocos2d.h"

#define CARROT_LEVEL 3

USING_NS_CC;

class Carrot : public cocos2d::Sprite {
public:
    Carrot(); // 构造函数

    // 初始化方法声明
    bool init() override;

    // 生成方法声明
    static Carrot* create();

    // 升级方法声明
    bool if_upgrade();

    // 血量减少方法声明
    bool health_decrease(int num);

    // 获取血量和等级的方法
    int getHealth() const { return health; }
    int getLevel() const { return level; }

    CREATE_FUNC(Carrot); //Carrot* myCarrot = Carrot::create();

private:
    int health;
    int level;
    
};

#endif

