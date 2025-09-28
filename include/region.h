#pragma once
#include <SDL.h>
#include "meal.h"

class Region
{
public:
    Region() = default;
    Region(const SDL_Rect &rect) : rect(rect) {}
    ~Region() = default;

    virtual void onUpdate(float delta) {}
    virtual void onRender(SDL_Renderer *renderer) {}
    virtual void onCursorDown() {}
    virtual void onCursorUp() {}
    virtual void onReturn(Meal meal) {}

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