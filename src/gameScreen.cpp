#include "screens/game/gameScreen.h"

#include "screens/game/statusBar.h"
#include "screens/game/deliveryDriver.h"
#include "screens/game/colaBundle.h"
#include "screens/game/spriteBundle.h"
#include "screens/game/tbBundle.h"
#include "screens/game/mbBoxBundle.h"
#include "screens/game/bcBoxBundle.h"
#include "screens/game/rcpBoxBundle.h"
#include "screens/game/microwaveOven.h"
#include "screens/game/takeoutBox.h"
#include "screens/game/trashCan.h"

#include "cursorMgr.h"
#include "screenMgr.h"

GameScreen::GameScreen() {
    timer.setOneShot(true);
    static const float time=Config::Instance()->get("time.game");
    timer.setWaitTime(time);
    timer.setOnTimeout([&]() {
        gameOver = true;
        paused=true;
    });
    timerChangeScreen.setOneShot(true);
    static const float time2=Config::Instance()->get("time.GoMenu");
    timerChangeScreen.setWaitTime(time2);
    timerChangeScreen.setOnTimeout([&](){
        ScreenMgr::Instance()->changeScreen(ScreenID::MainMenu);
    });
}

void GameScreen::onUpdate(float delta_) {
    float delta = paused ? 0.0f : delta_;
    mgr.onUpdate(delta);
    timer.onUpdate(delta);
    if(gameOver && gameOverProgress <= 1.0f){
        gameOverProgress += delta_/2.0f;
        if(gameOverProgress >= 1.0f){
            gameOverProgress = 1.0f;
            timerChangeScreen.onUpdate(delta_);
        }
    }
}

void GameScreen::onInput(const SDL_Event &event) {
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)paused = !paused;break;
    case SDL_MOUSEBUTTONDOWN:
        paused = false; break;
    }
    mgr.onInput(event);
}

void GameScreen::onRender(SDL_Renderer *renderer) {
    // 绘制背景图
    SDL_Rect rectBackground = {0, 0, 1280, 720};
    SDL_RenderCopy(renderer, ResMgr::Instance()->findTexture("background"), nullptr, &rectBackground);

    mgr.onRender(renderer);
    CursorMgr::Instance()->onRender(renderer);

    if(gameOver){
        std::string gameOverText = "Game Over";
        SDL_Color textColor = {255, 255, 255, 255}; // 白色
        SDL_Surface *textSurface = TTF_RenderText_Blended(ResMgr::Instance()->findFont("text"), gameOverText.c_str(), textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        int width, height;
        width = textSurface->w*2;
        height = textSurface->h*2;
        SDL_Rect textRect = {1280/2 - width/2, int(gameOverProgress*720/2-height/2), width, height};
        SDL_SetRenderDrawColor(renderer,0,0,0,30);
        SDL_RenderFillRect(renderer,&textRect);
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        static StatusBar *statusBar=static_cast<StatusBar*>(mgr.find("status_bar"));
        int lastMoney=statusBar->getMoney();
        std::string gameOverText2="Earned "+std::to_string(lastMoney-moneyBegin)+" shells";
        textSurface=TTF_RenderText_Blended(ResMgr::Instance()->findFont("text"),gameOverText2.c_str(),textColor);
        textTexture=SDL_CreateTextureFromSurface(renderer,textSurface);
        textRect={textRect.x,textRect.y+textRect.h,textSurface->w,textSurface->h};
        SDL_RenderCopy(renderer,textTexture,nullptr,&textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
    else{
        static SDL_Texture* texturePaused = ResMgr::Instance()->findTexture("pause");
        static SDL_Rect rectPaused = {1280/2 - 200, 720/2 - 200, 400, 400};
        if(paused)SDL_RenderCopy(renderer, texturePaused, nullptr, &rectPaused);
        float leftTime = timer.getLeftTime();
        // 绘制倒计时
        SDL_Color textColor = {255, 255, 255, 255}; // 白色
        std::string leftTimeText = std::to_string(static_cast<int>(leftTime))+" s";
        SDL_Surface *textSurface = TTF_RenderText_Blended(ResMgr::Instance()->findFont("text"), leftTimeText.c_str(), textColor);
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {60, 50, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        // 清理资源
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void GameScreen::onEnter() {
    static bool firstEnter = true;
    if (firstEnter) {
        static const Point dd1Pos = Config::Instance()->get("region.deliveryDriver1.pos");
        static const Point dd2Pos = Config::Instance()->get("region.deliveryDriver2.pos");
        static const Point dd3Pos = Config::Instance()->get("region.deliveryDriver3.pos");
        mgr.add("delivery_driver_1", new DeliveryDriver(dd1Pos.x, dd1Pos.y));
        mgr.add("delivery_driver_2", new DeliveryDriver(dd2Pos.x, dd2Pos.y));
        mgr.add("delivery_driver_3", new DeliveryDriver(dd3Pos.x, dd3Pos.y));

        static const Point cbPos = Config::Instance()->get("region.colaBundle.pos");
        mgr.add("cola_bundle", new ColaBundle(cbPos.x, cbPos.y));

        static const Point sbPos = Config::Instance()->get("region.spriteBundle.pos");
        mgr.add("sprite_bundle", new SpriteBundle(sbPos.x, sbPos.y));

        static const Point tbPos = Config::Instance()->get("region.tbBundle.pos");
        mgr.add("tb_bundle", new TbBundle(tbPos.x, tbPos.y));

        static const Point mbPos = Config::Instance()->get("region.mbBoxBundle.pos");
        mgr.add("mb_box_bundle", new MbBoxBundle(mbPos.x, mbPos.y));

        static const Point bcPos = Config::Instance()->get("region.bcBoxBundle.pos");
        mgr.add("bc_box_bundle", new BcBoxBundle(bcPos.x, bcPos.y));

        static const Point rcpPos = Config::Instance()->get("region.rcpBoxBundle.pos");
        mgr.add("rcp_box_bundle", new RcpBoxBundle(rcpPos.x, rcpPos.y));

        static const Point mo1Pos = Config::Instance()->get("region.microwaveOven1.pos");
        static const Point mo2Pos = Config::Instance()->get("region.microwaveOven2.pos");
        mgr.add("microwave_oven_1", new MicrowaveOven(mo1Pos.x, mo1Pos.y));
        mgr.add("microwave_oven_2", new MicrowaveOven(mo2Pos.x, mo2Pos.y));

        static const Point tb1Pos = Config::Instance()->get("region.takeoutBox1.pos");
        static const Point tb2Pos = Config::Instance()->get("region.takeoutBox2.pos");
        static const Point tb3Pos = Config::Instance()->get("region.takeoutBox3.pos");
        static const Point tb4Pos = Config::Instance()->get("region.takeoutBox4.pos");
        mgr.add("takeout_box_1", new TakeoutBox(tb1Pos.x, tb1Pos.y));
        mgr.add("takeout_box_2", new TakeoutBox(tb2Pos.x, tb2Pos.y));
        mgr.add("takeout_box_3", new TakeoutBox(tb3Pos.x, tb3Pos.y));
        mgr.add("takeout_box_4", new TakeoutBox(tb4Pos.x, tb4Pos.y));

        static const Point tcPos = Config::Instance()->get("region.trashCan.pos");
        mgr.add("trash_can", new TrashCan(tcPos.x, tcPos.y));

        mgr.add("status_bar", new StatusBar(0,0));
    }
    timer.restart();
    timerChangeScreen.restart();
    static StatusBar* statusBar = static_cast<StatusBar*>(mgr.find("status_bar"));
    moneyBegin=statusBar->getMoney();
    paused = false;
}

void GameScreen::onExit() {
    paused = false;
}