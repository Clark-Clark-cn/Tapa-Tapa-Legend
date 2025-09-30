#pragma once

#include "../screen.h"
#include "regionMgr.h"

class MainScreen : public Screen{
    regionMgr mgr;
public:
    MainScreen();
    ~MainScreen()=default;

    void onInput(const SDL_Event& event)override;
    void onRender(SDL_Renderer* renderer)override;

    regionMgr* getRegionMgr()override;
};