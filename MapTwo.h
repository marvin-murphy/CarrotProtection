#pragma once
#ifndef MAP_TWO_H
#define MAP_TWO_H

#include "cocos2d.h"
#include "SelectScene.h"

class MapTwo : public SelectScene
{
public:
    EventListenerTouchOneByOne* listener;

    static cocos2d::Scene* createScene();
    virtual bool init();
    void MapTwo::update(float dt);
    void MapTwo::initSelect(int x, int y);
    void MapTwo::isOK(int x, int y, int tag);
    void MapTwo::countMoney(float dt);
    void MapTwo::countWaves(float dt);
    void MapTwo::refreshMonsters(float dt);
    CREATE_FUNC(MapTwo);

};

#endif

