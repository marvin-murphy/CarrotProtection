#include "Tower.h"

extern int money;


bool Tower::Tower_init(int type, const cocos2d::Vec2& touchlocation) {
    level = 1;
    attack_damage = 2;
    attack_range = 100;
    attack_speed = 1;
    slow_level = (type == 1) ? 1 : 2;

    spriteFileName = "tower" + std::to_string(type) + "_" + std::to_string(level) + ".png";
    Sprite* mySprite = Sprite::create(spriteFileName);
    setPosition(touchlocation);

    if (mySprite) {
        addChild(mySprite);
        return true;
    }
    return false;
}


Tower* Tower::Tower_create(int type, const cocos2d::Vec2& touchlocation, std::vector<Monster*>* monstersContainer, std::vector<Tower*>* towersContainer) {
    Tower* myTower = new Tower(monstersContainer, towersContainer);
    if (myTower && myTower->Tower_init(type, touchlocation)) {
        myTower->autorelease();
        if (towersContainer) {
            towersContainer->push_back(myTower);
        }
        return myTower;
    }
    else {
        CC_SAFE_DELETE(myTower);
        return nullptr;
    }
}


void Tower::shootBulletAtMonster(Monster* target) {
    // 获取塔和目标的位置
    cocos2d::Vec2 startPosition = this->getPosition();
    cocos2d::Vec2 targetPosition = target->getPosition();

    // 定义子弹的其他属性，比如图像、伤害、速度等
    // 使用字符串拼接
        std::string spriteFileName = "bullet_" + std::to_string(type) + "_" + std::to_string(level) + ".png";
    int damage = this->attack_damage; // 使用塔的攻击伤害
    float speed = 200.0 * attack_speed; // 子弹速度，可以根据塔的属性调整

    // 使用Bullet::create创建子弹
    Bullet* bullet = Bullet::create(startPosition, target, spriteFileName, damage, speed, &bullets);
    if (bullet) {
        // 将子弹添加到游戏世界中
        this->getParent()->addChild(bullet);
        // 启动子弹的其他逻辑或动画
        bullet->startMoving(targetPosition, speed);
    }
}

void Tower::removeTower()
{

    // 可以在删除节点之前先释放与炮塔相关的资源
    Sprite* mySprite = dynamic_cast<Sprite*>(this); // 假设this就是Sprite对象
    if (mySprite)
    {
        // 计算并添加金币，假设 money 是全局变量或某种形式的资源管理器中的变量
        money += 0.6 * (20 * type + 140 * level + 20 * level * level);
        mySprite->removeFromParentAndCleanup(true); // 删除并清理
    }

    // 从父节点中移除炮塔节点，并释放内存
    removeFromParentAndCleanup(true);

    // 从容器中移除自己
    if (towersPtr) {
        auto& container = *towersPtr;
        auto it = std::find(container.begin(), container.end(), this);
        if (it != container.end()) {
            container.erase(it);
        }
    }
    // 可以添加其他清理逻辑，比如额外的资源释放等
}
/*
// 创建一个Tower对象
Tower* myTower = new Tower(); // 或者任何创建Tower对象的方式

// 在某个事件或条件触发时
// 例如，玩家选择卖出塔或游戏需要清理塔
myTower->removeTower();  // 调用removeTower方法
*/

Monster* Tower::getNearestTarget(std::vector<Monster*>& monsters) {
    Monster* nearestTarget = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();

    for (Monster* target : monsters) {
        float distance = getPosition().distance(target->getPosition());

        if (distance < nearestDistance) {
            nearestDistance = distance;
            nearestTarget = target;
        }
    }

    return nearestTarget;
}



//当执行for (Node* target : possibleTargets)时，
    //这个循环在内部使用了possibleTargets的迭代器来遍历所有的元素。
    //范围基于的for循环是C++11引入的，它抽象了迭代器的复杂性，使得代码更清晰易读，
    //但实质上它是通过迭代器来访问和遍历容器的。
//getNearestTarget函数调用示例
/*
// 创建一个 Vector 对象
Vector<Node*> monsters;

// 添加怪物节点到 Vector 中
monsters.pushBack(monsterNode1);
monsters.pushBack(monsterNode2);
// 添加更多怪物节点...

// 获取炮塔最近的目标
Node* nearestTarget = myTower->getNearestTarget(monsters);
*/

void Tower::upgradeTower()
{
    // 根据需要更新炮塔的属性，这里只是示例
    if (money - (20 * type + 140 * level + 20 * level * level) >= 0 && level < TOWER_LEVEL)
    {
        money -= 20 * type + 140 * level + 20 * level * level;
        level++;
    }
    attack_damage += 2;
    attack_range += 50;
    attack_speed += 1;

    if (type != 1)
        slow_level++;

    // 构造新的图片文件路径
    std::string newSpriteFileName = "tower" + std::to_string(type) + "_" + std::to_string(level) + ".png";

    // 如果新路径和旧路径不同，才进行更新
    if (newSpriteFileName != spriteFileName)
    {
        // 获取名为 spriteFileName 的子节点
        Sprite* mySprite = dynamic_cast<Sprite*>(getChildByName(spriteFileName));

        // 如果存在，就将其移除
        if (mySprite)
        {
            removeChild(mySprite, true);
        }

        // 设置新的图片文件路径
        spriteFileName = newSpriteFileName;

        // 创建新的 Sprite 对象
        mySprite = Sprite::create(spriteFileName);

        // 将 Sprite 添加为 Tower 的子节点
        if (mySprite)
        {
            mySprite->setName(spriteFileName); // 设置子节点的名字与图片名字相同
            addChild(mySprite);
        }
    }
}

void Tower::rotateToTarget(Node* target)
{
    float rotationSpeed = 45.0f;;   // 旋转速度
    if (target)
    {
        Vec2 direction = target->getPosition() - getPosition();
        float targetRotation = CC_RADIANS_TO_DEGREES(direction.getAngle());

        // 创建 RotateTo 动作，实现匀速旋转
        RotateTo* rotateAction = RotateTo::create(1.0f / rotationSpeed, targetRotation);

        // 运行动作
        runAction(rotateAction);
    }
}

void Tower::updateTower(float dt) {
    // 更新自上次攻击以来经过的时间
    timeSinceLastAttack += dt;

    if (monstersPtr && !monstersPtr->empty() && timeSinceLastAttack >= attackInterval) {
        // 获取最近的目标
        Monster* nearestTarget = dynamic_cast<Monster*>(getNearestTarget(*monstersPtr));

        // 如果存在最近的目标，旋转并攻击
        if (nearestTarget) {
            rotateToTarget(nearestTarget);
            shootBulletAtMonster(nearestTarget);

            // 重置计时器
            timeSinceLastAttack = 0.0f;
        }
    }
}



/*
void Tower::extractTypeInfo() {
    // 获取文件名
    std::string fileName = this->getTexture()->getPath();

    // 解析文件名，假设文件名格式为 "tower{type}_{level}.png"
    size_t startPos = fileName.find("tower") + 5; // 找到 "tower" 后的位置
    size_t endPos = fileName.find("_"); // 找到 "_" 的位置
    if (startPos != std::string::npos && endPos != std::string::npos) {
        // 从字符串中提取 type
        type = std::stoi(fileName.substr(startPos, endPos - startPos));

        // 从字符串中提取 level
        startPos = endPos + 1;
        endPos = fileName.find(".png");
        if (startPos != std::string::npos && endPos != std::string::npos) {
            level = std::stoi(fileName.substr(startPos, endPos - startPos));
        }
    }
}
*/
