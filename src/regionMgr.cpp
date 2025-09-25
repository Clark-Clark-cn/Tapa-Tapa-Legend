#include "regionMgr.h"

regionMgr *regionMgr::manager = nullptr;

regionMgr *regionMgr::Instance()
{
    if (!manager)
        manager = new regionMgr();

    return manager;
}

void regionMgr:: add(const std::string &name, Region *region)
{
    regionPool[name] = region;
}

Region *regionMgr::find(const std::string &name)
{
    return regionPool[name];
}

void regionMgr::onUpdate(float delta)
{
    for (auto &pair : regionPool)
        pair.second->onUpdate(delta);
}
void regionMgr::onInput(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:

        if (event.button.button == SDL_BUTTON_LEFT)
        {

            for (auto &pair : regionPool)
            {
                SDL_Point pos = {event.motion.x, event.motion.y};
                if (SDL_PointInRect(&pos, &pair.second->getRect()))
                    pair.second->onCursorDown();
            }
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
        {

            for (auto &pair : regionPool)
            {
                SDL_Point pos = {event.motion.x, event.motion.y};
                if (SDL_PointInRect(&pos, &pair.second->getRect()))
                    pair.second->onCursorUp();
            }
        }
        break;
    }
}

void regionMgr::onRender(SDL_Renderer *renderer)
{
    for (auto &pair : regionPool)
        pair.second->onRender(renderer);
}

regionMgr::regionMgr() = default;

regionMgr::~regionMgr() = default;