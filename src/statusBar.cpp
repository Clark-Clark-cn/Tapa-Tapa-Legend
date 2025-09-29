#include "statusBar.h"

#include "resMgr.h"
#include <SDL_ttf.h>

void StatusBar::onRender(SDL_Renderer *renderer)
{
    // 绘制金钱图标
    static SDL_Texture *coinTexture = ResMgr::Instance()->findTexture("coin");
    SDL_Rect moneyIconRect = {20, 10, 30, 30};
    SDL_RenderCopy(renderer, coinTexture, nullptr, &moneyIconRect);

    // 绘制金钱数值
    SDL_Color textColor = {255, 255, 255, 255}; // 白色
    std::string moneyText = std::to_string(money);
    SDL_Surface *textSurface = TTF_RenderText_Blended(ResMgr::Instance()->findFont("text"), moneyText.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {60, 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    // 清理资源
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

