#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"

USING_NS_CC;

class Monster : public cocos2d::Sprite {
public:
    // Monster类构造函数
    Monster(std::vector<Monster*>* monsters) : monstersPtr(monsters), health(15), level(1), type(1), hit(1) {}

    // 初始化方法声明
    bool monster_init(int type);

    // 生成方法声明
    Monster* Monster::monster_create(int type, std::vector<Monster*>* monstersContainer);

    void setMonstersContainer(std::vector<Monster*>* monsters) {
        monstersPtr = monsters;
    }

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

private:
    int health;
    int level;
    int type;
    int hit;
    std::vector<Monster*>* monstersPtr;
};

#endif
//外部创建方法
/*std::vector<Monster*> monstersContainer;
int monsterType = 1; // 假设有一个怪物类型标识符
Monster* newMonster = Monster::monster_create(monsterType, &monstersContainer);

if (newMonster) {
    // 如果有场景或父节点，还需要将怪物添加到其中
    // this->addChild(newMonster);
    // 可以在这里做其他设置或初始化工作
}
*/

