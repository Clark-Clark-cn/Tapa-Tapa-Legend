#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <SDL.h>

struct Point{
    int x;
    int y;
    Point(int x=0, int y=0) : x(x), y(y) {}
};

class ConfigItem{
public:
    std::string value;
    
    static ConfigItem loadFromString(const std::string& str, std::string& key);
    ConfigItem() : value("0") {}
    ConfigItem(bool v) : value(v ? "true" : "false") {}
    ConfigItem(int v) : value(std::to_string(v)) {}
    ConfigItem(float v) : value(std::to_string(v)) {}
    ConfigItem(const char* v) : value(std::string(v)) {}
    ConfigItem(const Point& v) : value("Point{" + std::to_string(v.x) + "," + std::to_string(v.y) + "}") {}
    ~ConfigItem() = default;

    bool asBool() const { return value == "true"; }
    int asInt() const { 
        try{
        return std::stoi(value); }
        catch(...){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", "Value is not an integer!", nullptr);
            return 0;
        }
    }
    float asFloat() const { 
        try{
            return std::stof(value);
        }
        catch(...){
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", "Value is not a float!", nullptr);
            return 0.0f;
        }
    }
    std::string asString() const { return value; }
    std::string asSavingString(const std::string& key) const { return (key + "=" + value); }
    Point asPoint() const {
        if(value.find("Point{", 0) == 0 && value.back() == '}'){
            size_t comma = value.find(',', 6);
            if(comma != std::string::npos){
                try{
                    int x = std::stoi(value.substr(6, comma - 6));
                    int y = std::stoi(value.substr(comma + 1, value.size() - comma - 2));
                    return Point{x, y};
                }
                catch(...){
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", ("Value " + value + " is not a Point!").c_str(), nullptr);
                    return Point{0, 0};
                }
            }
        }
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config Error", ("Value " + value + " is not a Point!").c_str(), nullptr);
        return Point{0, 0};
    }


    operator bool() const { return asBool(); }
    operator int() const { return asInt(); }
    operator float() const { return asFloat(); }
    operator std::string() const { return asString(); }
    operator Point() const { return asPoint(); }
};

class Config{
    std::unordered_map<std::string, ConfigItem> items;
    static Config* instance;
    static Config* defaultConfig;
    bool isDefaults = false;
    Config(bool isDefaults = false) : isDefaults(isDefaults){
        if(isDefaults) return;
        load();
        defaults();
    }
    ~Config(){
        if(isDefaults) return;
        save();
    }
    void load();
    void defaults();
public:
    static Config* Instance(){
        if(!instance){
            defaultConfig = new Config(true);
            instance = new Config(false);
        }
        return instance;
    }
    void save() const;

    void set(const std::string& key, const ConfigItem& item){items[key] = item;}

    const ConfigItem& get(const std::string& key) const;

    void setifno(const std::string& key, const ConfigItem& item);
};