#ifndef MY_CARROT_H
#define MY_CARROT_H

#include "cocos2d.h"

#define CARROT_LEVEL 4

USING_NS_CC;

class Carrot : public cocos2d::Sprite {
public:
    virtual ~Carrot() {};

    // 声明并生成 health 和 level 属性的 getter 和 setter 方法
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, level, Level);

    // 初始化方法声明
    bool carrot_init();

    // 静态工厂方法声明
    Carrot* carrot_create();

    // 升级方法声明
    bool if_upgrate(int& money);

    // 血量减少方法声明
    bool health_decrease(int num);
};

#endif

