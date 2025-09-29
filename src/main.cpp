#define SDL_MAIN_HANDLED

#include "resMgr.h"
#include "cursorMgr.h"
#include "regionMgr.h"
#include "statusBar.h"

#include "deliveryDriver.h"
#include "colaBundle.h"
#include "spriteBundle.h"
#include "tbBundle.h"
#include "mbBoxBundle.h"
#include "bcBoxBundle.h"
#include "rcpBoxBundle.h"
#include "microwaveOven.h"
#include "takeoutBox.h"
#include "trashCan.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

// 初始化游戏界面可交互区域
void initRegions()
{
    static const Point dd1Pos = Config::Instance()->get("region.deliveryDriver1.pos");
    static const Point dd2Pos = Config::Instance()->get("region.deliveryDriver2.pos");
    static const Point dd3Pos = Config::Instance()->get("region.deliveryDriver3.pos");
    regionMgr::Instance()->add("delivery_driver_1", new DeliveryDriver(dd1Pos.x, dd1Pos.y));
    regionMgr::Instance()->add("delivery_driver_2", new DeliveryDriver(dd2Pos.x, dd2Pos.y));
    regionMgr::Instance()->add("delivery_driver_3", new DeliveryDriver(dd3Pos.x, dd3Pos.y));

    static const Point cbPos = Config::Instance()->get("region.colaBundle.pos");
    regionMgr::Instance()->add("cola_bundle", new ColaBundle(cbPos.x, cbPos.y));

    static const Point sbPos = Config::Instance()->get("region.spriteBundle.pos");
    regionMgr::Instance()->add("sprite_bundle", new SpriteBundle(sbPos.x, sbPos.y));

    static const Point tbPos = Config::Instance()->get("region.tbBundle.pos");
    regionMgr::Instance()->add("tb_bundle", new TbBundle(tbPos.x, tbPos.y));

    static const Point mbPos = Config::Instance()->get("region.mbBoxBundle.pos");
    regionMgr::Instance()->add("mb_box_bundle", new MbBoxBundle(mbPos.x, mbPos.y));

    static const Point bcPos = Config::Instance()->get("region.bcBoxBundle.pos");
    regionMgr::Instance()->add("bc_box_bundle", new BcBoxBundle(bcPos.x, bcPos.y));

    static const Point rcpPos = Config::Instance()->get("region.rcpBoxBundle.pos");
    regionMgr::Instance()->add("rcp_box_bundle", new RcpBoxBundle(rcpPos.x, rcpPos.y));

    static const Point mo1Pos = Config::Instance()->get("region.microwaveOven1.pos");
    static const Point mo2Pos = Config::Instance()->get("region.microwaveOven2.pos");
    regionMgr::Instance()->add("microwave_oven_1", new MicrowaveOven(mo1Pos.x, mo1Pos.y));
    regionMgr::Instance()->add("microwave_oven_2", new MicrowaveOven(mo2Pos.x, mo2Pos.y));

    static const Point tb1Pos = Config::Instance()->get("region.takeoutBox1.pos");
    static const Point tb2Pos = Config::Instance()->get("region.takeoutBox2.pos");
    static const Point tb3Pos = Config::Instance()->get("region.takeoutBox3.pos");
    static const Point tb4Pos = Config::Instance()->get("region.takeoutBox4.pos");
    regionMgr::Instance()->add("takeout_box_1", new TakeoutBox(tb1Pos.x, tb1Pos.y));
    regionMgr::Instance()->add("takeout_box_2", new TakeoutBox(tb2Pos.x, tb2Pos.y));
    regionMgr::Instance()->add("takeout_box_3", new TakeoutBox(tb3Pos.x, tb3Pos.y));
    regionMgr::Instance()->add("takeout_box_4", new TakeoutBox(tb4Pos.x, tb4Pos.y));

    static const Point tcPos = Config::Instance()->get("region.trashCan.pos");
    regionMgr::Instance()->add("trash_can", new TrashCan(tcPos.x, tcPos.y));

    regionMgr::Instance()->add("status_bar", new StatusBar(0,0));
}

void onUpdate(float delta)
{
    regionMgr::Instance()->onUpdate(delta);
}
void onRender(SDL_Renderer *renderer)
{
    // 绘制背景图
    SDL_Rect tectBackground = {0, 0, 1280, 720};
    SDL_RenderCopy(renderer, ResMgr::Instance()->findTexture("background"), nullptr, &tectBackground);

    regionMgr::Instance()->onRender(renderer);
    CursorMgr::Instance()->onRender(renderer);
}

int main(int argc, char **argv)
{
    using namespace std::chrono;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    const int windowWidth = Config::Instance()->get("window.width").asInt();
    const int windowHeight = Config::Instance()->get("window.height").asInt();
    SDL_Window *window = SDL_CreateWindow("《拼好饭传奇》",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, 1280, 720);

    const bool isFullscreen = Config::Instance()->get("window.fullscreen").asBool();
    if (isFullscreen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    const bool Vsync = Config::Instance()->get("window.vsync").asBool();
    if (Vsync)
        SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    else
        SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    SDL_ShowCursor(SDL_DISABLE);
    ResMgr::Instance()->load(renderer);

    const int volume = Config::Instance()->get("audio.volume").asInt();
    Mix_Volume(-1, volume);
    initRegions();

    Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("bgm"), -1);

    SDL_Event event;
    bool isQuit = false;
    const int FPS = Config::Instance()->get("window.fps").asInt();
    const nanoseconds frameDuration(1000000000 / FPS);
    steady_clock::time_point lastTick = steady_clock::now();

    while (!isQuit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isQuit = true;
                break;
            }
            CursorMgr::Instance()->onInput(event);
            regionMgr::Instance()->onInput(event);
        }

        steady_clock::time_point frameStart = steady_clock::now();
        duration<float> delta = duration<float>(frameStart - lastTick);

        onUpdate(delta.count());

        SDL_RenderClear(renderer);
        onRender(renderer);
        SDL_RenderPresent(renderer);

        lastTick = frameStart;
        nanoseconds sleepDuration = frameDuration - (steady_clock::now() - frameStart);
        if (sleepDuration > nanoseconds(0))
            std::this_thread::sleep_for(sleepDuration);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}