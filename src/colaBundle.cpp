#include "colaBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

void ColaBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::Cola)
        CursorMgr::Instance()->setPicked(Meal::None);
}

void ColaBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::Cola);
}

void ColaBundle::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("cola_bundle");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}