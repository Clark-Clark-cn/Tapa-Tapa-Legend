#pragma once

#include "screens/screen.h"
#include "regionMgr.h"
#include <unordered_map>

enum class ScreenID{
    None,
    MainMenu,
    Game,
};

class ScreenMgr
{
    std::unordered_map<ScreenID, Screen *> screenPool;
    Screen *currentScreen = nullptr;
    ScreenID currentScreenID = ScreenID::None;
    ScreenMgr() = default;
    ~ScreenMgr();
    static ScreenMgr *manager;
public:
    static ScreenMgr *Instance();

    void changeScreen(ScreenID newScreen);
    Screen *getCurrentScreen() const;
    Screen* getScreen(ScreenID id)const;

    void onInput(const SDL_Event &event);
    void onRender(SDL_Renderer *renderer);
    void onUpdate(float delta);

    void addScreen(ScreenID id, Screen* screen){ screenPool[id] = screen; }
};