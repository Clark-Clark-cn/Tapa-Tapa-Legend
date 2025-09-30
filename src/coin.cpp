#include "screens/game/coin.h"
#include "screens/game/statusBar.h"

#include "resMgr.h"
#include "regionMgr.h"
#include "screenMgr.h"

int coinCounter=0;

bool Coin::onCursorUp()
{
    Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("get_coin"), 0);
    static auto regionMgr = ScreenMgr::Instance()->getScreen(ScreenID::Game)->getRegionMgr();
    static StatusBar* bar = static_cast<StatusBar*>(regionMgr->find("status_bar"));
    bar->addMoney(1); // 增加1金钱
    regionMgr->markForRemoval(id); // 从管理器中移除自己
    return true;
}

void Coin::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *coinTexture = ResMgr::Instance()->findTexture("coin");
    SDL_RenderCopy(renderer, coinTexture, nullptr, &rect);
    if (isDebug)
        SDL_RenderDrawRect(renderer, &rect);
}