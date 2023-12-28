#ifndef MY_TOWER_H
#define MY_TOWER_H
#define TOWER_LEVEL 4
#include "cocos2d.h"

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

	std::string spriteFileName; // �洢ͼ���ļ���·��
public:
	Tower() :level(1), type(1), attack_damage(2), attack_range(100), slow_level(0), attack_speed(1) {}
	virtual ~Tower()
	{
		// �ڴ���ӿ�����Ҫ�ͷŵ���Դ�������������
	}

	// ��ʼ����������
	bool Tower_init(int type);

	// ���ɷ�������
	static Tower* Tower_create(int type);

	//ɾ��������
	void removeTower();

	//�ҵ���������ķ�����
	Node* getNearestTarget(Vector<Node*>& possibleTargets);

	//����������
	void upgradeTower();

	//�����������Ƕȣ���׼�������Ŀ��
	void rotateToTarget(Node* target);

	CREATE_FUNC(Tower);//Tower* myTower = Tower::create(type);

};
#endif

