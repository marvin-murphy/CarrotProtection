#include "Map_1.h"
#include "HelloWorldScene.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"
#include "cocos2d.h"
#include "PauseScene.h"
#include "WinScene.h"
#include "LoseScene.h"
#include "move.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d;

#define blockHeight 60
#define blockWidth 60

int money = 500;
int towerLevel = 1;
int curWaves = 1;
int finalWaves = 5;
int gameState = 1;//游戏继续
int initNum = 10;//第几个放置位置(10为第一个)
int towerNum = 0;
int carrotLevel = 1;//萝卜等级
int pos[20] = { 0 };
extern int isWin;

std::vector<Monster*> monstersContainer; 
Carrot* myCarrot = new Carrot(); 
std::vector<Tower*> towersContainer;
std::vector<Bullet*> bulletsContainer;
GameLayer* gameLayer = new GameLayer(&monstersContainer, myCarrot, &towersContainer,&bulletsContainer); // ...在这里进行游戏逻辑或场景设置... // 记得在不再需要时适当地清理资源 // 例如，删除gameLayer, myCarrot等。


Scene* MapOne::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = MapOne::create();
    scene->addChild(layer);
    return scene;
}

bool MapOne::init()//第一张地图的初始化
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //地图背景图设置
    auto background = Sprite::create("BG1.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background, 0);


    //怪兽路线图设置
    auto route = Sprite::create("BG0.png");
    route->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 30));
    this->addChild(route, 0);


    //入口设置
    auto monsterEnter = Sprite::create("start01.png");
    monsterEnter->setPosition(Vec2(3 * blockWidth, 9 * blockHeight - 30));
    this->addChild(monsterEnter, 2);


    //顶栏设置
    auto topBg = Sprite::create("top_bg.png");
    topBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - 42));
    this->addChild(topBg, 2);


    //波次栏设置
    auto wavesBg = Sprite::create("waves_bg.png");
    wavesBg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y - 44));
    this->addChild(wavesBg, 2);

    
    //总共波次
    auto wavesGuide0 = Label::createWithTTF("5 WAVES", "fonts/Marker Felt.ttf", 25);
    wavesGuide0->setPosition(Vec2(visibleSize.width / 2 + origin.x+20, visibleSize.height + origin.y - 38));
    this->addChild(wavesGuide0, 3);


    //添加计时器(塔、敌人更新等)
    scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(MapOne::countMoney), 0.2f);
    this->schedule(CC_SCHEDULE_SELECTOR(MapOne::countWaves), 0.2f);
    this->schedule(CC_SCHEDULE_SELECTOR(MapOne::refreshMonsters), 1.0f);

    //第一波
    gameLayer->createWave(1, 5);



    myCarrot->create(myCarrot);
    this->addChild(myCarrot, 2);

    auto carrotUpdate = Button::create("mission_succeed.png");
    carrotUpdate->setTag(99);
    carrotUpdate->setPosition(Vec2(960, 530));
    carrotUpdate->addClickEventListener([=](Ref*) {
        myCarrot->if_upgrade();
        if (carrotLevel >= 2) {
            this->removeChildByTag(99);
        }
        carrotLevel++;
        });
    this->addChild(carrotUpdate, 2);

 

    this->addChild(gameLayer, 2);


    //添加炮台按钮(从外圈到内圈)
    int x1 = 4 * blockWidth + 20, y1 = 6 * blockHeight + 10;
    initSelect(x1, y1);

    int x2 = 4 * blockWidth + 20, y2 = 5 * blockHeight - 10;
    initSelect(x2, y2);

    int x3 = 4 * blockWidth + 20, y3 = 2 * blockHeight + 10;
    initSelect(x3, y3);

    int x4 = 5 * blockWidth + 35, y4 = 1 * blockHeight - 5;
    initSelect(x4, y4);

    int x5 = 9 * blockWidth + 25, y5 = 1 * blockHeight - 5;
    initSelect(x5, y5);

    int x6 = 12 * blockWidth + 5, y6 = 1 * blockHeight - 5;
    initSelect(x6, y6);

    int x7 = 13 * blockWidth + 22, y7 = 1 * blockHeight - 5;
    initSelect(x7, y7);

    int x8 = 14 * blockWidth + 40, y8 = 2 * blockHeight + 10;
    initSelect(x8, y8);

    int x9 = 14 * blockWidth + 40, y9 = 5 * blockHeight - 10;
    initSelect(x9, y9);

    int x10 = 14 * blockWidth + 40, y10 = 6 * blockHeight+10;
    initSelect(x10, y10);

    int x11 = 7 * blockWidth - 5, y11 = 5 * blockHeight - 10;
    initSelect(x11, y11);

    int x12 = 8 * blockWidth+5, y12 = 4 * blockHeight - 30;
    initSelect(x12, y12);

    int x13 = 9 * blockWidth+25, y13 = 4 * blockHeight - 30;
    initSelect(x13, y13);

    int x14 = 7 * blockWidth - 5, y14 = 7 * blockHeight + 20;
    initSelect(x14, y14);

    int x15 = 5 * blockWidth + 35, y15 = 8 * blockHeight + 40;
    initSelect(x15, y15);

    int x16 = 12 * blockWidth, y16 = 5 * blockHeight - 10;
    initSelect(x16, y16);

    int x17 = 12 * blockWidth, y17 = 6 * blockHeight + 10;
    initSelect(x17, y17);

    int x18 = 13 * blockWidth + 22, y18 = 8 * blockHeight + 40;
    initSelect(x18, y18);

    int x19 = 14 * blockWidth + 40, y19 = 8 * blockHeight + 40;
    initSelect(x19, y19);

    //暂停按钮
    // 绑定按钮点击事件 
    auto pauseBtn = Button::create("pause_0.png");
    pauseBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x + 320, visibleSize.height + origin.y - 44));
    pauseBtn->addClickEventListener([=](Ref*) {
        // 暂停所有游戏逻辑更新
        Director::getInstance()->pause();
        gameState = 0;
        });
    this->addChild(pauseBtn, 4);


    //继续按钮
    auto continueBtn = Button::create("pause_1.png");
    continueBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x + 390, visibleSize.height + origin.y - 44));
    continueBtn->addClickEventListener([=](Ref*) {
        Director::getInstance()->resume();
        gameState = 1;
        });
    this->addChild(continueBtn, 4);


    /* 添加回到上一界面按钮 */
    auto backToSelect = Button::create("menu.png");
    backToSelect->setPosition(Vec2(visibleSize.width / 2 + 460, visibleSize.height + origin.y - 44));
    backToSelect->addClickEventListener([=](Ref*) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, SelectScene::create(), Color3B::BLACK));
        });
    this->addChild(backToSelect, 2);



    return true;
}

void MapOne::update(float dt)
{
    //gameLayer->my_update(dt);
}

void MapOne::initSelect(int x, int y)
{
    auto addTower = Button::create("select_01.png");
    addTower->setTag(initNum);
    addTower->setPosition(Vec2(x, y));
    addTower->addClickEventListener([=](Ref*) {
        int tag = addTower->getTag();
        this->isOK(x, y, tag);
        });
    this->addChild(addTower, 1);
    initNum++;
}

void MapOne::isOK(int x, int y, int tag)
{
    for (int i = 1; i < 4; i++) {
        this->removeChildByTag(i);
    }


    auto back = Button::create("mission_lose.png");
    back->setTag(3);
    back->setPosition(Vec2(x, y - 30));
    back->addClickEventListener([=](Ref*) {
        for (int i = 1; i < 4; i++) {
            this->removeChildByTag(i);
        }
        });
    this->addChild(back, 1);


    if (money >= 100) {

        auto bottleBtn = Button::create("newBottle1.png");
        bottleBtn->setTag(1);
        bottleBtn->setPosition(Vec2(x - 50, y + 50));
        bottleBtn->addClickEventListener([=](Ref*) {


            for (int i = 1; i < 4; i++) {
                this->removeChildByTag(i);
            }
            this->removeChildByTag(tag);


            gameLayer->createTower(1, Vec2(x, y), tag);


            money -= 100;
            if (money <= 0)money = 0;


            //升级第一次
                auto upgradeBtn = Button::create("mission_succeed.png");
                upgradeBtn->setTag(tag * tag * tag);
                upgradeBtn->setPosition(Vec2(x, y + 30));
                upgradeBtn->addClickEventListener([=](Ref*) {
                    for (Tower* tower : towersContainer) {
                        if (tower && tower->getID() == tag) {
                            tower->upgradeTower();
                        }
                    }
                    });
                this->addChild(upgradeBtn, 1);


            auto deleteBtn = Button::create("mission_lose.png");
            deleteBtn->setTag(tag*tag*tag+1);
            deleteBtn->setPosition(Vec2(x, y - 30));
            deleteBtn->addClickEventListener([=](Ref*sender) {
                for (Tower* tower : towersContainer) {
                    if (tower && tower->getID() == tag) {
                        tower->removeTower();
                        this->removeChildByTag(tag * tag * tag);
                        this->removeChildByTag(tag * tag * tag+1);
                        auto plus = Sprite::create("PShit01.png");
                        plus->setPosition(Vec2(x, y));
                        this->addChild(plus, 1);
                    }
                }
                });
            this->addChild(deleteBtn, 1);

            towerNum++;
            });
        this->addChild(bottleBtn, 1);
    }
    else {
        auto bottleBtn = Button::create("newBottle0.png");
        bottleBtn->setTag(1);
        bottleBtn->setPosition(Vec2(x - 50, y + 50));
        this->addChild(bottleBtn, 1);
    }

    if (money >= 120) {
        auto shit = Button::create("Shit01.png");
        shit->setTag(2);
        shit->setPosition(Vec2(x + 50, y + 50));
        shit->addClickEventListener([=](Ref*) {
            for (int i = 1; i < 4; i++) {
                this->removeChildByTag(i);
            }
            this->removeChildByTag(tag);


            gameLayer->createTower(2, Vec2(x, y), tag);


            money -= 120;
            if (money <= 0)money = 0;


            //升级第一次
                auto upgradeBtn = Button::create("mission_succeed.png");
                upgradeBtn->setTag(tag * tag * tag);
                upgradeBtn->setPosition(Vec2(x, y + 30));
                upgradeBtn->addClickEventListener([=](Ref*) {
                    for (Tower* tower : towersContainer) {
                        if (tower && tower->getID() == tag) {
                            tower->upgradeTower();
                        }
                    }
                    });
                this->addChild(upgradeBtn, 1);


            auto deleteBtn = Button::create("mission_lose.png");
            deleteBtn->setTag(tag* tag* tag+1);
            deleteBtn->setPosition(Vec2(x, y - 30));
            deleteBtn->addClickEventListener([=](Ref* sender) {
                for (Tower* tower : towersContainer) {
                    if (tower && tower->getID() == tag) {
                        tower->removeTower();
                        this->removeChildByTag(tag * tag * tag);
                        this->removeChildByTag(tag * tag * tag + 1);
                        auto plus = Sprite::create("PShit01.png");
                        plus->setPosition(Vec2(x, y));
                        this->addChild(plus, 1);
                    }
                }
                });
            this->addChild(deleteBtn, 1);

            towerNum++;
            });
        this->addChild(shit, 1);
    }
    else {
        auto shit = Button::create("Shit00.png");
        shit->setTag(2);
        shit->setPosition(Vec2(x + 50, y + 50));
        this->addChild(shit, 1);
    }


}

void MapOne::countMoney(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //还要加上加钱逻辑

    this->removeChildByTag(9);
    auto coinNum = Label::createWithTTF(std::to_string(money), "fonts/Marker Felt.ttf", 30);
    coinNum->setTag(9);
    coinNum->setPosition(Vec2(visibleSize.width / 2 + origin.x - 400, visibleSize.height + origin.y - 38));
    this->addChild(coinNum, 3);
}

void MapOne::countWaves(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //还要加上波次逻辑

    this->removeChildByTag(8);
    auto wavesGuide = Label::createWithTTF(std::to_string(curWaves), "fonts/Marker Felt.ttf", 25);
    wavesGuide->setTag(8);
    wavesGuide->setPosition(Vec2(visibleSize.width / 2 + origin.x - 60, visibleSize.height + origin.y - 38));
    this->addChild(wavesGuide, 3);
}

void MapOne::refreshMonsters(float dt)
{
    if (myCarrot->getHealth() <= 0) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, LoseScene::create(), Color3B::BLACK));
        isWin = 0;
    }
    if (curWaves >= finalWaves&& gameLayer->allMonstersDead()) {
        if (myCarrot->getHealth() > 0) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WinScene::create(), Color3B::BLACK)); 
            isWin = 1;
        }
        else {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, LoseScene::create(), Color3B::BLACK));
            isWin = 0;
        }
    }
    if(gameLayer->allMonstersDead())
    {
        curWaves++;
        if (curWaves == 2) {
            gameLayer->createWave(1, 10);
        }
        else if (curWaves == 3) {
            gameLayer->createWave(2, 10);
        }
        else if (curWaves == 4) {
            gameLayer->createWave(3, 5);
        }
        else if (curWaves == 5) {
            gameLayer->createWave(3, 10);
        }
    }


}

void MapOne::isHit()
{

}
