#include "Tower.h"

extern int money;

bool Tower ::Tower_init(int type, const cocos2d::Vec2& touchlocation)
{
	level = 1;
	attack_damage = 2;
	attack_range = 100;
	attack_speed = 1;
    slow_level = (type == 1) ? 1 : 2;

    // 创建 Sprite 对象（根据type选择不同的图像文件）
    std::string spriteFileName = "tower" + std::to_string(type) + "_" + std::to_string(level) + ".png";
    Sprite* mySprite = Sprite::create(spriteFileName);

    // 设置 Sprite 的位置等属性（根据实际需求进行调整）
    setPosition(touchlocation);  // 设置位置

    if (mySprite) {
        addChild(mySprite); // 将 Sprite 添加为 Tower 的子节点
        return true;
    }
    return false;
}
Tower* Tower::Tower_create(int type, const cocos2d::Vec2& touchlocation, std::vector<Tower*>* towersContainer) {
    Tower* my_Tower = new Tower(towersContainer);
    if (my_Tower->Tower_init(type, touchlocation)) {
        my_Tower->autorelease();
        // 如果需要，可以在这里将塔添加到容器中
        if (towersContainer) {
            towersContainer->push_back(my_Tower);
        }
        return my_Tower;
    }
    else {
        CC_SAFE_DELETE(my_Tower);
        return nullptr;
    }
}
void Tower::removeTower()
{
    // 通过名字获取 Sprite 对象
    Sprite* mySprite = dynamic_cast<Sprite*>(getChildByName(spriteFileName));

    // 从文件名中提取 type 和 level
    int type = -1; // 初始化为一个无效值
    int level = -1; // 初始化为一个无效值

    // 可以在删除节点之前先释放与炮塔相关的资源
    if (mySprite)
    {
        // 获取文件名
        std::string fileName = mySprite->getTexture()->getPath();

        // 解析文件名，假设文件名格式为 "tower{type}_{level}.png"
        size_t startPos = fileName.find("tower") + 5; // 找到 "tower" 后的位置
        size_t endPos = fileName.find("_"); // 找到 "_" 的位置
        if (startPos != std::string::npos && endPos != std::string::npos)
        {
            // 从字符串中提取 type
            type = std::stoi(fileName.substr(startPos, endPos - startPos));

            // 从字符串中提取 level
            startPos = endPos + 1;
            endPos = fileName.find(".png");
            if (startPos != std::string::npos && endPos != std::string::npos)
            {
                level = std::stoi(fileName.substr(startPos, endPos - startPos));
            }
        }
        money += 0.6 * (20 * type + 140 * level + 20 * level * level);
        mySprite->removeFromParentAndCleanup(true);
        mySprite = nullptr; // 将指针置为 nullptr，防止悬空指针
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

Node* Tower::getNearestTarget(Vector<Node*>& possibleTargets)
{
    Node* nearestTarget = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    
    //当执行for (Node* target : possibleTargets)时，
    //这个循环在内部使用了possibleTargets的迭代器来遍历所有的元素。
    //范围基于的for循环是C++11引入的，它抽象了迭代器的复杂性，使得代码更清晰易读，
    //但实质上它是通过迭代器来访问和遍历容器的。
    for (Node* target : possibleTargets)
    {
        // 计算炮塔到目标的距离
        float distance = getPosition().distance(target->getPosition());

        // 检查目标是否在攻击范围内
        if (distance <= attack_range)
        {
            // 更新最近目标
            if (distance < nearestDistance)
            {
                nearestDistance = distance;
                nearestTarget = target;
            }
        }
    }

    return nearestTarget;
}

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
