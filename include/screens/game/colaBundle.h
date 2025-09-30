#pragma once
#include "region.h"

static Point cbSize = Config::Instance()->get("region.colaBundle.size");

class ColaBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    ColaBundle(int x, int y) : Region({x, y, cbSize.x, cbSize.y}) {
        texture = ResMgr::Instance()->findTexture("cola_bundle");
        returnTexture = ResMgr::Instance()->findTexture("cola");
    }
    ~ColaBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};