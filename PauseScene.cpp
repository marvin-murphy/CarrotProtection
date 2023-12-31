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
    /* 初始化场景 */
    if (!Scene::init())
    {
        return false;
    }


    /* 获取屏幕大小 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /* 添加背景1 */
    auto sprite = Sprite::create("adv_menu.png");
    sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(sprite, 1);


    /* 添加背景2 */
    auto backGround1 = Sprite::create("BG1.png");
    backGround1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround1, 0);


    /* 添加继续游戏按钮 */
    auto continueSign = Sprite::create("adv_menu_continue.png");
    continueSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 93));
    this->addChild(continueSign, 3);

    auto continueBtn = ui::Button::create("btn_green_m.png", "btn_green_m_pressed.png");
    continueBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 93)); // 设置按钮的初始位置
    continueBtn->addClickEventListener([=](Ref*) {
        // 恢复游戏逻辑更新
        Director::getInstance()->resume();

        // 弹出暂停场景,返回游戏场景
        Director::getInstance()->popScene();
        });
    this->addChild(continueBtn, 2);


    /* 添加重新开始按钮 */
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


    /* 添加回到上一界面按钮 */
    auto backSign = Sprite::create("adv_menu_home.png");
    backSign->setPosition(Vec2(visibleSize.width / 2 - 93, visibleSize.height / 2 - 152));
    this->addChild(backSign, 3);

    auto backToSelect = ui::Button::create("btn_blue_l.png", "btn_blue_l_pressed.png");
    backToSelect->setPosition(Vec2(visibleSize.width / 2 - 93, visibleSize.height / 2 - 152));
    backToSelect->addClickEventListener([=](Ref*) {
        Director::getInstance()->replaceScene(SelectScene::create());
        });
    this->addChild(backToSelect, 2);


    /* 分享按钮 */
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
