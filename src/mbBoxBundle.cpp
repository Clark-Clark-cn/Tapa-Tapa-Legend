#include "mbBoxBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

void MbBoxBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::MeatBall_Box)
        CursorMgr::Instance()->setPicked(Meal::None);
}

void MbBoxBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::MeatBall_Box, this);
}

void MbBoxBundle::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("mb_box_bundle");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}