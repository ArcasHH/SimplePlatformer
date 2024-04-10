#pragma once
#include<vector>
#include "Object.h"
class BaseWindow {
public:
    std::vector<Object*> Objects;
    std::vector<PushButton*> Buttons;

    BaseWindow() = default;
    virtual ~BaseWindow() = default;

    virtual void input(sf::RenderWindow& window, isW& is_w) {
        for (auto&& Obj : Buttons) {
            Obj->input(window, is_w);
        }
    }
    virtual void update(sf::RenderWindow& window) {
        for (auto&& Obj : Buttons)
            Obj->update(window);
    }
    virtual void draw(sf::RenderWindow& window) {
        for (auto&& Obj : Objects)
            Obj->draw(window);
        for (auto&& Obj : Buttons)
            Obj->draw(window);
    }
    
    
    
};

class GameWindow final : public BaseWindow {
public:
    Player p;
    Player* p_ref = &p;
    GameWindow() = default;
    ~GameWindow() = default;
    void input(sf::RenderWindow& window, isW& is_w)override {
        for (auto&& Obj : Buttons) {
            Obj->input(window, is_w);
        }
        p_ref->input();
    }
    void update(sf::RenderWindow& window) override {
        for (auto&& Obj : Buttons)
            Obj->update(window);
        p_ref->update();
        
    }
     void draw(sf::RenderWindow& window) override {
        for (auto&& Obj : Objects)
            Obj->draw(window);
        for (auto&& Obj : Buttons)
            Obj->draw(window);
        p_ref->draw(window);
    }
    
    

};
