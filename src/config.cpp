#include "config.h"
#include <fstream>

#include <SDL.h>

Config* Config::instance = nullptr;
Config* Config::defaultConfig = nullptr;

ConfigItem ConfigItem::loadFromString(const std::string& str, std::string& key){
    auto d=str.find('=');
    if(d==std::string::npos){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
            "config error", ("cannot parse " + str).c_str(), nullptr);
        return ConfigItem(0);
    }
    std::string value = str.substr(d + 1);
    key = str.substr(0, d);
    if(value=="true" || value=="false"){
        return ConfigItem(value=="true");
    }
    else if(value.find("Point")!=std::string::npos){
        auto comma = value.find(',');
        auto pointX = value.substr(6, comma-6);
        auto pointY = value.substr(comma+1, value.size()-comma-2);
        if(comma==std::string::npos || pointX.empty() || pointY.empty()){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
                "config error", ("cannot parse point " + value + " for key " + key).c_str(), nullptr);
            return ConfigItem(0);
        }
        int x=0, y=0;
        try{
            x=std::stoi(pointX);
            y=std::stoi(pointY);
        }catch(...){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
                "config error", ("cannot parse point " + value + " for key " + key).c_str(), nullptr);
            return ConfigItem(0);
        }
        return ConfigItem(Point{x, y});
    }
    else{
        try{
            if(value.find('.')!=std::string::npos){
                return ConfigItem(std::stof(value));
            }
            else{
                return ConfigItem(std::stoi(value));
            }
        }catch(...){
            return ConfigItem(value.c_str());
        }
    }
}

void Config::load(){
    std::ifstream file("config.ini");
    if(!file.is_open()){
        return;
    }
    std::string line;
    std::string key;
    while(std::getline(file, line)){
        auto item = ConfigItem::loadFromString(line, key);
        if(key.empty()) continue;
        items[key] = item;
    }
}

void Config::save() const{
    std::ofstream file("config.ini", std::ios::trunc);
    if(!file.is_open()){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", "Failed to open config file for writing!", nullptr);
        return;
    }
    for(const auto& item : items){
        file << item.second.asSavingString(item.first) << std::endl;
    }
}

const ConfigItem& Config::get(const std::string& key) const{
    if(items.find(key)==items.end()){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", ("Key " + key + " not found!").c_str(), nullptr);
        if(!isDefaults && defaultConfig){
            return defaultConfig->get(key);
        }
        static const ConfigItem defaultItem("0");
        return defaultItem;
    }
    return items.at(key);
}

void Config::setifno(const std::string& key, const ConfigItem& item){
    if(items.find(key)==items.end()){
        items[key] = item;
    }
    defaultConfig->set(key, item);
}

void Config::defaults(){
    setifno("region.bcBoxBundle.size", Point(160,88));
    setifno("region.colaBundle.size", Point(120,124));
    setifno("region.mbBoxBundle.size", Point(160,88));
    setifno("region.microwaveOven.size", Point(284,176));
    setifno("region.rcpBoxBundle.size", Point(160,88));
    setifno("region.spriteBundle.size", Point(120,124));
    setifno("region.takeoutBox.size", Point(120,55));
    setifno("region.tbBundle.size", Point(112,96));
    setifno("region.trashCan.size", Point(143,140));
    setifno("region.deliveryDriver.size", Point(192,272));
    setifno("region.clock.size", Point(64,64));
    setifno("region.coin.size",Point(30,30));

    setifno("region.deliveryDriver1.pos", Point(385, 142));
    setifno("region.deliveryDriver2.pos", Point(690, 142));
    setifno("region.deliveryDriver3.pos", Point(995, 142));
    setifno("region.colaBundle.pos", Point(300, 390));
    setifno("region.spriteBundle.pos", Point(425, 390));
    setifno("region.tbBundle.pos", Point(550, 418));
    setifno("region.mbBoxBundle.pos", Point(225, 520));
    setifno("region.bcBoxBundle.pos", Point(395, 520));
    setifno("region.rcpBoxBundle.pos", Point(565, 520));
    setifno("region.microwaveOven1.pos", Point(740, 400));
    setifno("region.microwaveOven2.pos", Point(975, 400));
    setifno("region.takeoutBox1.pos", Point(750, 580));
    setifno("region.takeoutBox2.pos", Point(875, 580));
    setifno("region.takeoutBox3.pos", Point(1000, 580));
    setifno("region.takeoutBox4.pos", Point(1125, 580));
    setifno("region.trashCan.pos", Point(50, 550));

    setifno("region.start.pos",Point(500,300));
    setifno("region.start.size",Point(280,120));

    setifno("deliveryDriver.waitTime", 40.0f);
    setifno("deliveryDriver.maxDrinks", 8);
    setifno("deliveryDriver.maxMeals", 4);
    setifno("deliveryDriver.coinMultiplier", 1.5f);
    setifno("clock.cost", 5);
    setifno("microwaveOven.cost", 20);
    setifno("microwaveOven.workTime", 5.0f);
    setifno("cursor.returnTime", 0.2f);
    setifno("money.count", 100);

    setifno("time.game",300.0f);
    setifno("time.GoMenu", 2.0f);

    setifno("window.width", 1280);
    setifno("window.height", 720);
    setifno("window.fullscreen", false);
    setifno("window.fps", 144);
    setifno("window.vsync", false);
    setifno("audio.volume", 64);
    setifno("showTips",true);
    save();
}