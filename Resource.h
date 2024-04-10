#pragma once
#include "Windows.h"

namespace {

    BaseWindow w_menu;
    BaseWindow w_settings;

    PushButton menu_exit("images/exit256.png", 100, 700, exit_button());
    PushButton menu_play("images/play256.png", 100, 100, settings_button());
    PushButton menu_settings("images/settings256.png", 100, 400, settings_button());
    PushButton settings_menu("images/back256.png", 100, 700, menu_button());

    void load_menu_objects() {
        w_menu.Buttons.push_back(&menu_play);
        w_menu.Buttons.push_back(&menu_settings);
        w_menu.Buttons.push_back(&menu_exit);
        
    }
    void load_settings_objects() {
        w_settings.Buttons.push_back(&settings_menu);
    }
}
