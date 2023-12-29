#ifndef MY_MONSTER_H
#define MY_MONSTER_H

#include "cocos2d.h"
#include "Carrot.h"


USING_NS_CC;

class Monster : public cocos2d::Sprite 
{
public:
    // Monster�๹�캯��
    Monster(std::vector<Monster*>* monsters, Carrot* targetCarrot)
        : monstersPtr(monsters), carrotPtr(targetCarrot), health(15), level(1), type(1), hit(1) {
        // ������ʼ������
    }

    // ��ʼ����������
    bool monster_init(int type);

    // ���ɷ�������
    Monster* monster_create(int type, Carrot* carrot, std::vector<Monster*>* monstersContainer);

    void setMonstersContainer(std::vector<Monster*>* monsters) {
        monstersPtr = monsters;
    }

    void onReachedDestination();

    // Ѫ�����ٷ�������
    bool health_decrease(int num);

    bool Monster::isAlive() const {
        return health > 0;
    }


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

    // �ƶ�����
    //void moveLeft(float duration);
    //void moveRight(float duration);
    //void moveUp(float duration);
    //void moveDown(float duration);
    void startMoving(int speed);
    //void updatePosition();
   // int getX() const {
   //     return x;
   // }

    //void setX(int value) {
    //    x = value;
   // }
   // int getY() const {
    //    return y;
   // }

    //void setY(int value) {
   //     y = value;
   // }

private:
    int health;
    int level;
    int type;
    int hit;
   // int x;
   // int y;
    std::vector<Monster*>* monstersPtr;// ָ�����������ָ��
    Carrot* carrotPtr;                   // ָ��Carrot�����ָ��
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

