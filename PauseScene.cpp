#include "PauseScene.h"
#include "SelectScene.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "Map_1.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d;

Scene* PauseScene::createScene()
{
    return PauseScene::create();
}
bool PauseScene::init()
{
    /* ��ʼ������ */
    if (!Scene::init())
    {
        return false;
    }


    /* ��ȡ��Ļ��С */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /* ��ӱ���1 */
    auto sprite = Sprite::create("adv_menu.png");
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(sprite, 1);


    /* ��ӱ���2 */
    auto backGround1 = Sprite::create("BG1.png");
    backGround1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround1, 0);


    /* ��Ӽ�����Ϸ��ť */
    auto continueSign = Sprite::create("adv_menu_continue.png");
    continueSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 93));
    this->addChild(continueSign, 3);

    auto continueBtn = ui::Button::create("btn_green_m.png", "btn_green_m_pressed.png");
    continueBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 93)); // ���ð�ť�ĳ�ʼλ��
    continueBtn->addClickEventListener([=](Ref*) {
        // �ָ���Ϸ�߼�����
        Director::getInstance()->resume();

        // ������ͣ����,������Ϸ����
        Director::getInstance()->popScene();
        });
    this->addChild(continueBtn, 2);


    /* ������¿�ʼ��ť */
    auto restartSign = Sprite::create("adv_menu_restart.png");
    restartSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
    this->addChild(restartSign, 3);

    auto restartBtn = ui::Button::create(
        "btn_blue_m.png",
        "btn_blue_m_pressed.png");
    restartBtn->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 30));
    restartBtn->addClickEventListener([=](Ref*) {
        Director::getInstance()->replaceScene(MapOne::create());
        });
    this->addChild(restartBtn, 2);


    /* ��ӻص���һ���水ť */
    auto backSign = Sprite::create("adv_menu_home.png");
    backSign->setPosition(Vec2(visibleSize.width / 2 - 93, visibleSize.height / 2 - 152));
    this->addChild(backSign, 3);

    auto backToSelect = ui::Button::create("btn_blue_l.png", "btn_blue_l_pressed.png");
    backToSelect->setPosition(Vec2(visibleSize.width / 2 - 93, visibleSize.height / 2 - 152));
    backToSelect->addClickEventListener([=](Ref*) {
        Director::getInstance()->replaceScene(SelectScene::create());
        });
    this->addChild(backToSelect, 2);


    /* ����ť */
    auto shareSign = Sprite::create("adv_menu_weibo.png");
    shareSign->setPosition(Vec2(visibleSize.width / 2 + 95, visibleSize.height / 2 - 152));
    this->addChild(shareSign, 3);

    auto shareBtn = ui::Button::create("btn_blue_l.png", "btn_blue_l_pressed.png");
    shareBtn->setPosition(Vec2(visibleSize.width / 2 + 95, visibleSize.height / 2 - 152));
    shareBtn->addClickEventListener([=](Ref*) {
        });
    this->addChild(shareBtn, 2);
    return true;
}
