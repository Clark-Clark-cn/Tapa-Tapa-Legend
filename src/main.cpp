#define SDL_MAIN_HANDLED

#include "resMgr.h"
#include "cursorMgr.h"
#include "regionMgr.h"

#include "deliveryDriver.h"
#include "colaBundle.h"
#include "spriteBundle.h"
#include "tbBundle.h"
#include "mbBoxBundle.h"
#include "bcBoxBundle.h"
#include "rcpBoxBundle.h"
#include "microwaveOven.h"
#include "takeoutBox.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

// 初始化游戏界面可交互区域
void initRegions()
{
    regionMgr::Instance()->add("delivery_driver_1", new DeliveryDriver(385, 142));
    regionMgr::Instance()->add("delivery_driver_2", new DeliveryDriver(690, 142));
    regionMgr::Instance()->add("delivery_driver_3", new DeliveryDriver(995, 142));

    regionMgr::Instance()->add("cola_bundle", new ColaBundle(300, 390));
    regionMgr::Instance()->add("sprite_bundle", new SpriteBundle(425, 390));
    regionMgr::Instance()->add("tb_bundle", new TbBundle(550, 418));

    regionMgr::Instance()->add("mb_box_bundle", new MbBoxBundle(225, 520));
    regionMgr::Instance()->add("bc_box_bundle", new BcBoxBundle(395, 520));
    regionMgr::Instance()->add("rcp_box_bundle", new RcpBoxBundle(565, 520));

    regionMgr::Instance()->add("microwave_oven_1", new MicrowaveOven(740, 400));
    regionMgr::Instance()->add("microwave_oven_2", new MicrowaveOven(975, 400));

    regionMgr::Instance()->add("takeout_box_1", new TakeoutBox(830, 580));
    regionMgr::Instance()->add("takeout_box_2", new TakeoutBox(935, 580));
    regionMgr::Instance()->add("takeout_box_3", new TakeoutBox(1040, 580));
    regionMgr::Instance()->add("takeout_box_4", new TakeoutBox(1145, 580));
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

    SDL_Window *window = SDL_CreateWindow("《拼好饭传奇》",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        1280, 720, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_ShowCursor(SDL_DISABLE);

    ResMgr::Instance()->load(renderer);

    initRegions();

    Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("bgm"), -1);

    SDL_Event event;
    bool isQuit = false;

    const nanoseconds frameDuration(1000000000 / 144);
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