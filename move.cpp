#include "move.h"
void GameLayer::createMonster(float dt, int type, int totalMonsters)
{
    if (monstersCreated < totalMonsters) 
    {
        Monster* newMonster = Monster::monster_create(type, myCarrot, &monstersContainer);
        if (newMonster) {
            // 将新怪物添加到游戏层或场景中
            newMonster->parentLayer = this; // 设置parentLayer
            this->addChild(newMonster);

            // 安排新怪物在0.5秒后开始移动
            newMonster->scheduleOnce(
                [newMonster](float dt) { // Lambda表达式开始
                    newMonster->startMoving(1); // 在Lambda内调用startMoving方法
                }, // Lambda表达式结束
                0.5f, // 延迟0.5秒后执行
                    "start_moving_schedule" // 调度任务的标识字符串
                    );
        }
        monstersCreated++;
    }
    else {
        // 使用任务的键来取消调度
        this->unschedule("monster_creation_scheduler");
    }
}
void GameLayer::startCreatingMonsters(int type, int totalMonsters)
{
    this->schedule([=](float dt) {
        this->createMonster(dt, type, totalMonsters);
        }, 1.0f, "monster_creation_scheduler");
}

void GameLayer::notifyMonsterDeath() {
    if (allMonstersDead()) {
        // 所有怪物都死了，开始下一轮生成或者其他逻辑
        //startCreatingMonsters(nextMonsterType, nextTotalMonsters);
    }
}

bool GameLayer::allMonstersDead() {
    for (auto monster : monstersContainer) {
        if (monster->state == Monster::State::Alive) {
            return false; // 发现至少一个怪物还活着
        }
    }
    return true; // 所有怪物都死了
}

void GameLayer::onPlayerTouch(const cocos2d::Vec2& location) {
    // 假设玩家触摸位置就是放置塔的位置
    // 并且你已经有了塔的类型
    int towerType = 1; // 塔的类型，根据游戏逻辑确定

    createTower(towerType, location);
}

void GameLayer::createTower(int type, const cocos2d::Vec2& touchlocation) {
    // 假设monstersContainer和towersContainer已经在GameLayer中定义为成员变量
    Tower* newTower = Tower::Tower_create(type, touchlocation, &monstersContainer, &towersContainer);

    if (newTower) {
        // 塔创建成功，已经在 Tower::Tower_create 中添加到容器
        this->addChild(newTower); // 将塔添加到游戏场景中
        // ... 其他设置和逻辑 ...
    }
}


void GameLayer::update(float dt) {
    // 遍历所有塔并更新它们
    for (Tower* tower : towersContainer) {
        tower->updateTower(dt);
    }
    // ... 可能的其他更新逻辑 ...
}
