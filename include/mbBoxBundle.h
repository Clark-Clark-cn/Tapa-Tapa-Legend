#pragma once
#include "region.h"

class MbBoxBundle : public Region
{
public:
    MbBoxBundle(int x, int y) : Region({x, y, 160, 88}) {}
    ~MbBoxBundle() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
};
