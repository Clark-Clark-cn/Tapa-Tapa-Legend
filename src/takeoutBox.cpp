#include "screens/game/takeoutBox.h"

#include "resMgr.h"
#include "cursorMgr.h"

bool TakeoutBox::onCursorUp()
{
    // 如果当前位置是空的快餐盒
    if (meal == Meal::TakeoutBox)
    {
        switch (CursorMgr::Instance()->getPicked())
        {
        case Meal::BraisedChicken_Box:
            meal = Meal::BraisedChicken_Cold;
            CursorMgr::Instance()->setPicked(Meal::None);
            return true;
            break;
        case Meal::MeatBall_Box:
            meal = Meal::MeatBall_Cold;
            CursorMgr::Instance()->setPicked(Meal::None);
            return true;
            break;
        case Meal::RedCookedPork_Box:
            meal = Meal::RedCookedPork_Cold;
            CursorMgr::Instance()->setPicked(Meal::None);
            return true;
            break;
        default:
            break;
        }
    }
    // 否则如果当前位置没有物品并且光标抓取了可放置的物品
    else if (meal == Meal::None && canPlace(CursorMgr::Instance()->getPicked()))
    {
        meal = CursorMgr::Instance()->getPicked();
        CursorMgr::Instance()->setPicked(Meal::None);
        return true;
    }
    return false;
}

void TakeoutBox::onCursorDown()
{
    if (CursorMgr::Instance()->getPicked() == Meal::None)
    {
        CursorMgr::Instance()->setPicked(meal, this);
        meal = Meal::None;
    }
}

void TakeoutBox::onRender(SDL_Renderer *renderer)
{
    switch (meal)
    {
    case Meal::None:
        texture = nullptr;
        break;
    case Meal::BraisedChicken_Hot:
        texture = ResMgr::Instance()->findTexture("bc_hot");
        break;
    case Meal::BraisedChicken_Cold:
        texture = ResMgr::Instance()->findTexture("bc_cold");
        break;
    case Meal::MeatBall_Cold:
        texture = ResMgr::Instance()->findTexture("mb_cold");
        break;
    case Meal::MeatBall_Hot:
        texture = ResMgr::Instance()->findTexture("mb_hot");
        break;
    case Meal::RedCookedPork_Cold:
        texture = ResMgr::Instance()->findTexture("rcp_cold");
        break;
    case Meal::RedCookedPork_Hot:
        texture = ResMgr::Instance()->findTexture("rcp_hot");
        break;
    case Meal::TakeoutBox:
        texture = ResMgr::Instance()->findTexture("tb");
        break;
    default:
        texture = nullptr;
        break;
    }

    if (texture)
    {
        textureReturn=texture;
        SDL_Rect rectTexture = {rect.x, rect.y, 0, 0};
        SDL_QueryTexture(texture, nullptr, nullptr, &rectTexture.w, &rectTexture.h);
        SDL_RenderCopy(renderer, texture, nullptr, &rectTexture);
    }

    if (isDebug)SDL_RenderDrawRect(renderer, &rect);
}

void TakeoutBox::onReturn(Meal target)
{
    meal=target;
}

bool TakeoutBox::canPlace(Meal target)
{
    return target == Meal::BraisedChicken_Hot || target == Meal::BraisedChicken_Cold 
    || target == Meal::MeatBall_Hot || target == Meal::MeatBall_Cold 
    || target == Meal::RedCookedPork_Hot || target == Meal::RedCookedPork_Cold 
    || target == Meal::TakeoutBox;
} 