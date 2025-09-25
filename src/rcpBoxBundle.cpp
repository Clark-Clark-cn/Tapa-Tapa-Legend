#include "rcpBoxBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

void RcpBoxBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::RedCookedPork_Box)
        CursorMgr::Instance()->setPicked(Meal::None);
}

void RcpBoxBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::RedCookedPork_Box);
}

void RcpBoxBundle::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("rcp_box_bundle");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}
