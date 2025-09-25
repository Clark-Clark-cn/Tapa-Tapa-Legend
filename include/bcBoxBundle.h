#pragma once
#include "region.h"

class BcBoxBundle : public Region
{
public:
    BcBoxBundle(int x, int y) : Region({x, y, 160, 88}) {}
    ~BcBoxBundle() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
};