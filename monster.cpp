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
    setPosition(Vec2(180, 510));  // 设置位置

    if (mySprite) {
        addChild(mySprite); // 将 Sprite 添加为 Monster 的子节点
        return true;
    }
    return false;
}

Monster* Monster::monster_create(int type,Carrot*carrot, std::vector<Monster*>* monstersContainer) {
    // 在创建Monster时，传递monstersContainer
    Monster* my_monster = new Monster(monstersContainer, carrot);
    if (my_monster->monster_init(type)) {
        my_monster->autorelease();
        // 如果有必要，可以在这里将怪物添加到容器中
        if (monstersContainer) {
            monstersContainer->push_back(my_monster);
        }
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

void Monster::onReachedDestination() {
    // 减少萝卜的生命值
    if (carrotPtr) {
        bool alive = carrotPtr->health_decrease(hit);

        if (!alive) {
            // 如果萝卜生命值耗尽，执行游戏结束逻辑
        }
    }

    // 怪物到达终点后自我销毁
    this->die();
}

void Monster::die() {

    // 创建并显示击杀效果
    cocos2d::Sprite* hitEffect = cocos2d::Sprite::create("monster_die.png");
    if (hitEffect) {
        hitEffect->setPosition(this->getPosition()); // 设置为子弹击中的位置
        this->getParent()->addChild(hitEffect);

        // 设置淡出时间
        float duration = 0.5f;

        // 创建淡出动作并在完成后删除精灵
        auto fadeOutAndRemove = cocos2d::Sequence::create(
            cocos2d::FadeOut::create(duration), // 淡出动作
            cocos2d::RemoveSelf::create(),      // 完成后删除自己
            nullptr);

        // 运行动作
        hitEffect->runAction(fadeOutAndRemove);
    }
    state = State::Dead; // 更新状态

    // 确保有有效的容器指针
    if (monstersPtr) {
        auto& container = *monstersPtr;  // 解引用以简化访问
        auto it = std::find(container.begin(), container.end(), this);
        if (it != container.end()) {
            container.erase(it);  // 从容器中删除自己
        }
    }

    // 执行其他清理工作...
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
    parentLayer->notifyMonsterDeath();

    int type = getType();
    money += 10 * type; // 增加金币，假设 money 是全局变量
}

/*void Monster::updatePosition() {
    // 获取当前精灵的位置
    Vec2 currentPosition = this->getPosition();

    // 更新类内部的x和y值
    x = currentPosition.x;
    y = currentPosition.y;

    // 可以在这里打印出或者以其他方式使用新的坐标
}
*/
void Monster::startMoving(int speed) {
    float speedFactor = 1.2f - 0.2f * speed;

    // 限制 speedFactor 的取值在 0.2 到 1.2 之间
    speedFactor = std::max(0.4f, std::min(1.2f, speedFactor));

    // 设置初始位置
    this->setPosition(Vec2(180, 510)); // 设置monster的起始位置

    // 创建一个动作序列，按照新的路径点移动
    auto move1 = MoveTo::create(2 / speedFactor, Vec2(330, 510)); // 到拐点1
    auto move2 = MoveTo::create(4 / speedFactor, Vec2(330, 210)); // 到拐点2
    auto move3 = MoveTo::create(6 / speedFactor, Vec2(780, 210)); // 到拐点3
    auto move4 = MoveTo::create(4 / speedFactor, Vec2(780, 510)); // 到拐点4
    auto move5 = MoveTo::create(2 / speedFactor, Vec2(930, 510)); // 到终点

    // 最后一个移动动作后的回调
    auto callback = CallFunc::create(CC_CALLBACK_0(Monster::onReachedDestination, this));

    // 将所有动作和回调串联成一个序列
    auto sequence = Sequence::create(move1, move2, move3, move4, move5, callback, nullptr);

    // 执行动作序列
    this->runAction(sequence);
}

void Monster::updateHealthLabel() {
    if (healthLabel) {
        std::string labelText = "Health: " + std::to_string(health);
        healthLabel->setString(labelText); // 更新标签文本为当前血量
    }
}

void Monster::update(float dt) {
    // 调用父类的update方法
    cocos2d::Sprite::update(dt);

    // 在这里可以添加额外的逻辑，如果有必要的话

    // 比如，如果怪物的移动方式使得标签需要特别调整位置，可以在这里实现
}


/*void Monster::moveLeft(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(-10, 0)); // 向左移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void Monster::moveRight(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(10, 0)); // 向右移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void Monster::moveUp(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, 10)); // 向上移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}

void Monster::moveDown(float duration) {
    auto moveBy = MoveBy::create(duration, Vec2(0, -10)); // 向下移动
    auto sequence = Sequence::create(moveBy, CallFunc::create(CC_CALLBACK_0(Monster::updatePosition, this)), nullptr);
    this->runAction(sequence);
}
*/
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
