#include "Carrot.h"

extern int money;

Carrot::Carrot() : health(0), level(0) {
    // ���캯������Ҫ��������г�ʼ��
    spriteFileName = "mysprite.png"; // Ĭ��ͼ���ļ�·��
}

bool Carrot::init() {
    if (!Sprite::init()) {
        return false;
    }
    // ʹ�ü��ص�ͼ���ļ����� Sprite ����
    if (!spriteFileName.empty()) {
        Sprite* mySprite = Sprite::create(spriteFileName);
        if (mySprite) {
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


