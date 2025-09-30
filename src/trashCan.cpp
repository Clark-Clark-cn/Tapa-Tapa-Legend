#include "screens/game/trashCan.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool TrashCan::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() != Meal::None){
        Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("trash"), 0);
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void TrashCan::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("trash_can");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    
    if (isDebug)SDL_RenderDrawRect(renderer, &rect);
}