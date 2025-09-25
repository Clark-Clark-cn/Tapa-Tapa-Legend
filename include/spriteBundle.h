#pragma once
#include "region.h"

class SpriteBundle : public Region
{
public:
    SpriteBundle(int x, int y) : Region({x, y, 120, 124}) {}
    ~SpriteBundle() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
};
