#pragma once
#include "meal.h"
#include "region.h"

class TakeoutBox : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureReturn = nullptr;
public:
    TakeoutBox(int x, int y) : Region({x, y, 92, 50}) {}
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
