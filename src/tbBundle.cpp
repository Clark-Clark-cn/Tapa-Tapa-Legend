#include "tbBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

void TbBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::TakeoutBox)
        CursorMgr::Instance()->setPicked(Meal::None);
}

void TbBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::TakeoutBox);
}

void TbBundle::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("tb_bundle");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}