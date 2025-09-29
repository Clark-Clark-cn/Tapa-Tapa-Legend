#pragma once

#include "region.h"

static Point tcSize = Config::Instance()->get("region.trashCan.size");

class TrashCan:public Region{
public:
    TrashCan(int x, int y) : Region({x, y, tcSize.x, tcSize.y}) {}
    ~TrashCan() = default;

    bool onCursorUp() override;
    void onRender(SDL_Renderer *renderer) override;
};