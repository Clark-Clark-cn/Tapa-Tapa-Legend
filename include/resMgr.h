#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>
#include <unordered_map>

class ResMgr
{
    ResMgr() = default;
    ~ResMgr() = default;

    static ResMgr *manager;
    std::unordered_map<std::string, SDL_Texture *> texturePool;
    std::unordered_map<std::string, Mix_Chunk *> soundPool;
public:
    static ResMgr *Instance();

    void load(SDL_Renderer *renderer);
    SDL_Texture *findTexture(const std::string &name);
    Mix_Chunk *findAudio(const std::string &name);
};