#include "mbBoxBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool MbBoxBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::MeatBall_Box){
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void MbBoxBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::MeatBall_Box, this);
}

void MbBoxBundle::onRender(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}