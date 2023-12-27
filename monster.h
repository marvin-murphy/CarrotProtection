#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"

USING_NS_CC;

class Monster : public cocos2d::Sprite {
public:
    // 初始化方法声明
    bool monster_init(int type);

    // 生成方法声明
    static Monster* monster_create(int type);

    // 血量减少方法声明
    bool health_decrease(int num);

    // 获取血量的方法
    int getHealth() const;

    // 设置血量的方法
    void setHealth(int value);

    // 获取等级的方法
    int getLevel() const;

    // 设置等级的方法
    void setLevel(int value);

    // 获取类型的方法
    int getType() const;

    // 设置类型的方法
    void setType(int value);

    // 获取攻击力的方法
    int getHit() const;

    // 设置攻击力的方法
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

