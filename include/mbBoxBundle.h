#pragma once
#include "region.h"

static Point mbbSize = Config::Instance()->get("region.mbBoxBundle.size");

class MbBoxBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    MbBoxBundle(int x, int y) : Region({x, y, mbbSize.x, mbbSize.y}) {
        texture = ResMgr::Instance()->findTexture("mb_box_bundle");
        returnTexture = ResMgr::Instance()->findTexture("mb_box");
    }
    ~MbBoxBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};
