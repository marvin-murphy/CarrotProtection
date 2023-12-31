#pragma once
#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::ui;

enum MapTags {
    // 关卡标签
    TAG_MAP_1,
    TAG_MAP_2,
    TAG_MAP_3,
    TAG_MAP_4,
    TAG_MAP_5,
    // 页面标签
    TAG_MAP_IMAGE = 2000,
    // 锁定标签
    TAG_LOCK_IMAGE = 2100,
    // 完成标签
    TAG_FINISH_IMAGE = 2200,
    // 视图标签
    TAG_PAGE_VIEW


};

class SelectScene : public cocos2d::Scene
{
private:
    // 添加是否锁定
    bool isLock = false; // 添加关卡是否完成的接口

    // 添加是否完成关卡
    bool isFinish = false; // 添加关卡是否完成的接口
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void scroll();

    void updateMapState(int pageIndex);

    void GameScene(Ref* sender);

    CREATE_FUNC(SelectScene);
};



#endif