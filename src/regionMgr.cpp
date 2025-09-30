#include "regionMgr.h"
#include "cursorMgr.h"


void regionMgr:: add(const std::string &name, Region *region)
{
    regionPool[name] = region;
}

Region *regionMgr::find(const std::string &name)
{
    return regionPool[name];
}

void regionMgr::markForRemoval(const std::string& name)
{
    toRemoveQueue.push(name);
}

void regionMgr::markForRemoval(Region* region)
{
    for (const auto& pair : regionPool) {
        if (pair.second == region) {
            toRemoveQueue.push(pair.first);
            break; // 找到后退出循环
        }
    }
}

void regionMgr::remove(const std::string &name)
{
    auto it = regionPool.find(name);
    if (it != regionPool.end()) {
        delete it->second; // 释放内存
        regionPool.erase(it); // 从map中移除
    }
}

void regionMgr::onUpdate(float delta)
{
    for (auto &pair : regionPool)
        pair.second->onUpdate(delta);
    CursorMgr::Instance()->onUpdate(delta);

    while(!toRemoveQueue.empty()) {
        remove(toRemoveQueue.front());
        toRemoveQueue.pop();
    }
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
    case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                for (auto &pair : regionPool)
                {
                    SDL_Point pos = {event.motion.x, event.motion.y};
                    if (SDL_PointInRect(&pos, &pair.second->getRect()))
                        pair.second->onCursorRightDown();
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