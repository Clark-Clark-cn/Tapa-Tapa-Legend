#include "microwaveOven.h"

#include "resMgr.h"
#include "cursorMgr.h"

MicrowaveOven::MicrowaveOven(int x, int y) : Region({x, y, 284, 176})
{
    timer.setOneShot(true);
    timer.setWaitTime(9.0f);
    timer.setOnTimeout([&](){
        isWorking=false;
        Mix_PlayChannel(-1,ResMgr::Instance()->findAudio("complete"),0);
    });
}

bool MicrowaveOven::onCursorUp()
{
    if (isWorking)
        return false;

    if (mealTarget == Meal::None && canPlace(CursorMgr::Instance()->getPicked()))
    {
        switch (CursorMgr::Instance()->getPicked())
        {

        case Meal::BraisedChicken_Cold:
            mealTarget = Meal::BraisedChicken_Hot;
            break;
        case Meal::MeatBall_Cold:
            mealTarget = Meal::MeatBall_Hot;
            break;
        case Meal::RedCookedPork_Cold:
            mealTarget = Meal::RedCookedPork_Hot;
            break;
        }

        timer.restart();
        isWorking = true;
        CursorMgr::Instance()->setPicked(Meal::None);
        Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("mo_working"), 0);
        return true;
    }
    return false;
}

void MicrowaveOven::onCursorDown()
{
    if (isWorking)
        return;

    if (CursorMgr::Instance()->getPicked() == Meal::None)
    {
        CursorMgr::Instance()->setPicked(mealTarget, this);
        mealTarget = Meal::None;
    }
}

void MicrowaveOven::onUpdate(float delta)
{
    if (isWorking)
        timer.onUpdate(delta);
}

void MicrowaveOven::onRender(SDL_Renderer *renderer)
{
    SDL_Texture *textureMo = ResMgr::Instance()->findTexture(isWorking ? "mo_working" : "mo_opening");

    SDL_RenderCopy(renderer, textureMo, nullptr, &rect);

    if (!isWorking)
    {
        switch (mealTarget)
        {
        case Meal::None:
            texture = nullptr;
            break;
        case Meal::BraisedChicken_Hot:
            texture = ResMgr::Instance()->findTexture("bc_hot_picked");
            break;
        case Meal::MeatBall_Hot:
            texture = ResMgr::Instance()->findTexture("mb_hot_picked");
            break;
        case Meal::RedCookedPork_Hot:
            texture = ResMgr::Instance()->findTexture("rcp_hot_picked");
            break;
        }
        if (texture)
        {
            texturnReturn = texture;
            SDL_Rect rectPicked = {rect.x + 113, rect.y + 65, 0, 0};
            SDL_QueryTexture(texture, nullptr, nullptr, &rectPicked.w, &rectPicked.h);
            SDL_RenderCopy(renderer, texture, nullptr, &rectPicked);
        }
    }
    SDL_RenderDrawRect(renderer, &rect);
}

void MicrowaveOven::onReturn(Meal meal)
{
    mealTarget=meal;
}

bool MicrowaveOven::canPlace(Meal target)
{
    return target == Meal::BraisedChicken_Cold 
    || target == Meal::MeatBall_Cold
    || target == Meal::RedCookedPork_Cold;
}