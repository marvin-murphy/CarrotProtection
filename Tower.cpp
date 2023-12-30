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
    // ��ȡ����Ŀ���λ��
    cocos2d::Vec2 startPosition = this->getPosition();
    cocos2d::Vec2 targetPosition = target->getPosition();

    // �����ӵ����������ԣ�����ͼ���˺����ٶȵ�
    // ʹ���ַ���ƴ��
        std::string spriteFileName = "bullet_" + std::to_string(type) + "_" + std::to_string(level) + ".png";
    int damage = this->attack_damage; // ʹ�����Ĺ����˺�
    float speed = 200.0 * attack_speed; // �ӵ��ٶȣ����Ը����������Ե���

    // ʹ��Bullet::create�����ӵ�
    Bullet* bullet = Bullet::create(startPosition, target, spriteFileName, damage, speed, &bullets);
    if (bullet) {
        // ���ӵ���ӵ���Ϸ������
        this->getParent()->addChild(bullet);
        // �����ӵ��������߼��򶯻�
        bullet->startMoving(targetPosition, speed);
    }
}

void Tower::removeTower()
{

    // ������ɾ���ڵ�֮ǰ���ͷ���������ص���Դ
    Sprite* mySprite = dynamic_cast<Sprite*>(this); // ����this����Sprite����
    if (mySprite)
    {
        // ���㲢��ӽ�ң����� money ��ȫ�ֱ�����ĳ����ʽ����Դ�������еı���
        money += 0.6 * (20 * type + 140 * level + 20 * level * level);
        mySprite->removeFromParentAndCleanup(true); // ɾ��������
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
/*
// ����һ��Tower����
Tower* myTower = new Tower(); // �����κδ���Tower����ķ�ʽ

// ��ĳ���¼�����������ʱ
// ���磬���ѡ������������Ϸ��Ҫ������
myTower->removeTower();  // ����removeTower����
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



//��ִ��for (Node* target : possibleTargets)ʱ��
    //���ѭ�����ڲ�ʹ����possibleTargets�ĵ��������������е�Ԫ�ء�
    //��Χ���ڵ�forѭ����C++11����ģ��������˵������ĸ����ԣ�ʹ�ô���������׶���
    //��ʵ��������ͨ�������������ʺͱ��������ġ�
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

void Tower::updateTower(float dt) {
    // �������ϴι�������������ʱ��
    timeSinceLastAttack += dt;

    if (monstersPtr && !monstersPtr->empty() && timeSinceLastAttack >= attackInterval) {
        // ��ȡ�����Ŀ��
        Monster* nearestTarget = dynamic_cast<Monster*>(getNearestTarget(*monstersPtr));

        // ������������Ŀ�꣬��ת������
        if (nearestTarget) {
            rotateToTarget(nearestTarget);
            shootBulletAtMonster(nearestTarget);

            // ���ü�ʱ��
            timeSinceLastAttack = 0.0f;
        }
    }
}



/*
void Tower::extractTypeInfo() {
    // ��ȡ�ļ���
    std::string fileName = this->getTexture()->getPath();

    // �����ļ����������ļ�����ʽΪ "tower{type}_{level}.png"
    size_t startPos = fileName.find("tower") + 5; // �ҵ� "tower" ���λ��
    size_t endPos = fileName.find("_"); // �ҵ� "_" ��λ��
    if (startPos != std::string::npos && endPos != std::string::npos) {
        // ���ַ�������ȡ type
        type = std::stoi(fileName.substr(startPos, endPos - startPos));

        // ���ַ�������ȡ level
        startPos = endPos + 1;
        endPos = fileName.find(".png");
        if (startPos != std::string::npos && endPos != std::string::npos) {
            level = std::stoi(fileName.substr(startPos, endPos - startPos));
        }
    }
}
*/
