#ifndef _BULLET_H_
#define _BULLET_H_
#include "Monster.h"
#include "cocos2d.h"
#include "AudioEngine.h"


USING_NS_CC;

class Bullet : public cocos2d::Sprite {
public:
    // ���캯��
    Bullet(const cocos2d::Vec2& startPosition,
        Monster* targetMonster, // ���Ŀ�����ָ��
        float speed,
        int damage,
        std::vector<Bullet*>* bulletsContainer)
        : targetMonster(targetMonster), // ����Ŀ���������
        damage(damage),
        bulletsPtr(bulletsContainer) {
        // ��ʼ��Sprite����������
        // ...
    }

    // ��ʼ������
    bool init(const cocos2d::Vec2& startPosition, const std::string& spriteFileName);

    // ��̬��������
   static Bullet* create(const cocos2d::Vec2& startPosition,
        Monster* targetMonster, // ���Ŀ��������
        const std::string& spriteFileName,
        int damage,
        float speed,
        std::vector<Bullet*>* bulletsContainer);

    // �����ӵ�����
    void destroy();

    void startMoving(const Vec2& targetPosition, float speed);

    void hitTarget();

private:
    cocos2d::Vec2 position;  // �ӵ��ĵ�ǰλ��
    cocos2d::Vec2 velocity;  // �ӵ����ٶ�����
    cocos2d::Vec2 target;    // �ӵ���Ŀ��λ��
    int damage;              // �ӵ��Թ�����˺�
    std::vector<Bullet*>* bulletsPtr;  // �ӵ�����ָ��
    Monster* targetMonster;  // Ŀ�����ָ��
};


#endif

