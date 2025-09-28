#include "deliveryDriver.h"

#include "resMgr.h"
#include "cursorMgr.h"

#include <algorithm>

DeliveryDriver::DeliveryDriver(int x, int y) : Region({x, y, 192, 272})
{
    timerRefresh.setOneShot(true);
    timerRefresh.setOnTimeout([&](){ isWaiting = true; });
    refresh();
}

bool DeliveryDriver::onCursorUp()
{
    if (!isWaiting)return false;

    Meal mealHeld = CursorMgr::Instance()->getPicked();
    if (mealHeld == Meal::None || checkAndPlace(mealHeld))
    {
        CursorMgr::Instance()->setPicked(Meal::None);
        Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("complete"), 0);
        return true;
    }
    return false;
}

void DeliveryDriver::onUpdate(float delta)
{
    // 如果还没有在等待，就更新刷新定时器
    if (!isWaiting)
    {
        timerRefresh.onUpdate(delta);
        return;
    }

    // 累加等待时间检查是否超时
    timeWaited += delta;
    if (timeWaited >= timeWaitedLimit)
    {
        refresh();
        return;
    }

    // 检查餐品是否完整
    if (std::count(statusList.begin(), statusList.end(), Status::Waiting) == 0)
        refresh();
}

void DeliveryDriver::onRender(SDL_Renderer *renderer)
{
    if (!isWaiting)return;

    // 绘制外卖员
    SDL_Texture *texture = ResMgr::Instance()->findTexture(isMeituan ? "meituan" : "eleme");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    // 绘制耐心条

    SDL_Rect rectBorder = {rect.x - 35, rect.y + 15, 40, 160};
    SDL_RenderCopy(renderer, ResMgr::Instance()->findTexture("patience_border"), nullptr, &rectBorder);
    SDL_Rect rectContentSrc = {0, 0, rectBorder.w, 0};
    SDL_Rect rectContentDst = {rectBorder.x, 0, rectBorder.w, 0};
    rectContentDst.h = (int)(rectBorder.h * (timeWaited / timeWaitedLimit));
    rectContentDst.y = rectBorder.y + rectBorder.h - rectContentDst.h; // 边框与内容物图片底部对齐
    rectContentSrc.h = rectContentDst.h;
    rectContentSrc.y = rectBorder.h - rectContentSrc.h; // 从底部开始裁剪内容物图片
    SDL_RenderCopy(renderer, ResMgr::Instance()->findTexture("patience_content"), &rectContentSrc, &rectContentDst);

    // 绘制餐品清单
    SDL_Rect rectBubble = {rect.x + 175, rect.y + 55, 76, 139};
    SDL_RenderCopy(renderer, ResMgr::Instance()->findTexture("bubble"), nullptr, &rectBubble);
    for (int i = 0; i < numDish; i++) // 绘制菜品
    {
        SDL_Texture *textureMeal = nullptr;
        switch (mealList[i])
        {
        case Meal::BraisedChicken_Hot:
            textureMeal = ResMgr::Instance()->findTexture("bc_icon");
            break;
        case Meal::MeatBall_Hot:
            textureMeal = ResMgr::Instance()->findTexture("mb_icon");
            break;
        case Meal::RedCookedPork_Hot:
            textureMeal = ResMgr::Instance()->findTexture("rcp_icon");
            break;
        }

        SDL_Rect rectMeal = {rectBubble.x + 18, rectBubble.y + 32 * i + 5, 45, 25};
        SDL_SetTextureAlphaMod(textureMeal, (Uint8)((statusList[i] == Status::Waiting ? 1.0f : 0.35f) * 225));
        SDL_RenderCopy(renderer, textureMeal, nullptr, &rectMeal);
    }
    for (int i = numDish; i < mealList.size(); i++) // 绘制饮料
    {
        SDL_Texture *textureDrink = nullptr;
        switch (mealList[i])
        {
        case Meal::Cola:
            textureDrink = ResMgr::Instance()->findTexture("cola_icon");
            break;
        case Meal::Sprite:
            textureDrink = ResMgr::Instance()->findTexture("sprite_icon");
            break;
        }

        SDL_Rect rectDrink = {rectBubble.x + 18, 0, 20, 26};
        bool isLeftSide = ((i - numDish) % 2 == 0);
        if (!isLeftSide)
            rectDrink.x += 32; // 饮料可以并排放置
        rectDrink.y = rectBubble.y + 32 * numDish + 10 + ((i - numDish) / 2) * 28;
        SDL_SetTextureAlphaMod(textureDrink, (Uint8)((statusList[i] == Status::Waiting ? 1.0f : 0.35f) * 225));
        SDL_RenderCopy(renderer, textureDrink, nullptr, &rectDrink);
    }
    SDL_RenderDrawRect(renderer, &rect);
}
void DeliveryDriver::refresh()
{
    // 重置状态
    timeWaited = 0;
    isWaiting = false;
    mealList.clear();
    statusList.clear();
    numDrink = 0, numDish = 0;

    // 随机刷新时间
    timerRefresh.setWaitTime(rand() % 10 + 10.0f);
    timerRefresh.restart();

    // 随机外卖员形象
    isMeituan = (rand() % 2 == 0);

    // 随机餐品内容
    numDrink = (rand() % 8);                       // 随机饮料数量0~7
    int numLine = (int)std::ceil(numDrink / 2.0f); // 计算饮料所占的行数
    numDish = 4 - numLine;                         // 计算剩余的菜品个数
    for (int i = 0; i < numDish; i++)              // 随机菜品
    {
        switch (rand() % 3)
        {
        case 0:
            mealList.push_back(Meal::BraisedChicken_Hot);
            break;
        case 1:
            mealList.push_back(Meal::MeatBall_Hot);
            break;
        case 2:
            mealList.push_back(Meal::RedCookedPork_Hot);
            break;
        }
    }

    for (int i = 0; i < numDrink; i++) // 随机饮料
    {
        switch (rand() % 2)
        {
        case 0:
            mealList.push_back(Meal::Cola);
            break;
        case 1:
            mealList.push_back(Meal::Sprite);
            break;
        }
    }

    // 更新餐品状态
    statusList.assign(mealList.size(), Status::Waiting);
}

bool DeliveryDriver::checkAndPlace(Meal target)
{
    if (!isWaiting)
        return false;

    for (int i = 0; i < mealList.size(); i++)
    {
        if (statusList[i] == Status::Waiting && mealList[i] == target)
        {
            statusList[i] = Status::Completed;
            return true;
        }
    }
    return false;
}