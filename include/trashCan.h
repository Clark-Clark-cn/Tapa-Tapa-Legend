#pragma once

#include "region.h"

class TrashCan:public Region{
public:
    TrashCan(int x, int y) : Region({x, y, 143, 140}) {}
    ~TrashCan() = default;

    bool onCursorUp() override;
    void onRender(SDL_Renderer *renderer) override;
};