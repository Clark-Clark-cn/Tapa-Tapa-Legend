#include "regionMgr.h"
#include "cursorMgr.h"

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
    CursorMgr::Instance()->onUpdate(delta);
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
            bool handled = false;
            for (auto &pair : regionPool)
            {
                SDL_Point pos = {event.motion.x, event.motion.y};
                if (SDL_PointInRect(&pos, &pair.second->getRect()))
                {
                    if(pair.second->onCursorUp())
                        handled=true;
                }
            }
            if(!handled&&CursorMgr::Instance()->getPicked()!=Meal::None)
                CursorMgr::Instance()->startReturn();
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