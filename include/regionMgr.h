#pragma once
#include "region.h"

#include <SDL.h>

#include <string>
#include <unordered_map>

class regionMgr
{
public:
    static regionMgr *Instance();

    void add(const std::string &name, Region *region);
    Region *find(const std::string &name);

    void onUpdate(float delta);
    void onInput(const SDL_Event &event);
    void onRender(SDL_Renderer *renderer);

private:
    regionMgr();
    ~regionMgr();

private:
    static regionMgr *manager;
    std::unordered_map<std::string, Region *> regionPool;
};