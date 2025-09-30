#include "screens/game/bcBoxBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool BcBoxBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::BraisedChicken_Box){
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void BcBoxBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::BraisedChicken_Box, this);
}

void BcBoxBundle::onRender(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    if (isDebug)
        SDL_RenderDrawRect(renderer, &rect);
}
