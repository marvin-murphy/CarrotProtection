#include "Bullet.h"

bool Bullet::init(const cocos2d::Vec2& startPosition, const std::string& spriteFileName) {
    // 初始化子弹属性
    if (!Sprite::init()) {
        return false;
    }
    // 使用加载的图像文件创建 Sprite 对象
    if (!spriteFileName.empty()) {
        Sprite* mySprite = Sprite::create(spriteFileName);

        // 设置 Sprite 的位置等属性（根据实际需求进行调整）
        setPosition(startPosition); // 设置位置

        if (mySprite) {
            mySprite->setName(spriteFileName); // 设置子节点的名字与图片名字相同
            addChild(mySprite); // 将 Sprite 添加为 Carrot 的子节点
        }
    }

    return true;
}

Bullet* Bullet::create(const cocos2d::Vec2& startPosition,
    Monster* targetMonster, // 添加目标怪物参数
    const std::string& spriteFileName,
    int damage,
    float speed,
    std::vector<Bullet*>* bulletsContainer) {
    // 创建Bullet对象，传递目标怪物引用
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

    // 确保有有效的容器指针
    if (bulletsPtr) {
        auto& container = *bulletsPtr;  // 解引用以简化访问
        auto it = std::find(container.begin(), container.end(), this);
        if (it != container.end()) {
            container.erase(it);  // 从容器中删除子弹
        }
    }

    // 执行其他清理工作...
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
}

void Bullet::hitTarget() {
    // 获取子弹当前位置
    cocos2d::Vec2 currentPosition = this->getPosition();

    // 计算子弹和目标之间的距离
    float distance = currentPosition.distance(target);

    // 设定一个阈值，当子弹和目标的距离小于这个阈值时，视为击中
    float hitThreshold = 5.0f; // 可以根据需要调整这个值

    if (distance < hitThreshold) {

        if (targetMonster) { // 确保有有效的怪物目标
            // 调用怪物的 health_decrease 方法减少血量
            bool isAlive = targetMonster->health_decrease(damage);
        }
        // 播放打中音效
    // 假设使用Cocos2d-x的SimpleAudioEngine
        int audioId = cocos2d::AudioEngine::play2d("hit_sound.mp3");

        // 调用destroy销毁子弹
        this->destroy();
    }
}


void Bullet::startMoving(const cocos2d::Vec2& targetPosition, float speed) {
    // 计算移动所需的时间
    float distance = this->getPosition().distance(targetPosition);
    float moveDuration = distance / speed;

    // 创建一个移动动作
    auto moveAction = MoveTo::create(moveDuration, targetPosition);

    // 创建一个定期检查怪物存活状态的回调
    auto checkMonsterStatus = CallFunc::create([this]() {
        if (targetMonster && !targetMonster->isAlive()) {
            // 如果怪物已经死亡，则销毁子弹
            this->destroy();
        }
        });

    // 创建一个回调动作，在移动完成后检查是否击中目标
    auto callbackAction = CallFunc::create(CC_CALLBACK_0(Bullet::hitTarget, this));

    // 创建一个动作序列：先移动，然后检查击中，同时定期检查怪物状态
    auto sequence = Sequence::create(moveAction, checkMonsterStatus, callbackAction, nullptr);

    // 执行动作序列
    this->runAction(sequence);
}

