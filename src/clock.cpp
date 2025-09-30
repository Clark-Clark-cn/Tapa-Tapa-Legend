#include "screens/game/clock.h"
#include "screens/game/gameScreen.h"
#include "screens/game/statusBar.h"
#include "screens/game/deliveryDriver.h"

#include "screenMgr.h"

void Clock::onRender(SDL_Renderer *renderer)
{
    if (!isVisible)return;
     if (!texture)return;
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    if (isDebug)
        SDL_RenderDrawRect(renderer, &rect);
}

void Clock::onCursorDown()
{
    if(deliveryDriver){
        if(deliveryDriver->getWaitedTime()<5.0f)return;
    }
    static Screen* gameScreen = (ScreenMgr::Instance()->getScreen(ScreenID::Game));
    static StatusBar* statusBar = static_cast<StatusBar*>(gameScreen->getRegionMgr()->find("status_bar"));
    static const int cost = Config::Instance()->get("clock.cost");
    if (statusBar&& statusBar->reduceMoney(cost)&& deliveryDriver)
    {
        Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("use_clock"), 0);
        deliveryDriver->setWaitedTime(0.0f);
    }
}