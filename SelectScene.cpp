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
    /* ��ʼ������ */
    if (!Scene::init())
    {
        return false;
    }

    /* ��ȡ��Ļ��С */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /* ���ñ��� */
    auto backGround = Sprite::create("BG1.png");
    backGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(backGround, 0);


    /* ���������水ť */
    auto backToWelcome = ui::Button::create("winlose_home.png", "winlose_home.png");
    backToWelcome->setPosition(Vec2(40, 610)); // ���ð�ť�ĳ�ʼλ��


    // ��ť����¼������߼�
    backToWelcome->addClickEventListener([=](Ref*) {
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, HelloWorld::create(), Color3B::BLACK)); // �л����³���
        });
    this->addChild(backToWelcome, 1);


    /* ���뻬��ѡ�ز��� */
    SelectScene::scroll();

    return true;
}

void SelectScene::scroll()
{
    // ��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //�����ͼ��
    int mapNum = 5;

    // ������ҳ
    auto pageView = ui::PageView::create();
    pageView->setContentSize(visibleSize);
    pageView->setPosition(origin);
    pageView->setTag(TAG_PAGE_VIEW);
    this->addChild(pageView);

    // ѭ����ӡ�ؿ�Ԥ��ͼ�����뻬������
    for (int i = 0; i < mapNum; i++) {
        // ����ҳ��չʾ����
        auto layout = Layout::create();
        layout->setContentSize(Size(visibleSize.width, visibleSize.height));
        layout->setTag(TAG_MAP_1 + i); 

        // ��ӹؿ�ͼƬ
        if (i == 0) {
            auto mapImage = ImageView::create("BG0.png");
            mapImage->setTag(TAG_MAP_IMAGE);
            mapImage->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2 + 30));
            layout->addChild(mapImage);
            if (isWin == 0) {
                ;
            }
            else {
                // ����finish��ͼ��
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

        // ��ÿһ��ͼ��ӵ�����ҳ����
        pageView->addPage(layout);
    }

    // ��ʼ����ʹ��һҳ��Ϊ��ǰҳ
    this->updateMapState(pageView->getCurrentPageIndex());

    // ���� PageView �¼�������
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
    // ��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto pageView = dynamic_cast<ui::PageView*>(this->getChildByTag(TAG_PAGE_VIEW));

    /* �Ե�ͼ��͸���Ƚ��и��� */
    for (auto& item : pageView->getChildren()) {
        //���ص���Node�࣬��Ҫת����Layout����ImageView��
        auto layout = dynamic_cast<ui::Layout*>(item);
        auto mapImage = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_MAP_IMAGE));
        // �����Ƿ��ǵ�ǰҳ��������͸����
        mapImage->setOpacity(layout->getTag() == (TAG_MAP_1 + pageIndex) ? 255 : 50);

        // ����͸���ȱ仯
        if (isLock) {
            auto lock = dynamic_cast<ui::ImageView*>(layout->getChildByTag(TAG_LOCK_IMAGE));
            lock->setOpacity(layout->getTag() == (TAG_MAP_1 + pageIndex) ? 255 : 50);
        }
    }

    /* ��ÿһҳ�Ĺ̶��������и��� */
    // ����̶������ı�ǩ
    const int TAG_FIXED_PART = 1000;

    // ��ӹ̶�������ÿ��ҳ��Ĳ�������һ��
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

    // �Ƴ���һ����ӵĹ̶�����
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

/* ������Ϸ���� */
void SelectScene::GameScene(Ref* sender)
{
    if (isWin == 0) {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MapOne::create(), Color3B::BLACK)); // �л����³���
    }
    else {
        //Director::getInstance()->replaceScene(TransitionFade::create(0.5f, MapTwo::create(), Color3B::BLACK)); // �л����³���
    }
}