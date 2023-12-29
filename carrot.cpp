#include "Carrot.h"

extern int money;

Carrot::Carrot() : health(0), level(0) {
    // 构造函数，不要在这里进行初始化
    std::string initialLabelText = "health: " + std::to_string(health);
    healthLabel = cocos2d::Label::createWithSystemFont(initialLabelText, "Arial", 24);
    if (healthLabel) {
        healthLabel->setPosition(Vec2(930, 560));
        this->addChild(healthLabel);
    }
    spriteFileName = "carrot_10.png"; // 默认图像文件路径
}

bool Carrot::init() {
    if (!Sprite::init()) {
        return false;
    }
    // 使用加载的图像文件创建 Sprite 对象
    if (!spriteFileName.empty()) {
        Sprite* mySprite = Sprite::create(spriteFileName);

        // 设置 Sprite 的位置等属性（根据实际需求进行调整）
        setPosition(Vec2(930, 510));  // 设置位置

        if (mySprite) {
            mySprite->setName(spriteFileName); // 设置子节点的名字与图片名字相同
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

void Carrot::updateHealthLabel() {
    if (healthLabel) {
        std::string labelText = "health: " + std::to_string(health);
        healthLabel->setString(labelText);
        // 更新标签文本为当前血量
    }
}

bool Carrot::if_upgrade() {
    
    if (money - 100 * level >= 0 && level < CARROT_LEVEL) {
        money -= 100 * level;
        level++;
        health += 5;
        // 升级后调用更新函数来更新纹理
        updateSpriteFileName();
        updateHealthLabel(); // 更新血量标签
        return true;
    }
    return false;
}

bool Carrot::health_decrease(int num) {
    if (health - num < 0)
        return false;
    else {
        health -= num;

        // 调用更新函数来更新纹理
        updateSpriteFileName();
        updateHealthLabel(); // 更新血量标签

        return true;
    }
}

void Carrot::updateSpriteFileName() {
    // 计算血量级别
    int healthLevel = std::min((health / 1) + 1, 10); // 以1为一个级别的基数，限制在小于等于10


    // 构造新的图片文件路径
    std::string newSpriteFileName = "carrot_" + std::to_string(healthLevel) + ".png";

    // 如果新路径和旧路径不同，才进行更新
    if (newSpriteFileName != spriteFileName) {
        // 获取名为 spriteFileName 的子节点
        Sprite* mySprite = dynamic_cast<Sprite*>(getChildByName(spriteFileName));

        // 如果存在，就将其移除
        if (mySprite) {
            removeChild(mySprite,true);
        }

        // 设置新的图片文件路径
        spriteFileName = newSpriteFileName;

        // 创建新的 Sprite 对象
        mySprite = Sprite::create(spriteFileName);

        // 将 Sprite 添加为 Carrot 的子节点
        if (mySprite) {
            mySprite->setName(spriteFileName); // 设置子节点的名字与图片名字相同
            addChild(mySprite);
        }
    }
}




