#include "SettingsScene.h"
#include "HelloWorldScene.h"
#include <string.h>
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
    return SettingsScene::create();
}

bool SettingsScene::init()
{
    /* ��ʼ������ */
    if (!Scene::init())
    {
        return false;
    }

    /* ��ȡ��Ļ��С */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto sprite = Sprite::create("woodbg_notice.png");
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(sprite, 1);

    auto backGround1 = Sprite::create("BG1.png");
    backGround1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround1, 0);

    /* ������ǩ */
    auto quitGuide = Label::createWithTTF("QUIT GAME", "fonts/Marker Felt.ttf", 35);
    quitGuide->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+25));
    this->addChild(quitGuide,3);

    /* ���������水ť */
    auto backToWelcome = ui::Button::create("stagemap_toolbar_home.png", "stagemap_toolbar_home.png");
    backToWelcome->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-90)); // ���ð�ť�ĳ�ʼλ��
    backToWelcome->addClickEventListener([=](Ref*) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::create(), Color3B::BLACK)); // �л����³���

        });
    this->addChild(backToWelcome, 4);

    auto quitGame = ui::Button::create("btn_red_m.png", "btn_red_m_pressed.png");
    quitGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+25));
    quitGame->addClickEventListener([=](Ref*) {
        Director::getInstance()->end();
        });
    this->addChild(quitGame, 2);
}
