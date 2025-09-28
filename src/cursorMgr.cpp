#include "resMgr.h"
#include "cursorMgr.h"

CursorMgr *CursorMgr::manager = nullptr;

CursorMgr *CursorMgr::Instance()
{
    if (!manager)
        manager = new CursorMgr();

    return manager;
}

void CursorMgr::onInput(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
    {
        posCursor.x = event.motion.x;
        posCursor.y = event.motion.y;
    }
    break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            isMouseLbtnDown = true;
            switch (rand() % 3)
            {
            case 0:
                Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("click_1"), 0);
                break;
            case 1:
                Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("click_2"), 0);
                break;
            case 2:
                Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("click_3"), 0);
                break;
            }
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
            isMouseLbtnDown = false;
        break;
    }
}

void CursorMgr::onRender(SDL_Renderer *renderer)
{
    // 根据当前抓取的餐品不同选择不同的餐品纹理进行绘制
    SDL_Texture *texturePicked = nullptr;
    switch (mealPicked)
    {
    case Meal::None:
        break;
    case Meal::Cola:
        texturePicked = ResMgr::Instance()->findTexture("cola");
        break;
    case Meal::Sprite:
        texturePicked = ResMgr::Instance()->findTexture("sprite");
        break;
    case Meal::BraisedChicken_Hot:
        texturePicked = ResMgr::Instance()->findTexture("bc_hot_picked");
        break;
    case Meal::BraisedChicken_Cold:
        texturePicked = ResMgr::Instance()->findTexture("bc_cold_picked");
        break;
    case Meal::MeatBall_Hot:
        texturePicked = ResMgr::Instance()->findTexture("mb_hot_picked");
        break;
    case Meal::MeatBall_Cold:
        texturePicked = ResMgr::Instance()->findTexture("mb_cold_picked");
        break;
    case Meal::RedCookedPork_Hot:
        texturePicked = ResMgr::Instance()->findTexture("rcp_hot_picked");
        break;
    case Meal::RedCookedPork_Cold:
        texturePicked = ResMgr::Instance()->findTexture("rcp_cold_picked");
        break;
    case Meal::BraisedChicken_Box:
        texturePicked = ResMgr::Instance()->findTexture("bc_box");
        break;
    case Meal::MeatBall_Box:
        texturePicked = ResMgr::Instance()->findTexture("mb_box");
        break;
    case Meal::RedCookedPork_Box:
        texturePicked = ResMgr::Instance()->findTexture("rcp_box");
        break;
    case Meal::TakeoutBox:
        texturePicked = ResMgr::Instance()->findTexture("tb_picked");
        break;
    }
    if (texturePicked)
    {
        SDL_Rect rectPicked = {posCursor.x, posCursor.y, 0, 0};
        SDL_QueryTexture(texturePicked, nullptr, nullptr, &rectPicked.w, &rectPicked.h);
        SDL_RenderCopy(renderer, texturePicked, nullptr, &rectPicked);
    }

    // 根据当前鼠标左键状态选择不同的光标纹理进行绘制
    SDL_Rect rectCursor = {posCursor.x, posCursor.y, 64, 64};
    SDL_Texture *textureCursor = ResMgr::Instance()->findTexture(isMouseLbtnDown ? "cursor_down" : "cursor_idle");
    SDL_RenderCopy(renderer, textureCursor, nullptr, &rectCursor);

    // 如果正在归位动画中，绘制归位动画
    if(isReturning&&textureReturn){
        SDL_Rect rectReturn;
        SDL_QueryTexture(textureReturn, nullptr, nullptr, &rectReturn.w, &rectReturn.h);
        rectReturn.x=static_cast<int>(returnStartPos.x+(returnEndPos.x-returnStartPos.x)*returnProgress)-rectReturn.w/2;
        rectReturn.y=static_cast<int>(returnStartPos.y+(returnEndPos.y-returnStartPos.y)*returnProgress)-rectReturn.h/2;
        SDL_RenderCopy(renderer, textureReturn, nullptr, &rectReturn);
    }
}

void CursorMgr::onUpdate(float delta){
    if(isReturning){
        returnProgress+=delta/returnSpeed;
        if(returnProgress>=1.0f){
            if(source)
                source->onReturn(mealReturning);
            isReturning=false;
            returnProgress=0.0f;
        }
    }
}

void CursorMgr::setPicked(Meal meal, Region* src)
{
    mealPicked = meal;
    if(meal==Meal::None)
        source=nullptr;
    else
        source = src;
}

Meal CursorMgr::getPicked()
{
    return mealPicked;
}

Region* CursorMgr::getSource()
{
    return source;
}

void CursorMgr::startReturn(){
    if(mealPicked!=Meal::None&&source){
        mealReturning=mealPicked;
        isReturning=true;
        returnStartPos=posCursor;
        SDL_Rect srcRect=source->getRect();
        returnEndPos={srcRect.x+srcRect.w/2,srcRect.y+srcRect.h/2};
        returnProgress=0.0f;
        textureReturn=source->getTextureForReturn();
        mealPicked=Meal::None;
    }
}

CursorMgr::CursorMgr() = default;

CursorMgr::~CursorMgr() = default;