#pragma once

#include "region.h"

class UpgradeCover : public Region
{
    SDL_Texture* texture = nullptr;
    float alpha = 255.0f;
public:
    UpgradeCover(int x, int y, int w, int h) : Region({x, y, w, h}) {
        texture = ResMgr::Instance()->findTexture("upgrade");
    }
    ~UpgradeCover() = default;

    void onRender(SDL_Renderer *renderer) override;
    void onUpdate(float delta) override;
};