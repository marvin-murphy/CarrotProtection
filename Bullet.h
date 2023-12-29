#ifndef _BULLET_H_
#define _BULLET_H_
#include "Monster.h"
#include "cocos2d.h"
#include "AudioEngine.h"


USING_NS_CC;

class Bullet : public cocos2d::Sprite {
public:
    // 构造函数
    Bullet(const cocos2d::Vec2& startPosition,
        Monster* targetMonster, // 添加目标怪物指针
        float speed,
        int damage,
        std::vector<Bullet*>* bulletsContainer)
        : targetMonster(targetMonster), // 保存目标怪物引用
        damage(damage),
        bulletsPtr(bulletsContainer) {
        // 初始化Sprite和其他属性
        // ...
    }

    // 初始化方法
    bool init(const cocos2d::Vec2& startPosition, const std::string& spriteFileName);

    // 静态创建方法
   static Bullet* create(const cocos2d::Vec2& startPosition,
        Monster* targetMonster, // 添加目标怪物参数
        const std::string& spriteFileName,
        int damage,
        float speed,
        std::vector<Bullet*>* bulletsContainer);

    // 销毁子弹方法
    void destroy();

    void startMoving(const Vec2& targetPosition, float speed);

    void hitTarget();

private:
    cocos2d::Vec2 position;  // 子弹的当前位置
    cocos2d::Vec2 velocity;  // 子弹的速度向量
    cocos2d::Vec2 target;    // 子弹的目标位置
    int damage;              // 子弹对怪物的伤害
    std::vector<Bullet*>* bulletsPtr;  // 子弹容器指针
    Monster* targetMonster;  // 目标怪物指针
};


#endif

