#include "screens/main/mainScreen.h"

#include "screens/main/button.h"
#include "screenMgr.h"

MainScreen::MainScreen(){
    static Point pos=Config::Instance()->get("region.start.pos");
    static Point size=Config::Instance()->get("region.start.size");
    Button* start=new Button(pos.x,pos.y,size.x,size.y);

    start->setName("Play!");
    start->setCallback([this](){
        ScreenMgr::Instance()->changeScreen(ScreenID::Game);
    });

    mgr.add("start",start);
}

regionMgr* MainScreen::getRegionMgr(){
    return &mgr;
}

void MainScreen::onInput(const SDL_Event& event){
    mgr.onInput(event);
    if(event.type==SDL_KEYDOWN){
        if(event.key.keysym.sym==SDLK_KP_ENTER){
            ScreenMgr::Instance()->changeScreen(ScreenID::Game);
        }
    }
}

void MainScreen::onRender(SDL_Renderer* renderer){
    SDL_Rect backgroundRect={0,0,1280,720};
    static SDL_Texture* background=ResMgr::Instance()->findTexture("background");
    SDL_RenderCopy(renderer, background, nullptr, &backgroundRect);

    mgr.onRender(renderer);
}
