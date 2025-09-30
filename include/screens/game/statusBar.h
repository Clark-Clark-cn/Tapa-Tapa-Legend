#pragma once

#include "region.h"

class StatusBar: public Region {
    unsigned int money = Config::Instance()->get("money.count").asInt();
public:
    StatusBar(int x, int y) : Region({x, y, 1280, 50}) {}
    ~StatusBar();
    void onRender(SDL_Renderer *renderer)override;
    void addMoney(int delta) { money += delta; }
    int getMoney() const { return money; }
    bool reduceMoney(int delta) {
        if(money>=delta){
            money-=delta;
            return true;
        }
        return false;
    }
};