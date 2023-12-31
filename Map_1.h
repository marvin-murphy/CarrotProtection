#pragma once
#ifndef MAP_ONE_H
#define MAP_ONE_H

#include "cocos2d.h"
#include "SelectScene.h"

class MapOne : public SelectScene
{
public:
    EventListenerTouchOneByOne* listener;

    static cocos2d::Scene* createScene();
    virtual bool init();
    void MapOne::update(float dt);
    void MapOne::initSelect(int x, int y);
    void MapOne::isOK(int x, int y, int tag);
    void MapOne::countMoney(float dt);
    void MapOne::countWaves(float dt);
    void MapOne::refreshMonsters(float dt);
    void MapOne::isHit();
    CREATE_FUNC(MapOne);

};

#endif

