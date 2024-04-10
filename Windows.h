#pragma once
#include<vector>
#include "Object.h"
class BaseWindow {
public:
    std::vector<Object*> Objects;
    std::vector<PushButton*> Buttons;

    BaseWindow() {}
    virtual void draw(sf::RenderWindow& window) {
        for (auto&& Obj : Objects)
            Obj->draw(window);
        for (auto&& Obj : Buttons)
            Obj->draw(window);
    }
    virtual void update(sf::RenderWindow& window) {
        for (auto&& Obj : Buttons)
            Obj->update(window);
    }
    virtual void input(sf::RenderWindow& window, isW &is_w) {
        for (auto&& Obj : Buttons) {
            Obj->input(window, is_w);
        }
    }
};
