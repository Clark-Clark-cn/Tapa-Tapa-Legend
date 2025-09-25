#include "resMgr.h"

#include <SDL_image.h>
#include <filesystem>

ResMgr *ResMgr::manager = nullptr;

ResMgr *ResMgr::Instance()
{
    if (!manager)
        manager = new ResMgr();

    return manager;
}

Mix_Chunk *ResMgr::findAudio(const std::string &name)
{
    if(soundPool.find(name) == soundPool.end()){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ("Audio " + name + " not found!").c_str(), nullptr);
        return nullptr;
    }
    return soundPool[name];
}
SDL_Texture *ResMgr::findTexture(const std::string &name)
{
    if(texturePool.find(name) == texturePool.end()){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", ("Texture " + name + " not found!").c_str(), nullptr);
        return nullptr;
    }
    return texturePool[name];
}

void ResMgr::load(SDL_Renderer *renderer){
    using namespace std::filesystem;

    for(const auto& entry:directory_iterator("res")){
        if(entry.is_regular_file()){
            const path& path = entry.path();
            if(path.extension()==".png"){
                SDL_Texture* texture = IMG_LoadTexture(renderer, path.string().c_str());
                if(texture)
                    texturePool[path.stem().string()] = texture;
                else SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", IMG_GetError(), nullptr);
            }else if(path.extension()==".mp3"){
                Mix_Chunk* chunk = Mix_LoadWAV(path.string().c_str());
                if(chunk)
                    soundPool[path.stem().string()] = chunk;
                else SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", Mix_GetError(), nullptr);

            }
        }
    }
}