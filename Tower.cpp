#include "Tower.h"

extern int money;

bool Tower ::Tower_init(int type, const cocos2d::Vec2& touchlocation)
{
	level = 1;
	attack_damage = 2;
	attack_range = 100;
	attack_speed = 1;
    slow_level = (type == 1) ? 1 : 2;

    // ���� Sprite ���󣨸���typeѡ��ͬ��ͼ���ļ���
    std::string spriteFileName = "tower" + std::to_string(type) + "_" + std::to_string(level) + ".png";
    Sprite* mySprite = Sprite::create(spriteFileName);

    // ���� Sprite ��λ�õ����ԣ�����ʵ��������е�����
    setPosition(touchlocation);  // ����λ��

    if (mySprite) {
        addChild(mySprite); // �� Sprite ���Ϊ Tower ���ӽڵ�
        return true;
    }
    return false;
}
Tower* Tower::Tower_create(int type, const cocos2d::Vec2& touchlocation, std::vector<Tower*>* towersContainer) {
    Tower* my_Tower = new Tower(towersContainer);
    if (my_Tower->Tower_init(type, touchlocation)) {
        my_Tower->autorelease();
        // �����Ҫ�����������ｫ����ӵ�������
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
    // ͨ�����ֻ�ȡ Sprite ����
    Sprite* mySprite = dynamic_cast<Sprite*>(getChildByName(spriteFileName));

    // ���ļ�������ȡ type �� level
    int type = -1; // ��ʼ��Ϊһ����Чֵ
    int level = -1; // ��ʼ��Ϊһ����Чֵ

    // ������ɾ���ڵ�֮ǰ���ͷ���������ص���Դ
    if (mySprite)
    {
        // ��ȡ�ļ���
        std::string fileName = mySprite->getTexture()->getPath();

        // �����ļ����������ļ�����ʽΪ "tower{type}_{level}.png"
        size_t startPos = fileName.find("tower") + 5; // �ҵ� "tower" ���λ��
        size_t endPos = fileName.find("_"); // �ҵ� "_" ��λ��
        if (startPos != std::string::npos && endPos != std::string::npos)
        {
            // ���ַ�������ȡ type
            type = std::stoi(fileName.substr(startPos, endPos - startPos));

            // ���ַ�������ȡ level
            startPos = endPos + 1;
            endPos = fileName.find(".png");
            if (startPos != std::string::npos && endPos != std::string::npos)
            {
                level = std::stoi(fileName.substr(startPos, endPos - startPos));
            }
        }
        money += 0.6 * (20 * type + 140 * level + 20 * level * level);
        mySprite->removeFromParentAndCleanup(true);
        mySprite = nullptr; // ��ָ����Ϊ nullptr����ֹ����ָ��
    }

    // �Ӹ��ڵ����Ƴ������ڵ㣬���ͷ��ڴ�
    removeFromParentAndCleanup(true);

    // ���������Ƴ��Լ�
    if (towersPtr) {
        auto& container = *towersPtr;
        auto it = std::find(container.begin(), container.end(), this);
        if (it != container.end()) {
            container.erase(it);
        }
    }
    // ����������������߼�������������Դ�ͷŵ�
}

Node* Tower::getNearestTarget(Vector<Node*>& possibleTargets)
{
    Node* nearestTarget = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    
    //��ִ��for (Node* target : possibleTargets)ʱ��
    //���ѭ�����ڲ�ʹ����possibleTargets�ĵ��������������е�Ԫ�ء�
    //��Χ���ڵ�forѭ����C++11����ģ��������˵������ĸ����ԣ�ʹ�ô���������׶���
    //��ʵ��������ͨ�������������ʺͱ��������ġ�
    for (Node* target : possibleTargets)
    {
        // ����������Ŀ��ľ���
        float distance = getPosition().distance(target->getPosition());

        // ���Ŀ���Ƿ��ڹ�����Χ��
        if (distance <= attack_range)
        {
            // �������Ŀ��
            if (distance < nearestDistance)
            {
                nearestDistance = distance;
                nearestTarget = target;
            }
        }
    }

    return nearestTarget;
}

//getNearestTarget��������ʾ��
/*
// ����һ�� Vector ����
Vector<Node*> monsters;

// ��ӹ���ڵ㵽 Vector ��
monsters.pushBack(monsterNode1);
monsters.pushBack(monsterNode2);
// ��Ӹ������ڵ�...

// ��ȡ���������Ŀ��
Node* nearestTarget = myTower->getNearestTarget(monsters);
*/

void Tower::upgradeTower()
{
    // ������Ҫ�������������ԣ�����ֻ��ʾ��
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

    // �����µ�ͼƬ�ļ�·��
    std::string newSpriteFileName = "tower" + std::to_string(type) + "_" + std::to_string(level) + ".png";

    // �����·���;�·����ͬ���Ž��и���
    if (newSpriteFileName != spriteFileName)
    {
        // ��ȡ��Ϊ spriteFileName ���ӽڵ�
        Sprite* mySprite = dynamic_cast<Sprite*>(getChildByName(spriteFileName));

        // ������ڣ��ͽ����Ƴ�
        if (mySprite)
        {
            removeChild(mySprite, true);
        }

        // �����µ�ͼƬ�ļ�·��
        spriteFileName = newSpriteFileName;

        // �����µ� Sprite ����
        mySprite = Sprite::create(spriteFileName);

        // �� Sprite ���Ϊ Tower ���ӽڵ�
        if (mySprite)
        {
            mySprite->setName(spriteFileName); // �����ӽڵ��������ͼƬ������ͬ
            addChild(mySprite);
        }
    }
}

void Tower::rotateToTarget(Node* target)
{
    float rotationSpeed = 45.0f;;   // ��ת�ٶ�
    if (target)
    {
        Vec2 direction = target->getPosition() - getPosition();
        float targetRotation = CC_RADIANS_TO_DEGREES(direction.getAngle());

        // ���� RotateTo ������ʵ��������ת
        RotateTo* rotateAction = RotateTo::create(1.0f / rotationSpeed, targetRotation);

        // ���ж���
        runAction(rotateAction);
    }
}
