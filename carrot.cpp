#include "Carrot.h"

extern int money;

Carrot::Carrot() : health(0), level(0) {
    // 构造函数，不要在这里进行初始化
    spriteFileName = "mysprite.png"; // 默认图像文件路径
}

bool Carrot::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 使用加载的图像文件创建 Sprite 对象
    if (!spriteFileName.empty()) {
        Sprite* mySprite = Sprite::create(spriteFileName);
        if (mySprite) {
            addChild(mySprite); // 将 Sprite 添加为 Carrot 的子节点
        }
    }

    // 在这里进行对象的初始化工作
    health = 10; // 初始化血量为10
    level = 1;   // 初始化等级为1

    return true;
}

Carrot* Carrot::create() {
    Carrot* mycarrot = new Carrot();
    if (mycarrot && mycarrot->init()) {
        mycarrot->autorelease();
        return mycarrot; // 返回创建的 Carrot 对象
    }
    else {
        CC_SAFE_DELETE(mycarrot);
        return nullptr;
    }
}

bool Carrot::if_upgrade() {
    
    if (money - 20 * level >= 0 && level < CARROT_LEVEL) {
        money -= 20 * level;
        level++;
        health += 5;
        return true;
    }
    return false;
}

bool Carrot::health_decrease(int num) {
    if (health - num < 0)
        return false;
    else {
        health -= num;
        return true;
    }
}


