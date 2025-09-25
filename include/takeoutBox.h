#pragma once
#include "meal.h"
#include "region.h"

class TakeoutBox : public Region
{
public:
    TakeoutBox(int x, int y) : Region({x, y, 92, 32}) {}
    ~TakeoutBox() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;

private:
    Meal meal = Meal::None;

private:
    bool canPlace(Meal target);
};
