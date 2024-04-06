#pragma once
#include<vector>
#include "Object.h"
class BaseWindow {
public:
    std::vector<Object*> Objects;

    BaseWindow() {}
    virtual void draw(sf::RenderWindow& window) {
        for (auto&& Obj : Objects)
            Obj->draw(window);
    }

    virtual ~BaseWindow() {
        for (auto&& Obj : Objects)
            delete Obj;
    }
};
