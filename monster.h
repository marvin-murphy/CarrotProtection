#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"

USING_NS_CC;

class Monster : public cocos2d::Sprite {
public:
    // Monster�๹�캯��
    Monster(std::vector<Monster*>* monsters) : monstersPtr(monsters), health(15), level(1), type(1), hit(1) {}

    // ��ʼ����������
    bool monster_init(int type);

    // ���ɷ�������
    Monster* Monster::monster_create(int type, std::vector<Monster*>* monstersContainer);

    void setMonstersContainer(std::vector<Monster*>* monsters) {
        monstersPtr = monsters;
    }

    // Ѫ�����ٷ�������
    bool health_decrease(int num);

    // ��ȡѪ���ķ���
    int getHealth() const;

    // ����Ѫ���ķ���
    void setHealth(int value);

    // ��ȡ�ȼ��ķ���
    int getLevel() const;

    // ���õȼ��ķ���
    void setLevel(int value);

    // ��ȡ���͵ķ���
    int getType() const;

    // �������͵ķ���
    void setType(int value);

    // ��ȡ�������ķ���
    int getHit() const;

    // ���ù������ķ���
    void setHit(int value);

    void die();

private:
    int health;
    int level;
    int type;
    int hit;
    std::vector<Monster*>* monstersPtr;
};

#endif
//�ⲿ��������
/*std::vector<Monster*> monstersContainer;
int monsterType = 1; // ������һ���������ͱ�ʶ��
Monster* newMonster = Monster::monster_create(monsterType, &monstersContainer);

if (newMonster) {
    // ����г����򸸽ڵ㣬����Ҫ��������ӵ�����
    // this->addChild(newMonster);
    // �������������������û��ʼ������
}
*/

