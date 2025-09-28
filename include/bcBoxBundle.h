#pragma once
#include "region.h"

class BcBoxBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    BcBoxBundle(int x, int y) : Region({x, y, 160, 88}) {
        texture = ResMgr::Instance()->findTexture("bc_box_bundle");
        returnTexture = ResMgr::Instance()->findTexture("bc_box");
    }
    ~BcBoxBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};