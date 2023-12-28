/*#include "monster_move.h"

bool monster_move::init() {
    if (!Monster::init()) {
        return false;
    }

    // 在这里可以初始化 monster_move 类的特定属性和动作
    // 例如，可以添加动画或其他移动逻辑

    return true;
}
void monster_move::updatePosition() {
    // 获取当前精灵的位置
    Vec2 currentPosition = this->getPosition();

    // 更新类内部的x和y值
    x = currentPosition.x;
    y = currentPosition.y;

    // 可以在这里打印出或者以其他方式使用新的坐标
}
void monster_move::startMoving(int speed) {

    float speedFactor = 1.2f - 0.2f * speed;

    // 限制 speedFactor 的取值在 0.2 到 1.2 之间
    speedFactor = std::max(0.4f, std::min(1.2f, speedFactor));

    // 假设monster的起始位置已经在 (135, 135)
    // 创建一个动作序列，按路径点依次移动

    auto move1 = MoveBy::create(2 / speedFactor, Vec2(180, 0));// 从(135,135)到(315,135)
    auto move2 = MoveBy::create(4 / speedFactor, Vec2(0, 370)); // 从(315,135)到(315,505)
    auto move3 = MoveBy::create(6 / speedFactor, Vec2(540, 0));// 从(315,505)到(855,505)
    auto move4 = MoveBy::create(4 / speedFactor, Vec2(0, -370)); // 从(855,505)到(855,135)
    auto move5 = MoveBy::create(2 / speedFactor, Vec2(190, 0)); // 从(855,135)到(1045,135)

    // 将所有动作串联成一个序列
    auto sequence = Sequence::create(move1, move2, move3, move4, move5,
        CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)),
        nullptr);

    // 执行动作序列
    this->runAction(sequence);
    //外部调用方法
    // 调用startMoving函数，开始移动怪物
    //myMonster->startMoving();
}

/*void monster_move::move(path* path) {
    if (!path) {
        return;
    }

    int pointCount = path->getPointCount();
    for (int i = 0; i < pointCount; i++) {
        PathPoint point = path->getPointAtIndex(i);
        // 根据点的位置来移动怪物
        // 使用 Cocos2d-x 的动作来实现移动，如 MoveTo、MoveBy 等
    }
}*/
/*
void monster_move::moveLeft(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(-10, 0)); // 向左移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void monster_move::moveRight(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(10, 0)); // 向右移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void monster_move::moveUp(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, 10)); // 向上移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void monster_move::moveDown(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, -10)); // 向下移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}
*/


