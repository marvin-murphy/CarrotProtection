#include "Monster.h"

extern int money;

bool Monster::monster_init(int type) {
    // 给 Monster 对象的属性赋值
    health = 10 + 5 * type; // 设置具体的血量值
    hit = 1 + type; // 设置具体的攻击力
    level = 1 + type;
    this->type = type; // 设置具体类型

    // 创建 Sprite 对象（根据type选择不同的图像文件）
    std::string spriteFileName = "monster" + std::to_string(type) + ".png";
    Sprite* mySprite = Sprite::create(spriteFileName);

    // 设置 Sprite 的位置等属性（根据实际需求进行调整）
    setPosition(Vec2(0, 0));  // 设置位置

    if (mySprite) {
        addChild(mySprite); // 将 Sprite 添加为 Monster 的子节点
        return true;
    }
    return false;
}

Monster* Monster::monster_create(int type) {
    Monster* my_monster = new Monster();
    if (my_monster->monster_init(type)) {
        my_monster->autorelease();
        return my_monster; // 返回创建的 Monster 对象
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
        die(); // 调用死亡处理
    }
    setHealth(health);
    return health > 0;
}

void Monster::die() {
    int type = getType();
    money += type; // 增加金币，假设 money 是全局变量
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
