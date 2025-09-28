#pragma once
#include "region.h"
#include "timer.h"
#include "meal.h"

class MicrowaveOven : public Region
{
public:
    MicrowaveOven(int x, int y);
    ~MicrowaveOven() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onUpdate(float delta) override;
    void onRender(SDL_Renderer *renderer) override;
    void onReturn(Meal meal) override;

private:
    Timer timer;                  // 工作定时器
    bool isWorking = false;       // 当前是否正在工作
    Meal mealTarget = Meal::None; // 加工出的目标餐品

private:
    bool canPlace(Meal target);
};
