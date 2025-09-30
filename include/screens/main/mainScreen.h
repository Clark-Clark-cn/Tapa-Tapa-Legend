#pragma once

#include "../screen.h"
#include "regionMgr.h"

class MainScreen : public Screen{
    regionMgr mgr;
public:
    MainScreen();
    ~MainScreen()=default;

    void onInput(const SDL_Event& event);
    void onRender(SDL_Renderer* renderer);

    regionMgr* getRegionMgr()override;
};