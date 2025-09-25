#pragma once
#include "region.h"

class TbBundle : public Region
{
public:
    TbBundle(int x, int y) : Region({x, y, 112, 96}) {}
    ~TbBundle() = default;

    void onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
};