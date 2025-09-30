#pragma once
#include <SDL.h>
#include "screens/game/meal.h"
#include "resMgr.h"
#include "config.h"


extern bool isDebug;
class Region
{
public:
    Region() = default;
    Region(const SDL_Rect &rect) : rect(rect) {}
    ~Region() = default;

    virtual void onUpdate(float delta) {}
    virtual void onRender(SDL_Renderer *renderer) {}
    virtual void onCursorDown() {}
    virtual bool onCursorUp() {return false; }
    virtual void onCursorRightDown() {}
    virtual void onReturn(Meal meal) {}
    virtual SDL_Texture* getTextureForReturn() { return nullptr; }

    void setRect(const SDL_Rect &rect)
    {
        this->rect = rect;
    }

    const SDL_Rect &getRect() const
    {
        return rect;
    }

protected:
    SDL_Rect rect;
};