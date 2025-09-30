#pragma once

#include <SDL.h>

class regionMgr;

class Screen{
public:
    Screen() = default;
    virtual ~Screen() = default;

    virtual void onInput(const SDL_Event &event) = 0;
    virtual void onRender(SDL_Renderer *renderer) = 0;
    virtual void onUpdate(float delta){}
    virtual void onEnter(){}
    virtual void onExit(){}

    virtual regionMgr* getRegionMgr(){ return nullptr; }
};