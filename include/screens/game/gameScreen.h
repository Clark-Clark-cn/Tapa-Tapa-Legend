#pragma once

#include <SDL.h>
#include "timer.h"
#include "screens/screen.h"
#include "regionMgr.h"

class GameScreen : public Screen
{
private:
    SDL_Texture* background = nullptr;
    SDL_Rect bgRect;
    Timer timer;
    Timer timerChangeScreen;
    regionMgr mgr;
    bool paused = false;
    bool gameOver = false;
    float gameOverProgress = 0.0f;
    int moneyBegin=0;
public:
    GameScreen();
    ~GameScreen()=default;

    void onInput(const SDL_Event &event) override;
    void onRender(SDL_Renderer *renderer) override;
    void onUpdate(float delta) override;
    void onEnter() override;
    void onExit() override;

    regionMgr* getRegionMgr() override { return &mgr; }

};