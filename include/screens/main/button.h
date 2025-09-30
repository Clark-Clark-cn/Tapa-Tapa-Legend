#pragma once

#include "region.h"
#include <functional>
#include <string>

class Button:public Region{
    std::function<void()> callback=nullptr;
    std::string name="";
public:
    Button(int x=0, int y=0, int w=100, int h=50):Region({x,y,w,h}){}
    ~Button()=default;

    void setCallback(std::function<void()> callback);
    void setName(const std::string& name);

    void onRender(SDL_Renderer* renderer)override;
    bool onCursorUp()override;
};