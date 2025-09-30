#pragma once
#include "region.h"

class DeliveryDriver;

static Point clockSize = Config::Instance()->get("region.clock.size");

class Clock : public Region
{
    SDL_Texture* texture = nullptr;
    DeliveryDriver* deliveryDriver = nullptr;
    bool isVisible = true;
public:
    Clock(int x, int y, DeliveryDriver* driver) :
     Region({x, y, clockSize.x, clockSize.y}), deliveryDriver(driver) {
        texture = ResMgr::Instance()->findTexture("clock");
    }
    ~Clock() = default;

    void onRender(SDL_Renderer *renderer)override;
    void onCursorDown()override;

    void setVisible(bool val) { this->isVisible = val; }
};