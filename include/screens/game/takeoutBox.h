#pragma once
#include "meal.h"
#include "region.h"

static Point tb2Size = Config::Instance()->get("region.takeoutBox.size");

class TakeoutBox : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureReturn = nullptr;
public:
    TakeoutBox(int x, int y) : Region({x, y, tb2Size.x, tb2Size.y}) {}
    ~TakeoutBox() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    void onReturn(Meal meal) override;
    SDL_Texture* getTextureForReturn() override {return textureReturn; }

private:
    Meal meal = Meal::None;

private:
    bool canPlace(Meal target);
};
