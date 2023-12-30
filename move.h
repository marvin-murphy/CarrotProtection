#ifndef _MOVE_H_
#define _MOVE_H_
#include "cocos2d.h"
#include "Bullet.h"
#include "Tower.h"
#include "Carrot.h"
#include "Monster.h"

class GameLayer : public cocos2d::Layer {
private:
    int monstersCreated; // ��¼�Ѵ�����Monster����

    int totalMonstersToCreate; // �ܹ�Ҫ�����Ĺ�������

    std::vector<Monster*> monstersContainer; // �洢Monster����

    Carrot* myCarrot; // �Ѿ������ͳ�ʼ����Carrot����

    std::vector<Tower*> towersContainer; // �洢Tower����

public:
    GameLayer::GameLayer() {
        // ��ʼ��myCarrot
        myCarrot = Carrot::create();

        // ��ʼ��������Ա����
        monstersCreated = 0;
        // ...������ʼ������...
        this->scheduleUpdate();  // ����GameLayer����ĸ���
    }

    GameLayer::~GameLayer() {
        for (Monster* monster : monstersContainer) {
            monster->parentLayer = nullptr;  // ���Monster��GameLayer������
            // ���ܻ���Ҫ����������������ֹͣ������
        }
        // ... ����GameLayer�������Դ ...
    }

    void createMonster(float dt, int type, int totalMonsters); // ��Ӳ���

    void startCreatingMonsters(int type, int totalMonsters); // ���ڿ�ʼ��������ķ���

    bool allMonstersDead();

    void notifyMonsterDeath();

    void createTower(int type, const cocos2d::Vec2& touchlocation);

    void onPlayerTouch(const cocos2d::Vec2& location);

    void update(float dt);
};
#endif
// ��������ĳ���ط������������
//gameLayer->startCreatingMonsters(1, 20); // ���磬����20������Ϊ1�Ĺ���


