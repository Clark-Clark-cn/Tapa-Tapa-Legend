#pragma once
#include "region.h"

static Point tbSize = Config::Instance()->get("region.tbBundle.size");

class TbBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    TbBundle(int x, int y) : Region({x, y, tbSize.x, tbSize.y}) {
        texture = ResMgr::Instance()->findTexture("tb_bundle");
        returnTexture = ResMgr::Instance()->findTexture("tb");
    }
    ~TbBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};