#ifndef _MOVE_H_
#define _MOVE_H_
#include "cocos2d.h"
#include "Bullet.h"
#include "Tower.h"
#include "Carrot.h"
#include "Monster.h"

class GameLayer : public cocos2d::Layer {
private:
    int monstersCreated; // 记录已创建的Monster数量

    int totalMonstersToCreate; // 总共要创建的怪物数量

    std::vector<Monster*> monstersContainer; // 存储Monster对象

    Carrot* myCarrot; // 已经创建和初始化的Carrot对象

    std::vector<Tower*> towersContainer; // 存储Tower对象

public:
    GameLayer::GameLayer() {
        // 初始化myCarrot
        myCarrot = Carrot::create();

        // 初始化其他成员变量
        monstersCreated = 0;
        // ...其他初始化代码...
        this->scheduleUpdate();  // 安排GameLayer自身的更新
    }

    GameLayer::~GameLayer() {
        for (Monster* monster : monstersContainer) {
            monster->parentLayer = nullptr;  // 清除Monster对GameLayer的引用
            // 可能还需要做其他清理工作，如停止动作等
        }
        // ... 清理GameLayer自身的资源 ...
    }

    void createMonster(float dt, int type, int totalMonsters); // 添加参数

    void startCreatingMonsters(int type, int totalMonsters); // 用于开始创建怪物的方法

    bool allMonstersDead();

    void notifyMonsterDeath();

    void createTower(int type, const cocos2d::Vec2& touchlocation);

    void onPlayerTouch(const cocos2d::Vec2& location);

    void update(float dt);
};
#endif
// 假设你在某个地方调用这个方法
//gameLayer->startCreatingMonsters(1, 20); // 例如，创建20个类型为1的怪物


