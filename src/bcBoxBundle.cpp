#include "bcBoxBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

void BcBoxBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::BraisedChicken_Box)
        CursorMgr::Instance()->setPicked(Meal::None);
}

void BcBoxBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::BraisedChicken_Box, this);
}

void BcBoxBundle::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("bc_box_bundle");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}
