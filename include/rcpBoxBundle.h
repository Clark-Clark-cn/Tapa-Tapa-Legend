#pragma once
#include "region.h"

class RcpBoxBundle : public Region
{
public:
    RcpBoxBundle(int x, int y) : Region({x, y, 160, 88}) {}
    ~RcpBoxBundle() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
};