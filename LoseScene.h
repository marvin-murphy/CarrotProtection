#pragma once
#ifndef LOSE_SCENE_H
#define LOSE_SCENE_H

#include "cocos2d.h"
#include "SelectScene.h"

class LoseScene : public SelectScene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoseScene);
};
#endif

