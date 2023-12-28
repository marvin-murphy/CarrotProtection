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
