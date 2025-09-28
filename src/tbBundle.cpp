#include "tbBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool TbBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::TakeoutBox){
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void TbBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::TakeoutBox, this);
}

void TbBundle::onRender(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}