#pragma once
#include "region.h"

class RcpBoxBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    RcpBoxBundle(int x, int y) : Region({x, y, 160, 88}) {
        texture = ResMgr::Instance()->findTexture("rcp_box_bundle");
        returnTexture = ResMgr::Instance()->findTexture("rcp_box");
    }
    ~RcpBoxBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};