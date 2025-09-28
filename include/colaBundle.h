#pragma once
#include "region.h"

class ColaBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    ColaBundle(int x, int y) : Region({x, y, 120, 124}) {
        texture = ResMgr::Instance()->findTexture("cola_bundle");
        returnTexture = ResMgr::Instance()->findTexture("cola");
    }
    ~ColaBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};