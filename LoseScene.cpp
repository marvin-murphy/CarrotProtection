#include "LoseScene.h"
#include "Map_1.h"
#include "HelloWorldScene.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"
#include "cocos2d.h"
#include "PauseScene.h"
#include "AudioEngine.h"


USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d;

Scene* LoseScene::createScene()
{
    return LoseScene::create();
}

bool LoseScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    cocos2d::AudioEngine::play2d("Lose.mp3");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //地图背景图设置
    auto background = Sprite::create("BG1.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);

    //通关告示栏设置
    auto woodBg = Sprite::create("woodbg_notice.png");
    woodBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(woodBg, 0);

    //通关提示
    auto passSign = Label::createWithTTF("YOU LOSE...", "fonts/Marker Felt.ttf", 100);
    passSign->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30));
    this->addChild(passSign, 1);

    //返回选关界面
    auto backToSelect = Button::create("stagemap_toolbar_home.png");
    backToSelect->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 80));
    backToSelect->addClickEventListener([=](Ref*) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectScene::create(), Color3B::BLACK));
        });
    this->addChild(backToSelect, 1);

    return true;
}