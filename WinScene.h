#pragma once

#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include "cocos2d.h"
#include "SelectScene.h"

class WinScene : public SelectScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(WinScene);
};
#endif
