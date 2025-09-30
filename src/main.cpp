#define SDL_MAIN_HANDLED

#include "resMgr.h"
#include "cursorMgr.h"
#include "screenMgr.h"
#include "screens/game/gameScreen.h"
#include "screens/main/mainScreen.h"

#include <SDL_image.h>

#include <chrono>
#include <thread>
#include <iostream>

bool isDebug = false;
static SDL_Window *window = nullptr;

SDL_Renderer* init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    TTF_Init();

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    srand(time(nullptr));

    bool showTips=Config::Instance()->get("showTips");
    if(showTips){
        const SDL_MessageBoxButtonData buttons[]={
            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,0,"OK"},
            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,0,"Alright"}
        };
        SDL_MessageBoxData mb{
            SDL_MESSAGEBOX_INFORMATION, window,"tips",
R"(here is the tips for Tapa Tapa Legend
First, you can drag food or boxes through your mouse
Second, you can double right click on the microwave oven to upgrade it 
Third, you can click the clock on the delivery driver to make him/her wait you more time
but you need to pay him/her some money
Fourth, you need to pick up coins by yourself, you can drag your mouse through it would be picked up
Fifth, delivery driver would go if you cannot finish your meal in time,
and your dishes or drinks would gone, too.
Press OK and this tip would NOT show again.
)",SDL_arraysize(buttons),
        buttons,
        nullptr};
        int buttonID=-1;
        SDL_ShowMessageBox(&mb,&buttonID);
        std::cout<<SDL_GetError()<<std::endl;
        if(buttonID==0){
            Config::Instance()->set("showTips",false);
            Config::Instance()->save();
        }
    }
    const int windowWidth = Config::Instance()->get("window.width").asInt();
    const int windowHeight = Config::Instance()->get("window.height").asInt();
    window = SDL_CreateWindow("Tapa Tapa Legend",
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

    Mix_PlayChannel(-1, ResMgr::Instance()->findAudio("bgm"), -1);

    ScreenMgr::Instance()->addScreen(ScreenID::Game, new GameScreen());
    ScreenMgr::Instance()->addScreen(ScreenID::MainMenu, new MainScreen());
    ScreenMgr::Instance()->changeScreen(ScreenID::MainMenu);
    
    return renderer;
}

int main(int argc, char **argv)
{
    using namespace std::chrono;
    SDL_Renderer *renderer = init();

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
            case SDL_QUIT:isQuit = true;break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_F1) isDebug = !isDebug;break;
            }
            CursorMgr::Instance()->onInput(event);
            ScreenMgr::Instance()->onInput(event);
        }

        steady_clock::time_point frameStart = steady_clock::now();
        duration<float> delta = duration<float>(frameStart - lastTick);

        ScreenMgr::Instance()->onUpdate(delta.count());

        SDL_RenderClear(renderer);
        ScreenMgr::Instance()->onRender(renderer);
        CursorMgr::Instance()->onRender(renderer);
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