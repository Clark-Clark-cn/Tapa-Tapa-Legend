#pragma once
#include "meal.h"
#include "region.h"
#include <SDL.h>

class CursorMgr
{
public:
    static CursorMgr *Instance();

    void onInput(const SDL_Event &event);
    void onRender(SDL_Renderer *renderer);
    void onUpdate(float delta);

    void setPicked(Meal meal, Region* src = nullptr);
    Meal getPicked();
    Region* getSource();
    void startReturn();

private:
    CursorMgr();
    ~CursorMgr();

private:
    static CursorMgr *manager;

    Meal mealPicked = Meal::None; // 当前抓取的餐品
    Region* source = nullptr;      // 餐品来源区域
    SDL_Point posCursor = {0};    // 光标位置
    bool isMouseLbtnDown = false; // 鼠标左键是否按下

    // 新增：光标动画相关
    Meal mealReturning = Meal::None; // 当前归位的餐品
    bool isReturning = false; // 是否正在归位
    SDL_Point returnStartPos; // 归位起始位置
    SDL_Point returnEndPos;   // 归位结束位置
    float returnSpeed = Config::Instance()->get("cursor.returnTime").asFloat(); // 归位动画速度（单位：秒）
    float returnProgress = 0.0f;  // 归位动画进度
    SDL_Texture* textureReturn = nullptr; // 归位动画纹理
};
