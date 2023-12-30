#ifndef MY_TOWER_H
#define MY_TOWER_H
#define TOWER_LEVEL 4
#include "cocos2d.h"
#include "Bullet.h"
#include "Monster.h"

USING_NS_CC;
class Tower : public cocos2d::Sprite
{
private:
	int level;//�����ȼ�

	int type;//��������

	int attack_damage;//������

	int attack_range;//������Χ

	int slow_level;//���ٵȼ�

	int attack_speed;//�����ٶ�

	float attackInterval; // �����������0.5��

	float timeSinceLastAttack; // ���ϴι�������������ʱ��

	std::string spriteFileName; // �洢ͼ���ļ���·��

	std::vector<Tower*>* towersPtr;  // ָ���������Tower��������ָ��

	std::vector<Bullet*> bullets; // ���������ӵ�������

	std::vector<Monster*>* monstersPtr;  // ָ�����������ָ��

public:
	Tower(std::vector<Monster*>* monstersContainer, std::vector<Tower*>* towersContainer) :
		monstersPtr(monstersContainer),
		towersPtr(towersContainer),
		level(1),
		type(1),
		attack_damage(2),
		attack_range(100),
		slow_level(0),
		attack_speed(1),
		attackInterval(0.5f), // ��ʼ���������Ϊ0.5��
		timeSinceLastAttack(0.0f) // ��ʼ���ϴι���ʱ��Ϊ0
	{
		// ������Ա�����ĳ�ʼ���������������
		attack_speed = 1.0f;  // ʾ��ֵ�������ʾÿ�뷢��һ�ι���

		// ��Tower�������ʼ��ʱ�����Լ��ĸ���
		this->schedule(CC_SCHEDULE_SELECTOR(Tower::updateTower), attackInterval);
	}
	virtual ~Tower()
	{
		// �ڴ���ӿ�����Ҫ�ͷŵ���Դ�������������
	}

	// ��ʼ����������
	bool Tower_init(int type, const cocos2d::Vec2& touchlocation);

	static Tower* Tower_create(int type, const cocos2d::Vec2& touchlocation, std::vector<Monster*>* monstersContainer, std::vector<Tower*>* towersContainer);

	void shootBulletAtMonster(Monster* target);

	//ɾ��������
	void removeTower();

	//�ҵ���������ķ�����
	Monster* getNearestTarget(std::vector<Monster*>& monsters);

	//����������
	void upgradeTower();

	//�����������Ƕȣ���׼�������Ŀ��
	void rotateToTarget(Node* target);

	void updateTower(float dt);

	void shootBullet(std::vector<Bullet*>* bulletsContainer, const cocos2d::Vec2& targetPosition);

	void shootBulletAtMonster(Monster* target);

	//void extractTypeInfo();// ��ȡ�ļ���

};
#endif
//�ⲿ����
/*std::vector<Tower*> towersContainer;

// �����д���λ��touchlocation������type
Tower* newTower = Tower::Tower_create(type, touchlocation, &towersContainer);
// ������������...
*/

