#pragma once
#include "region.h"
#include "timer.h"
#include "meal.h"

#include <vector>

class DeliveryDriver : public Region
{
public:
    DeliveryDriver(int x, int y);
    ~DeliveryDriver() = default;

    bool onCursorUp() override;
    void onUpdate(float delta) override;
    void onRender(SDL_Renderer *renderer) override;

private:
    // 餐品状态
    enum class Status
    {
        Waiting,   // 等待中
        Completed, // 已完成
    };

private:
    Timer timerRefresh;               // 外卖员刷新定时器
    float timeWaited = 0.0f;         // 已经等待时间
    bool isWaiting = false;           // 当前是否正在等待
    bool isMeituan = false;           // 是否为美团外卖员
    std::vector<Meal> mealList;       // 餐品列表
    std::vector<Status> statusList;   // 餐品状态列表
    int numDrink = 0 , numDish = 0;    // 饮料和菜品数量
    const float timeWaitedLimit = Config::Instance()->get("deliveryDriver.waitTime"); // 等待超时上限

private:
    void refresh();
    bool checkAndPlace(Meal target);
};
