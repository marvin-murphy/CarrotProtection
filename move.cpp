#include "move.h"
void GameLayer::createMonster(float dt, int type, int totalMonsters)
{
    if (monstersCreated < totalMonsters) 
    {
        Monster* newMonster = Monster::monster_create(type, myCarrot, &monstersContainer);
        if (newMonster) {
            // ���¹�����ӵ���Ϸ��򳡾���
            newMonster->parentLayer = this; // ����parentLayer
            this->addChild(newMonster);

            // �����¹�����0.5���ʼ�ƶ�
            newMonster->scheduleOnce(
                [newMonster](float dt) { // Lambda���ʽ��ʼ
                    newMonster->startMoving(1); // ��Lambda�ڵ���startMoving����
                }, // Lambda���ʽ����
                0.5f, // �ӳ�0.5���ִ��
                    "start_moving_schedule" // ��������ı�ʶ�ַ���
                    );
        }
        monstersCreated++;
    }
    else {
        // ʹ������ļ���ȡ������
        this->unschedule("monster_creation_scheduler");
    }
}
void GameLayer::startCreatingMonsters(int type, int totalMonsters)
{
    this->schedule([=](float dt) {
        this->createMonster(dt, type, totalMonsters);
        }, 1.0f, "monster_creation_scheduler");
}

void GameLayer::notifyMonsterDeath() {
    if (allMonstersDead()) {
        // ���й��ﶼ���ˣ���ʼ��һ�����ɻ��������߼�
        //startCreatingMonsters(nextMonsterType, nextTotalMonsters);
    }
}

bool GameLayer::allMonstersDead() {
    for (auto monster : monstersContainer) {
        if (monster->state == Monster::State::Alive) {
            return false; // ��������һ�����ﻹ����
        }
    }
    return true; // ���й��ﶼ����
}

void GameLayer::onPlayerTouch(const cocos2d::Vec2& location) {
    // ������Ҵ���λ�þ��Ƿ�������λ��
    // �������Ѿ�������������
    int towerType = 1; // �������ͣ�������Ϸ�߼�ȷ��

    createTower(towerType, location);
}

void GameLayer::createTower(int type, const cocos2d::Vec2& touchlocation) {
    // ����monstersContainer��towersContainer�Ѿ���GameLayer�ж���Ϊ��Ա����
    Tower* newTower = Tower::Tower_create(type, touchlocation, &monstersContainer, &towersContainer);

    if (newTower) {
        // �������ɹ����Ѿ��� Tower::Tower_create ����ӵ�����
        this->addChild(newTower); // ������ӵ���Ϸ������
        // ... �������ú��߼� ...
    }
}


void GameLayer::update(float dt) {
    // ��������������������
    for (Tower* tower : towersContainer) {
        tower->updateTower(dt);
    }
    // ... ���ܵ����������߼� ...
}
