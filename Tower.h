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

	std::vector<Tower*>* towersPtr;  // ָ���������Tower��������ָ��
public:
	Tower(std::vector<Tower*>* towers) : towersPtr(towers), level(1), type(1), attack_damage(2), attack_range(100), slow_level(0), attack_speed(1) {}
	virtual ~Tower()
	{
		// �ڴ���ӿ�����Ҫ�ͷŵ���Դ�������������
	}

	// ��ʼ����������
	bool Tower_init(int type, const cocos2d::Vec2& touchlocation);

	// ���ɷ�������
	static Tower* Tower_create(int type, const cocos2d::Vec2& touchlocation, std::vector<Tower*>* towersContainer);

	//ɾ��������
	void removeTower();

	//�ҵ���������ķ�����
	Node* getNearestTarget(Vector<Node*>& possibleTargets);

	//����������
	void upgradeTower();

	//�����������Ƕȣ���׼�������Ŀ��
	void rotateToTarget(Node* target);

};
#endif
//�ⲿ����
/*std::vector<Tower*> towersContainer;

// �����д���λ��touchlocation������type
Tower* newTower = Tower::Tower_create(type, touchlocation, &towersContainer);
// ������������...
*/

