#pragma once
#include "meal.h"

#include <SDL.h>

class CursorMgr
{
public:
    static CursorMgr *Instance();

    void onInput(const SDL_Event &event);
    void onRender(SDL_Renderer *renderer);

    void setPicked(Meal meal);
    Meal getPicked();

private:
    CursorMgr();
    ~CursorMgr();

private:
    static CursorMgr *manager;

    Meal mealPicked = Meal::None; // 当前抓取的餐品
    SDL_Point posCursor = {0};    // 光标位置
    bool isMouseLbtnDown = false; // 鼠标左键是否按下
};
