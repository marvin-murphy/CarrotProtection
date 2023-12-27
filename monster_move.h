#ifndef MONSTER_MOVE_H
#define MONSTER_MOVE_H

#include "Monster.h" // �������� Monster ��ͷ�ļ�
#include "path.h"

class monster_move : public Monster {
public:
    monster_move() : x(0), y(0) {}
    bool init() override;
    void move(path* path); // ����ƶ�����
    // �ƶ�����
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
   // myMonster->move(); // �����ƶ�������ʹ���ﶯ����
    

private:
    int x;
    int y;
};

#endif


