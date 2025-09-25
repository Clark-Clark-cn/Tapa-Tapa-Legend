#pragma once
#include "region.h"

class ColaBundle : public Region
{
public:
    ColaBundle(int x, int y) : Region({x, y, 120, 124}) {}
    ~ColaBundle() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
};