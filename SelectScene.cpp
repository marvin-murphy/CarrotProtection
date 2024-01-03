#include "SelectScene.h"
#include "Map_1.h"
#include "HelloWorldScene.h"
#include <string.h>
#include "ui/CocosGUI.h"
#include "cocos/ui/UIImageView.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d;

int isWin = 0;

Scene* SelectScene::createScene()
{
    return SelectScene::create();
}

bool SelectScene::init()
{
    /* 初始化场景 */
    if (!Scene::init())
    {
        return false;
    }

    /* 获取屏幕大小 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /* 设置背景 */
    auto backGround = Sprite::create("BG1.png");
    backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround, 0);


    /* 返回主界面按钮 */
    auto backToWelcome = ui::Button::create("winlose_home.png", "winlose_home.png");
    backToWelcome->setPosition(Vec2(40, 610)); // 设置按钮的初始位置


    // 按钮点击事件处理逻辑
    backToWelcome->addClickEventListener([=](Ref*) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::create(), Color3B::BLACK)); // 切换到新场景
        });
    this->addChild(backToWelcome, 1);


    /* 进入滑动选关部分 */
    SelectScene::scroll();

    return true;
}

void SelectScene::scroll()
{
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //定义地图数
    int mapNum = 5;

    // 创建翻页
    auto pageView = ui::PageView::create();
    pageView->setContentSize(visibleSize);
    pageView->setPosition(origin);
    pageView->setTag(TAG_PAGE_VIEW);
    this->addChild(pageView);

    // 循环打印关卡预览图并加入滑动容器
    for (int i = 0; i < mapNum; i++) {
        // 设置页面展示容器
        auto layout = Layout::create();
        layout->setContentSize(Size(visibleSize.width, visibleSize.height));
        layout->setTag(TAG_MAP_1 + i); 

        // 添加关卡图片
        if (i == 0) {
            auto mapImage = ImageView::create("BG0.png");
            mapImage->setTag(TAG_MAP_IMAGE);
            mapImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
            layout->addChild(mapImage);
            if (isWin == 0) {
                ;
            }
            else {
                // 创建finish的图案
                auto finish = ImageView::create("gold.png");
                finish->setTag(TAG_FINISH_IMAGE);
                finish->setPosition(Vec2(layout->getContentSize().width / 2 + 450, layout->getContentSize().height / 2 - 200));
                layout->addChild(finish);
            }
        }
        if (i == 1) {
            auto mapImage = ImageView::create("2.png");
            mapImage->setTag(TAG_MAP_IMAGE);
            mapImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
            layout->addChild(mapImage);

            if (isWin == 0) {
                auto lock = ImageView::create("front_btn_floor_locked.png");
                lock->setTag(TAG_LOCK_IMAGE);
                lock->setPosition(Vec2(layout->getContentSize().width / 2 + 510, layout->getContentSize().height / 2 - 250));
                layout->addChild(lock);
            }
        }
        if (i == 2) {
            auto mapImage = ImageView::create("3.png");
            mapImage->setTag(TAG_MAP_IMAGE);
            mapImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
            layout->addChild(mapImage);

            auto lock = ImageView::create("front_btn_floor_locked.png");
            lock->setTag(TAG_LOCK_IMAGE);
            lock->setPosition(Vec2(layout->getContentSize().width / 2 + 510, layout->getContentSize().height / 2 - 250));
            layout->addChild(lock);
        }
        if (i == 3) {
            auto mapImage = ImageView::create("4.png");
            mapImage->setTag(TAG_MAP_IMAGE);
            mapImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
            layout->addChild(mapImage);
            auto lock = ImageView::create("front_btn_floor_locked.png");
            lock->setTag(TAG_LOCK_IMAGE);
            lock->setPosition(Vec2(layout->getContentSize().width / 2 + 510, layout->getContentSize().height / 2 - 250));
            layout->addChild(lock);
        }
        if (i == 4) {
            auto mapImage = ImageView::create("5.png");
            mapImage->setTag(TAG_MAP_IMAGE);
            mapImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
            layout->addChild(mapImage);

            auto lock = ImageView::create("front_btn_floor_locked.png");
            lock->setTag(TAG_LOCK_IMAGE);
            lock->setPosition(Vec2(layout->getContentSize().width / 2 + 510, layout->getContentSize().height / 2 - 250));
            layout->addChild(lock);
        }

        if (isWin == 1) {

        }

        // 将每一张图添加到滑动页面上
        pageView->addPage(layout);
    }

    // 初始化，使第一页成为当前页
    this->updateMapState(pageView->getCurrentPageIndex());

    // 设置 PageView 事件监听器
    pageView->addEventListener([this](Ref* sender, ui::PageView::EventType type) {
        if (type == ui::PageView::EventType::TURNING) {
            auto pageView = dynamic_cast<PageView*>(sender);
            int pageIndex = pageView->getCurrentPageIndex();
            this->updateMapState(pageIndex);
        }
        });

}


void SelectScene::updateMapState(int pageIndex)
{
    // 获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pageView = dynamic_cast<ui::PageView*>(this->getChildByTag(TAG_PAGE_VIEW));

    /* 对地图的透明度进行更新 */
    for (auto& item : pageView->getChildren()) {
        //返回的是Node类，需要转换成Layout或者ImageView类
        auto layout = dynamic_cast<ui::Layout*>(item);
        auto mapImage = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_MAP_IMAGE));
        // 根据是否是当前页面来设置透明度
        mapImage->setOpacity(layout->getTag() == (TAG_MAP_1 + pageIndex) ? 255 : 50);

        // 锁的透明度变化
        if (isLock) {
            auto lock = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_LOCK_IMAGE));
            lock->setOpacity(layout->getTag() == (TAG_MAP_1 + pageIndex) ? 255 : 50);
        }
    }

    /* 对每一页的固定部件进行更新 */
    // 定义固定部件的标签
    const int TAG_FIXED_PART = 1000;

    // 添加固定部件，每个页面的部件都不一样
    auto tower1 = ImageView::create("tower_1.png");
    tower1->setTag(TAG_FIXED_PART);
    auto tower2 = ImageView::create("tower_2.png");
    tower2->setTag(TAG_FIXED_PART + 1);
    auto tower3 = ImageView::create("tower_3.png");
    tower3->setTag(TAG_FIXED_PART + 2);
    auto tower4 = ImageView::create("tower_4.png");
    tower4->setTag(TAG_FIXED_PART + 3);
    auto tower5 = ImageView::create("tower_5.png");
    tower5->setTag(TAG_FIXED_PART + 4);
    auto beginSign = Label::createWithTTF("START", "fonts/Marker Felt.ttf", 35);
    beginSign->setTag(TAG_FIXED_PART + 5);
    auto lockSign = Label::createWithTTF("LOCKED", "fonts/Marker Felt.ttf", 35);
    lockSign->setTag(TAG_FIXED_PART + 6);
    auto beginBtn = ui::Button::create("btn_green_m.png", "btn_green_m_pressed.png");
    beginBtn->setTag(TAG_FIXED_PART + 7);
    auto lockBtn = ui::Button::create("btn_red_m.png", "btn_red_m_pressed.png");
    lockBtn->setTag(TAG_FIXED_PART + 8);

    // 移除上一次添加的固定部件
    for (int i = 0; i < 9; i++) {
        this->removeChildByTag(TAG_FIXED_PART + i);
    }

    if (pageIndex == 0) {

        this->removeChildByTag(10);
        this->removeChildByTag(11);

        tower1->setPosition(Vec2(pageView->getContentSize().width / 2 - 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower1);

        tower2->setPosition(Vec2(pageView->getContentSize().width / 2 + 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        beginBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        beginBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED)
            {
                this->GameScene(sender);
            }
            });
        this->addChild(beginBtn);

        beginSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        this->addChild(beginSign, 3);
    }
    if (pageIndex == 1) {
        tower1->setPosition(Vec2(pageView->getContentSize().width / 2 - 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower1);

        tower2->setPosition(Vec2(pageView->getContentSize().width / 2, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower3->setPosition(Vec2(pageView->getContentSize().width / 2 + 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower3);

        if (isWin == 0) {
            lockBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
            lockBtn->setTag(10);
            lockBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
                });
            this->addChild(lockBtn);

            lockSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
            lockSign->setTag(11);
            this->addChild(lockSign, 3);
        }
        else {
            this->removeChildByTag(10);
            this->removeChildByTag(11);
            beginBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
            beginBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
                if (type == Widget::TouchEventType::ENDED)
                {
                    this->GameScene(sender);
                }
                });
            this->addChild(beginBtn);

            beginSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
            this->addChild(beginSign, 3);
        }
    }
    if (pageIndex == 2) {
        this->removeChildByTag(10);
        this->removeChildByTag(11);


        tower1->setPosition(Vec2(pageView->getContentSize().width / 2 - 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower1);

        tower2->setPosition(Vec2(pageView->getContentSize().width / 2, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower4->setPosition(Vec2(pageView->getContentSize().width / 2 + 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower4);

        lockBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        lockBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
            });
        this->addChild(lockBtn);

        lockSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        this->addChild(lockSign, 3);
    }
    if (pageIndex == 3) {
        this->removeChildByTag(10);
        this->removeChildByTag(11);


        tower2->setPosition(Vec2(pageView->getContentSize().width / 2 - 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower5->setPosition(Vec2(pageView->getContentSize().width / 2 + 30, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower5);

        lockBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        lockBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
            });
        this->addChild(lockBtn);

        lockSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        this->addChild(lockSign, 3);
    }
    if (pageIndex == 4) {
        this->removeChildByTag(10);
        this->removeChildByTag(11);


        tower2->setPosition(Vec2(pageView->getContentSize().width / 2 - 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower2);

        tower3->setPosition(Vec2(pageView->getContentSize().width / 2, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower3);

        tower4->setPosition(Vec2(pageView->getContentSize().width / 2 + 60, pageView->getContentSize().height / 2 - 160));
        this->addChild(tower4);

        lockBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        lockBtn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
            });
        this->addChild(lockBtn);

        lockSign->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
        this->addChild(lockSign, 3);
    }
}

/* 进入游戏场景 */
void SelectScene::GameScene(Ref* sender)
{
    if (isWin == 0) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MapOne::create(), Color3B::BLACK)); // 切换到新场景
    }
    else {
        //Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MapTwo::create(), Color3B::BLACK)); // 切换到新场景
    }
}