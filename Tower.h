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
	int level;//炮塔等级

	int type;//炮塔类型

	int attack_damage;//攻击力

	int attack_range;//攻击范围

	int slow_level;//减速等级

	int attack_speed;//攻击速度

	std::string spriteFileName; // 存储图像文件的路径

	std::vector<Tower*>* towersPtr;  // 指向包含所有Tower的容器的指针

	std::vector<Bullet*> bullets; // 保存所有子弹的容器

public:
	Tower(std::vector<Tower*>* towers) : towersPtr(towers), level(1), type(1), attack_damage(2), attack_range(100), slow_level(0), attack_speed(1) {}
	virtual ~Tower()
	{
		// 在此添加可能需要释放的资源或其他清理操作
	}

	// 初始化方法声明
	bool Tower_init(int type, const cocos2d::Vec2& touchlocation);

	// 生成方法声明
	static Tower* Tower_create(int type, const cocos2d::Vec2& touchlocation, std::vector<Tower*>* towersContainer);

	void shootBulletAtMonster(Monster* target);

	//删除防御塔
	void removeTower();

	//找到距离最近的防御塔
	Node* getNearestTarget(Vector<Node*>& possibleTargets);

	//防御塔升级
	void upgradeTower();

	//调整防御塔角度，对准最近攻击目标
	void rotateToTarget(Node* target);

	void shootBullet(std::vector<Bullet*>* bulletsContainer, const cocos2d::Vec2& targetPosition);

	void shootBulletAtMonster(Monster* target);

	//void extractTypeInfo();// 获取文件名

};
#endif
//外部创建
/*std::vector<Tower*> towersContainer;

// 假设有触摸位置touchlocation和类型type
Tower* newTower = Tower::Tower_create(type, touchlocation, &towersContainer);
// 进行其他操作...
*/

