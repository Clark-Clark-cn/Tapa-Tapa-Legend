#pragma once
#include "region.h"

static Point sbSize = Config::Instance()->get("region.spriteBundle.size");

class SpriteBundle : public Region
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* returnTexture = nullptr;
public:
    SpriteBundle(int x, int y) : Region({x, y, sbSize.x, sbSize.y}) {
        texture = ResMgr::Instance()->findTexture("sprite_bundle");
        returnTexture = ResMgr::Instance()->findTexture("sprite");
    }
    ~SpriteBundle() = default;

    bool onCursorUp() override;
    void onCursorDown() override;
    void onRender(SDL_Renderer *renderer) override;
    SDL_Texture* getTextureForReturn() override {return returnTexture; }
};
