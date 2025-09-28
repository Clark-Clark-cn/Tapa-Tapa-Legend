#include "rcpBoxBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool RcpBoxBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::RedCookedPork_Box){
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void RcpBoxBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::RedCookedPork_Box, this);
}

void RcpBoxBundle::onRender(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}
