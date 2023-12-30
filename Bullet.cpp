#include "Bullet.h"

bool Bullet::init(const cocos2d::Vec2& startPosition, const std::string& spriteFileName) {
    // ��ʼ���ӵ�����
    if (!Sprite::init()) {
        return false;
    }
    // ʹ�ü��ص�ͼ���ļ����� Sprite ����
    if (!spriteFileName.empty()) {
        Sprite* mySprite = Sprite::create(spriteFileName);

        // ���� Sprite ��λ�õ����ԣ�����ʵ��������е�����
        setPosition(startPosition); // ����λ��

        if (mySprite) {
            mySprite->setName(spriteFileName); // �����ӽڵ��������ͼƬ������ͬ
            addChild(mySprite); // �� Sprite ���Ϊ Carrot ���ӽڵ�
        }
    }

    return true;
}

Bullet* Bullet::create(const cocos2d::Vec2& startPosition,
    Monster* targetMonster, // ���Ŀ��������
    const std::string& spriteFileName,
    int damage,
    float speed,
    std::vector<Bullet*>* bulletsContainer) {
    // ����Bullet���󣬴���Ŀ���������
    Bullet* bullet = new Bullet(startPosition, targetMonster, speed, damage, bulletsContainer);
    if (bullet && bullet->init(startPosition, spriteFileName)) {
        bullet->autorelease();
        if (bulletsContainer) {
            bulletsContainer->push_back(bullet);
        }
        return bullet;
    }
    else {
        CC_SAFE_DELETE(bullet);
        return nullptr;
    }
}

void Bullet::destroy() {

    // ȷ������Ч������ָ��
    if (bulletsPtr) {
        auto& container = *bulletsPtr;  // �������Լ򻯷���
        auto it = std::find(container.begin(), container.end(), this);
        if (it != container.end()) {
            container.erase(it);  // ��������ɾ���ӵ�
        }
    }

    // ִ������������...
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
}

void Bullet::hitTarget() {
    // ��ȡ�ӵ���ǰλ��
    cocos2d::Vec2 currentPosition = this->getPosition();

    // �����ӵ���Ŀ��֮��ľ���
    float distance = currentPosition.distance(target);

    // �趨һ����ֵ�����ӵ���Ŀ��ľ���С�������ֵʱ����Ϊ����
    float hitThreshold = 5.0f; // ���Ը�����Ҫ�������ֵ

    if (distance < hitThreshold) {

        if (targetMonster) { // ȷ������Ч�Ĺ���Ŀ��
            // ���ù���� health_decrease ��������Ѫ��
            bool isAlive = targetMonster->health_decrease(damage);
        }
        // ���Ŵ�����Ч
    // ����ʹ��Cocos2d-x��SimpleAudioEngine
        int audioId = cocos2d::AudioEngine::play2d("hit_sound.mp3");

        // ����destroy�����ӵ�
        this->destroy();
    }
}


void Bullet::startMoving(const cocos2d::Vec2& targetPosition, float speed) {
    // �����ƶ������ʱ��
    float distance = this->getPosition().distance(targetPosition);
    float moveDuration = distance / speed;

    // ����һ���ƶ�����
    auto moveAction = MoveTo::create(moveDuration, targetPosition);

    // ����һ�����ڼ�������״̬�Ļص�
    auto checkMonsterStatus = CallFunc::create([this]() {
        if (targetMonster && !targetMonster->isAlive()) {
            // ��������Ѿ��������������ӵ�
            this->destroy();
        }
        });

    // ����һ���ص����������ƶ���ɺ����Ƿ����Ŀ��
    auto callbackAction = CallFunc::create(CC_CALLBACK_0(Bullet::hitTarget, this));

    // ����һ���������У����ƶ���Ȼ������У�ͬʱ���ڼ�����״̬
    auto sequence = Sequence::create(moveAction, checkMonsterStatus, callbackAction, nullptr);

    // ִ�ж�������
    this->runAction(sequence);
}

