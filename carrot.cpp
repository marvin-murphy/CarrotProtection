#include "Carrot.h"

extern int money;

Carrot::Carrot() : health(0), level(0) {
    // ���캯������Ҫ��������г�ʼ��
    spriteFileName = "carrot_10.png"; // Ĭ��ͼ���ļ�·��
}

bool Carrot::init() {
    if (!Sprite::init()) {
        return false;
    }
    // ʹ�ü��ص�ͼ���ļ����� Sprite ����
    if (!spriteFileName.empty()) {
        Sprite* mySprite = Sprite::create(spriteFileName);

        // ���� Sprite ��λ�õ����ԣ�����ʵ��������е�����
        setPosition(Vec2(0, 0));  // ����λ��

        if (mySprite) {
            mySprite->setName(spriteFileName); // �����ӽڵ��������ͼƬ������ͬ
            addChild(mySprite); // �� Sprite ���Ϊ Carrot ���ӽڵ�
        }
    }


    // ��������ж���ĳ�ʼ������
    health = 10; // ��ʼ��Ѫ��Ϊ10
    level = 1;   // ��ʼ���ȼ�Ϊ1

    return true;
}

Carrot* Carrot::create() {
    Carrot* mycarrot = new Carrot();
    if (mycarrot && mycarrot->init()) {
        mycarrot->autorelease();
        return mycarrot; // ���ش����� Carrot ����
    }
    else {
        CC_SAFE_DELETE(mycarrot);
        return nullptr;
    }
}

bool Carrot::if_upgrade() {
    
    if (money - 100 * level >= 0 && level < CARROT_LEVEL) {
        money -= 100 * level;
        level++;
        health += 5;
        // ��������ø��º�������������
        updateSpriteFileName();
        return true;
    }
    return false;
}

bool Carrot::health_decrease(int num) {
    if (health - num < 0)
        return false;
    else {
        health -= num;

        // ���ø��º�������������
        updateSpriteFileName();

        return true;
    }
}

void Carrot::updateSpriteFileName() {
    // ����Ѫ������
    int healthLevel = std::min((health / 1) + 1, 10); // ��1Ϊһ������Ļ�����������С�ڵ���10


    // �����µ�ͼƬ�ļ�·��
    std::string newSpriteFileName = "carrot_" + std::to_string(healthLevel) + ".png";

    // �����·���;�·����ͬ���Ž��и���
    if (newSpriteFileName != spriteFileName) {
        // ��ȡ��Ϊ spriteFileName ���ӽڵ�
        Sprite* mySprite = dynamic_cast<Sprite*>(getChildByName(spriteFileName));

        // ������ڣ��ͽ����Ƴ�
        if (mySprite) {
            removeChild(mySprite,true);
        }

        // �����µ�ͼƬ�ļ�·��
        spriteFileName = newSpriteFileName;

        // �����µ� Sprite ����
        mySprite = Sprite::create(spriteFileName);

        // �� Sprite ���Ϊ Carrot ���ӽڵ�
        if (mySprite) {
            mySprite->setName(spriteFileName); // �����ӽڵ��������ͼƬ������ͬ
            addChild(mySprite);
        }
    }
}




