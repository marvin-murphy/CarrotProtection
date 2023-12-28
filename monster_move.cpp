/*#include "monster_move.h"

bool monster_move::init() {
    if (!Monster::init()) {
        return false;
    }

    // ��������Գ�ʼ�� monster_move ����ض����ԺͶ���
    // ���磬������Ӷ����������ƶ��߼�

    return true;
}
void monster_move::updatePosition() {
    // ��ȡ��ǰ�����λ��
    Vec2 currentPosition = this->getPosition();

    // �������ڲ���x��yֵ
    x = currentPosition.x;
    y = currentPosition.y;

    // �����������ӡ��������������ʽʹ���µ�����
}
void monster_move::startMoving(int speed) {

    float speedFactor = 1.2f - 0.2f * speed;

    // ���� speedFactor ��ȡֵ�� 0.2 �� 1.2 ֮��
    speedFactor = std::max(0.4f, std::min(1.2f, speedFactor));

    // ����monster����ʼλ���Ѿ��� (135, 135)
    // ����һ���������У���·���������ƶ�

    auto move1 = MoveBy::create(2 / speedFactor, Vec2(180, 0));// ��(135,135)��(315,135)
    auto move2 = MoveBy::create(4 / speedFactor, Vec2(0, 370)); // ��(315,135)��(315,505)
    auto move3 = MoveBy::create(6 / speedFactor, Vec2(540, 0));// ��(315,505)��(855,505)
    auto move4 = MoveBy::create(4 / speedFactor, Vec2(0, -370)); // ��(855,505)��(855,135)
    auto move5 = MoveBy::create(2 / speedFactor, Vec2(190, 0)); // ��(855,135)��(1045,135)

    // �����ж���������һ������
    auto sequence = Sequence::create(move1, move2, move3, move4, move5,
        CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)),
        nullptr);

    // ִ�ж�������
    this->runAction(sequence);
    //�ⲿ���÷���
    // ����startMoving��������ʼ�ƶ�����
    //myMonster->startMoving();
}

/*void monster_move::move(path* path) {
    if (!path) {
        return;
    }

    int pointCount = path->getPointCount();
    for (int i = 0; i < pointCount; i++) {
        PathPoint point = path->getPointAtIndex(i);
        // ���ݵ��λ�����ƶ�����
        // ʹ�� Cocos2d-x �Ķ�����ʵ���ƶ����� MoveTo��MoveBy ��
    }
}*/
/*
void monster_move::moveLeft(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(-10, 0)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void monster_move::moveRight(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(10, 0)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void monster_move::moveUp(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, 10)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void monster_move::moveDown(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, -10)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(monster_move::updatePosition, this)), nullptr);
    this->runAction(sequence);
}
*/


