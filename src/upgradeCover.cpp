#include "screens/game/upgradeCover.h"
#include "regionMgr.h"
#include "screenMgr.h"

void UpgradeCover::onRender(SDL_Renderer *renderer)
{
    SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(alpha));
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    if (isDebug)SDL_RenderDrawRect(renderer, &rect);
}

void UpgradeCover::onUpdate(float delta)
{
    rect.y -= 5 * delta * 50;
    alpha -= 500 * delta;
    static auto regionMgr = ScreenMgr::Instance()->getScreen(ScreenID::Game)->getRegionMgr();
    if (alpha < 0) regionMgr->markForRemoval(this);
}