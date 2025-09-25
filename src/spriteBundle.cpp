#include "spriteBundle.h"

#include "resMgr.h"
#include "cursorMgr.h"

void SpriteBundle::onCursorUp()
{
    if (CursorMgr::Instance()->getPicked() == Meal::Sprite)
        CursorMgr::Instance()->setPicked(Meal::None);
}

void SpriteBundle::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
        CursorMgr::Instance()->setPicked(Meal::Sprite);
}

void SpriteBundle::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *texture = ResMgr::Instance()->findTexture("sprite_bundle");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderDrawRect(renderer, &rect);
}
