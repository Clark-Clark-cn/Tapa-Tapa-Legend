#include "screens/main/button.h"

void Button::setCallback(std::function<void()> callback){
    this->callback=callback;
}

void Button::setName(const std::string& name){
    this->name=name;
}

void Button::onRender(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer,200,60,50,255);
    SDL_RenderFillRect(renderer,&rect);

    SDL_Surface* textSurface=TTF_RenderText_Blended(ResMgr::Instance()->findFont("text"),
    name.c_str(),{0,0,0,255});
    SDL_Texture* textTexture=SDL_CreateTextureFromSurface(renderer,textSurface);
    SDL_RenderCopy(renderer,textTexture,nullptr,&rect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

bool Button::onCursorUp(){
    if(callback)callback();
    return true;
}