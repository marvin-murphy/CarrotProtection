#ifndef MONSTER_MOVE_H
#define MONSTER_MOVE_H

#include "Monster.h" // 包含基类 Monster 的头文件
#include "path.h"

class monster_move : public Monster {
public:
    monster_move() : x(0), y(0) {}
    bool init() override;
    void move(path* path); // 添加移动方法
    // 移动函数
    void moveLeft(float duration);
    void moveRight(float duration);
    void moveUp(float duration);
    void moveDown(float duration);
    void startMoving();
    void updatePosition();
    int monster_move::getX() const {
        return x;
    }

    void monster_move::setX(int value) {
        x = value;
    }
    int monster_move::getY() const {
        return y;
    }

    void monster_move::setY(int value) {
        y = value;
    }

    CREATE_FUNC(monster_move);

    //monster_move* myMonster = monster_move::create();
   // myMonster->move(); // 调用移动方法，使怪物动起来
    

private:
    int x;
    int y;
};

#endif


