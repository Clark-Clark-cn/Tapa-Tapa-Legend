#pragma once
#include "region.h"

#include <SDL.h>

#include <string>
#include <unordered_map>
#include <queue>

class regionMgr
{
public:
    static regionMgr *Instance();

    void add(const std::string &name, Region *region);
    Region *find(const std::string &name);
    void markForRemoval(const std::string& name); // 标记删除

    void onUpdate(float delta);
    void onInput(const SDL_Event &event);
    void onRender(SDL_Renderer *renderer);

private:
    regionMgr();
    ~regionMgr();
    void remove(const std::string &name);

private:
    static regionMgr *manager;
    std::unordered_map<std::string, Region *> regionPool;
    std::queue<std::string> toRemoveQueue; // 待删除队列
};