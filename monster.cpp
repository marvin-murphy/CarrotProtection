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
    setPosition(Vec2(180, 510));  // ����λ��

    if (mySprite) {
        addChild(mySprite); // �� Sprite ���Ϊ Monster ���ӽڵ�
        return true;
    }
    return false;
}

Monster* Monster::monster_create(int type,Carrot*carrot, std::vector<Monster*>* monstersContainer) {
    // �ڴ���Monsterʱ������monstersContainer
    Monster* my_monster = new Monster(monstersContainer, carrot);
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

void Monster::onReachedDestination() {
    // �����ܲ�������ֵ
    if (carrotPtr) {
        bool alive = carrotPtr->health_decrease(hit);

        if (!alive) {
            // ����ܲ�����ֵ�ľ���ִ����Ϸ�����߼�
        }
    }

    // ���ﵽ���յ����������
    this->die();
}

void Monster::die() {

    // ��������ʾ��ɱЧ��
    cocos2d::Sprite* hitEffect = cocos2d::Sprite::create("monster_die.png");
    if (hitEffect) {
        hitEffect->setPosition(this->getPosition()); // ����Ϊ�ӵ����е�λ��
        this->getParent()->addChild(hitEffect);

        // ���õ���ʱ��
        float duration = 0.5f;

        // ������������������ɺ�ɾ������
        auto fadeOutAndRemove = cocos2d::Sequence::create(
            cocos2d::FadeOut::create(duration), // ��������
            cocos2d::RemoveSelf::create(),      // ��ɺ�ɾ���Լ�
            nullptr);

        // ���ж���
        hitEffect->runAction(fadeOutAndRemove);
    }
    state = State::Dead; // ����״̬

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
    parentLayer->notifyMonsterDeath();

    int type = getType();
    money += 10 * type; // ���ӽ�ң����� money ��ȫ�ֱ���
}

/*void Monster::updatePosition() {
    // ��ȡ��ǰ�����λ��
    Vec2 currentPosition = this->getPosition();

    // �������ڲ���x��yֵ
    x = currentPosition.x;
    y = currentPosition.y;

    // �����������ӡ��������������ʽʹ���µ�����
}
*/
void Monster::startMoving(int speed) {
    float speedFactor = 1.2f - 0.2f * speed;

    // ���� speedFactor ��ȡֵ�� 0.2 �� 1.2 ֮��
    speedFactor = std::max(0.4f, std::min(1.2f, speedFactor));

    // ���ó�ʼλ��
    this->setPosition(Vec2(180, 510)); // ����monster����ʼλ��

    // ����һ���������У������µ�·�����ƶ�
    auto move1 = MoveTo::create(2 / speedFactor, Vec2(330, 510)); // ���յ�1
    auto move2 = MoveTo::create(4 / speedFactor, Vec2(330, 210)); // ���յ�2
    auto move3 = MoveTo::create(6 / speedFactor, Vec2(780, 210)); // ���յ�3
    auto move4 = MoveTo::create(4 / speedFactor, Vec2(780, 510)); // ���յ�4
    auto move5 = MoveTo::create(2 / speedFactor, Vec2(930, 510)); // ���յ�

    // ���һ���ƶ�������Ļص�
    auto callback = CallFunc::create(CC_CALLBACK_0(Monster::onReachedDestination, this));

    // �����ж����ͻص�������һ������
    auto sequence = Sequence::create(move1, move2, move3, move4, move5, callback, nullptr);

    // ִ�ж�������
    this->runAction(sequence);
}

void Monster::updateHealthLabel() {
    if (healthLabel) {
        std::string labelText = "Health: " + std::to_string(health);
        healthLabel->setString(labelText); // ���±�ǩ�ı�Ϊ��ǰѪ��
    }
}

void Monster::update(float dt) {
    // ���ø����update����
    cocos2d::Sprite::update(dt);

    // �����������Ӷ�����߼�������б�Ҫ�Ļ�

    // ���磬���������ƶ���ʽʹ�ñ�ǩ��Ҫ�ر����λ�ã�����������ʵ��
}


/*void Monster::moveLeft(float duration) {
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
