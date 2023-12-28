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
    setPosition(Vec2(0, 0));  // ����λ��

    if (mySprite) {
        addChild(mySprite); // �� Sprite ���Ϊ Monster ���ӽڵ�
        return true;
    }
    return false;
}

Monster* Monster::monster_create(int type) {
    Monster* my_monster = new Monster();
    if (my_monster->monster_init(type)) {
        my_monster->autorelease();
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
    int type = getType();
    money += type; // ���ӽ�ң����� money ��ȫ�ֱ���
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
