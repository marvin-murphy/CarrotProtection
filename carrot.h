#ifndef MY_CARROT_H
#define MY_CARROT_H

#include "cocos2d.h"

#define CARROT_LEVEL 3

USING_NS_CC;

class Carrot : public cocos2d::Sprite {
public:
    Carrot(); // 构造函数

    virtual ~Carrot() {
        // 在这里释放可能的动态分配的资源
    }

    // 初始化方法声明
    bool init() override;

    // 生成方法声明
    static Carrot* create();

    // 升级方法声明
    bool if_upgrade();

    // 血量减少方法声明
    bool health_decrease(int num);

    // 获取血量和等级的方法
    int getHealth() const { return health; }
    int getLevel() const { return level; }

    void updateSpriteFileName();

private:
    int health;
    int level;
    std::string spriteFileName; // 存储图像文件的路径
    
};

#endif

