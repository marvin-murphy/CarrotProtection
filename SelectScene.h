#pragma once
#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::ui;

enum MapTags {
    // �ؿ���ǩ
    TAG_MAP_1,
    TAG_MAP_2,
    TAG_MAP_3,
    TAG_MAP_4,
    TAG_MAP_5,
    // ҳ���ǩ
    TAG_MAP_IMAGE = 2000,
    // ������ǩ
    TAG_LOCK_IMAGE = 2100,
    // ��ɱ�ǩ
    TAG_FINISH_IMAGE = 2200,
    // ��ͼ��ǩ
    TAG_PAGE_VIEW


};

class SelectScene : public cocos2d::Scene
{
private:
    // ����Ƿ�����
    bool isLock = false; // ��ӹؿ��Ƿ���ɵĽӿ�

    // ����Ƿ���ɹؿ�
    bool isFinish = false; // ��ӹؿ��Ƿ���ɵĽӿ�
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void scroll();

    void updateMapState(int pageIndex);

    void GameScene(Ref* sender);

    CREATE_FUNC(SelectScene);
};



#endif