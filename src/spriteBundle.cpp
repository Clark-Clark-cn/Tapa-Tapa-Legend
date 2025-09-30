#include "screens/game/spriteBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool SpriteBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::Sprite){
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void SpriteBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::Sprite, this);
}

void SpriteBundle::onRender(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    if (isDebug)SDL_RenderDrawRect(renderer, &rect);
}