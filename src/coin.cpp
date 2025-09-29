#include "coin.h"

#include "resMgr.h"
#include "regionMgr.h"
#include "statusBar.h"

int coinCounter=0;

bool Coin::onCursorUp()
{
    Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("get_coin"), 0);
    static StatusBar* bar = static_cast<StatusBar*>(regionMgr::Instance()->find("status_bar"));
    bar->addMoney(1); // 增加1金钱
    regionMgr::Instance()->markForRemoval(id); // 从管理器中移除自己
    return true;
}

void Coin::onRender(SDL_Renderer *renderer)
{
    static SDL_Texture *coinTexture = ResMgr::Instance()->findTexture("coin");
    SDL_RenderCopy(renderer, coinTexture, nullptr, &rect);
}