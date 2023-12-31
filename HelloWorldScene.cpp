/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SettingsScene.h"
#include "SelectScene.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //moster4
    auto monster_4 = Sprite::create("front_monster_4.png");
    monster_4->setPosition(origin.x + visibleSize.width / 2 - 400, origin.y + visibleSize.height / 2 + 150);
    this->addChild(monster_4, 1);

    //moster3
    auto monster_3 = Sprite::create("front_monster_3.png");
    monster_3->setPosition(origin.x + visibleSize.width / 2 - 420, origin.y + visibleSize.height / 2 - 120);
    this->addChild(monster_3, 1);

    //moster1
    auto monster_1 = Sprite::create("front_monster_1.png");
    monster_1->setPosition(origin.x + visibleSize.width / 2 - 335, origin.y + visibleSize.height / 2 - 155);
    this->addChild(monster_1, 1);

    //moster2
    auto monster_2 = Sprite::create("front_monster_2.png");
    monster_2->setPosition(origin.x + visibleSize.width / 2 - 250, origin.y + visibleSize.height / 2 - 170);
    this->addChild(monster_2, 1);

    //moster6
    auto monster_6 = Sprite::create("front_monster_6.png");
    monster_6->setPosition(origin.x + visibleSize.width / 2 + 500, origin.y + visibleSize.height / 2 - 80);
    this->addChild(monster_6, 1);

    //moster5
    auto monster_5 = Sprite::create("front_monster_5.png");
    monster_5->setPosition(origin.x + visibleSize.width / 2 + 330, origin.y + visibleSize.height / 2 - 155);
    this->addChild(monster_5, 1);

    //carrot
    auto carrot = Sprite::create("front_carrot.png");
    carrot->setPosition(origin.x + visibleSize.width / 2 + 50, origin.y + visibleSize.height / 2 - 390);
    this->addChild(carrot, 1);

    //smoke1
    auto smoke_1 = Sprite::create("front_smoke_1.png");
    smoke_1->setPosition(origin.x + visibleSize.width / 2 - 450, origin.y + visibleSize.height / 2 - 147);
    this->addChild(smoke_1, 1);

    //smoke3
    auto smoke_3 = Sprite::create("front_smoke_3.png");
    smoke_3->setPosition(origin.x + visibleSize.width / 2 + 460, origin.y + visibleSize.height / 2 - 155);
    this->addChild(smoke_3, 1);


    //开始冒险按钮
    auto beginAdventure = MenuItemImage::create(
        "front_btn_start_normal.png",
        "front_btn_start_pressed.png",
        CC_CALLBACK_1(HelloWorld::beginAdventureCallBack, this));

    if (beginAdventure == nullptr ||
        beginAdventure->getContentSize().width <= 0 ||
        beginAdventure->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2-5;
        float y = origin.y + visibleSize.height / 2+70;
        beginAdventure->setPosition(Vec2(x,y));
    }

    auto menu1 = Menu::create(beginAdventure, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);


    //天天向上按钮
    auto anotherAdventure = MenuItemImage::create(
        "front_btn_floor_normal.png",
        "front_btn_floor_pressed.png",
        CC_CALLBACK_1(HelloWorld::noResponse, this));

    if (anotherAdventure == nullptr ||
        anotherAdventure->getContentSize().width <= 0 ||
        anotherAdventure->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2 - 5;
        float y = origin.y + visibleSize.height / 2 - 55;
        anotherAdventure->setPosition(Vec2(x, y));
    }

    auto menu2 = Menu::create(anotherAdventure, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);


    //设置按钮
    auto settingsBtn = ui::Button::create(
        "front_btn_setting_normal.png",
        "front_btn_setting_pressed.png");

    if (settingsBtn == nullptr ||
        settingsBtn->getContentSize().width <= 0 ||
        settingsBtn->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2-363;
        float y = origin.y + visibleSize.height / 2+100;
        settingsBtn->setPosition(Vec2(x,y));
    }

    settingsBtn->addClickEventListener([=](Ref*) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SettingsScene::create(), Color3B::BLACK)); // 切换到新场景
        });

    this->addChild(settingsBtn, 1);



    //锁图
    auto everyDayBtnLocked = Sprite::create("front_btn_floor_locked.png");
    everyDayBtnLocked->setPosition(origin.x + visibleSize.width / 2 + 140, origin.y + visibleSize.height / 2 - 55);
    this->addChild(everyDayBtnLocked, 1);


    //背景2
    auto backGround2 = Sprite::create("front_front.png");
    backGround2->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(backGround2, 1);



    //主要背景
    auto sprite = Sprite::create("front_bg.png");
    if (sprite == nullptr){ problemLoading("'front_bg.png'");}
    else{
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;




    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    // add "HelloWorld" splash screen"

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}

void HelloWorld::beginAdventureCallBack(Ref* pSender)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectScene::create(), Color3B::BLACK)); // 切换到新场景
}

void HelloWorld::noResponse(Ref* pSender)
{
    CCLOG("HelloWorld::noResponse");
}
