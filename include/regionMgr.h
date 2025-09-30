#pragma once
#include "region.h"

#include <SDL.h>

#include <string>
#include <unordered_map>
#include <queue>

class regionMgr
{
public:

    void add(const std::string &name, Region *region);
    Region *find(const std::string &name);
    void markForRemoval(const std::string& name); // 标记删除
    void markForRemoval(Region* region); // 标记删除

    void onUpdate(float delta);
    void onInput(const SDL_Event &event);
    void onRender(SDL_Renderer *renderer);

    regionMgr();
    ~regionMgr();
private:
    void remove(const std::string &name);

private:
    std::unordered_map<std::string, Region *> regionPool;
    std::queue<std::string> toRemoveQueue; // 待删除队列
};