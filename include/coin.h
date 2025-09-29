#pragma once

#include "region.h"
#include <string>

extern int coinCounter; // 用于生成唯一ID

class Coin: public Region {
    std::string id;
public:
    Coin(int x, int y, std::string id) : Region({x, y, 30, 30}), id(std::move(id)) {}
    ~Coin() = default;
    void onRender(SDL_Renderer *renderer)override;
    bool onCursorUp()override;
    void onCursorDown()override { onCursorUp(); }
};