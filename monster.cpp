#include "Monster.h"

extern int money;

bool Monster::monster_init(int type) {
    // �� Monster ��������Ը�ֵ
    health = 10 + 5 * type; // ���þ����Ѫ��ֵ
    hit = 1 + type; // ���þ���Ĺ�����
    level = 1 + type;
    this->type = type; // ���þ�������

    // ���� Sprite ���󣨸���typeѡ��ͬ��ͼ���ļ���
    std::string spriteFileName = "monster" + std::to_string(type) + ".png";
    Sprite* mySprite = Sprite::create(spriteFileName);

    // ���� Sprite ��λ�õ����ԣ�����ʵ��������е�����
    setPosition(Vec2(135, 135));  // ����λ��

    if (mySprite) {
        addChild(mySprite); // �� Sprite ���Ϊ Monster ���ӽڵ�
        return true;
    }
    return false;
}

Monster* Monster::monster_create(int type, std::vector<Monster*>* monstersContainer) {
    // �ڴ���Monsterʱ������monstersContainer
    Monster* my_monster = new Monster(monstersContainer);
    if (my_monster->monster_init(type)) {
        my_monster->autorelease();
        // ����б�Ҫ�����������ｫ������ӵ�������
        if (monstersContainer) {
            monstersContainer->push_back(my_monster);
        }
        return my_monster; // ���ش����� Monster ����
    }
    else {
        CC_SAFE_DELETE(my_monster);
        return nullptr;
    }
}

bool Monster::health_decrease(int num) {
    int health = getHealth();
    health -= num;
    if (health <= 0) {
        health = 0;
        die(); // ������������
    }
    setHealth(health);
    return health > 0;
}

void Monster::die() {

    // ȷ������Ч������ָ��
    if (monstersPtr) {
        auto& container = *monstersPtr;  // �������Լ򻯷���
        auto it = std::find(container.begin(), container.end(), this);
        if (it != container.end()) {
            container.erase(it);  // ��������ɾ���Լ�
        }
    }

    // ִ������������...
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);

    int type = getType();
    money += 10 * type; // ���ӽ�ң����� money ��ȫ�ֱ���
}

void Monster::updatePosition() {
    // ��ȡ��ǰ�����λ��
    Vec2 currentPosition = this->getPosition();

    // �������ڲ���x��yֵ
    x = currentPosition.x;
    y = currentPosition.y;

    // �����������ӡ��������������ʽʹ���µ�����
}
void Monster::startMoving(int speed) {

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
        CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)),
        nullptr);

    // ִ�ж�������
    this->runAction(sequence);
    //�ⲿ���÷���
    // ����startMoving��������ʼ�ƶ�����
    //myMonster->startMoving();
}

void Monster::moveLeft(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(-10, 0)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void Monster::moveRight(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(10, 0)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void Monster::moveUp(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, 10)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void Monster::moveDown(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, -10)); // �����ƶ�
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}
int Monster::getHealth() const {
    return health;
}

void Monster::setHealth(int value) {
    health = value;
}

int Monster::getLevel() const {
    return level;
}

void Monster::setLevel(int value) {
    level = value;
}

int Monster::getType() const {
    return type;
}

void Monster::setType(int value) {
    type = value;
}

int Monster::getHit() const {
    return hit;
}

void Monster::setHit(int value) {
    hit = value;
}
