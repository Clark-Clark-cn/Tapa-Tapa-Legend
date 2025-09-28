#include "colaBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool ColaBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::Cola){
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void ColaBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::Cola, this);
}

void ColaBundle::onRender(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}