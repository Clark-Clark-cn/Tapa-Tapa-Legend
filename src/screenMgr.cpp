#include "screenMgr.h"

ScreenMgr *ScreenMgr::manager = nullptr;

ScreenMgr::~ScreenMgr()
{
    for (auto &pair : screenPool)
        delete pair.second;
    screenPool.clear();
}

ScreenMgr *ScreenMgr::Instance()
{
    if (manager == nullptr)
        manager = new ScreenMgr();
    return manager;
}

void ScreenMgr::changeScreen(ScreenID newScreen)
{
    if (currentScreenID == newScreen)
        return;
    if (currentScreen)
        currentScreen->onExit();
    currentScreenID = newScreen;
    currentScreen = screenPool[newScreen];
    if (currentScreen)
        currentScreen->onEnter();
}

Screen *ScreenMgr::getCurrentScreen() const
{
    return currentScreen;
}

Screen* ScreenMgr::getScreen(ScreenID id)const
{
    auto it = screenPool.find(id);
    if (it != screenPool.end())
        return it->second;
    return nullptr;
}

void ScreenMgr::onInput(const SDL_Event &event)
{
    if (currentScreen)
        currentScreen->onInput(event);
}

void ScreenMgr::onRender(SDL_Renderer *renderer)
{
    if (currentScreen)
        currentScreen->onRender(renderer);
}

void ScreenMgr::onUpdate(float delta)
{
    if (currentScreen)
        currentScreen->onUpdate(delta);
}