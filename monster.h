#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"

#define MONSTER_LEVEL 4

USING_NS_CC;
class Monster : public cocos2d::Sprite
{
    // 声明并生成 health 、 level、type、hit 属性的 getter 和 setter 方法
    CC_SYNTHESIZE(int, health, Health);
    CC_SYNTHESIZE(int, level, Level);
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(int, hit, Hit);

    // 初始化方法声明
    bool monster_init(int type);

    // 生成方法声明
    Monster* monster_create(int type);

    // 血量减少方法声明
    bool health_decrease(int num);
};
#endif

