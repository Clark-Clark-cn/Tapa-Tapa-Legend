#pragma once
#include "region.h"

class MbBoxBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    MbBoxBundle(int x, int y) : Region({x, y, 160, 88}) {
        texture = ResMgr::Instance()->findTexture("mb_box_bundle");
        returnTexture = ResMgr::Instance()->findTexture("mb_box");
    }
    ~MbBoxBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};
