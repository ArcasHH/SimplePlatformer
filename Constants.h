#pragma once
// экран
constexpr unsigned WINDOW_HEIGHT = 1080;
constexpr unsigned WINDOW_WIDTH = 1920;
constexpr int TILE_SIZE = 32;
constexpr int LVL_NUM_SIZE = 128;
constexpr unsigned TEXT_SIZE = 20;
constexpr unsigned BIG_TEXT_SIZE =50;

//скорость отрисовки
constexpr unsigned TIME_SCALE = 300;


//игровые константы
constexpr float PLAYER_SPEED = 0.1f;
constexpr float JUMP = -0.3f;
constexpr float GRAVITATION = 0.0002f;

constexpr int START_X = 100; //начальное положение игрока
constexpr int START_Y = 700;
 
constexpr float W = 96.f;  //ширина и высота спрайта слизн€. Ќеобходимо кратность 2
constexpr float H = 54.f;


// параметры меню
constexpr unsigned MENU_X = 50; //сдвиг текста меню по горизонтали
constexpr unsigned NEW_GAME_Y = 200;//положение кнопки "нова€ игра"
constexpr unsigned EXIT_Y = 300;//положение кнопки "выход"

constexpr unsigned BUTTON_WIDTH = 300;
constexpr unsigned BUTTON_HEIGHT = 50;
constexpr unsigned LVL_NUM_X = 350;
constexpr unsigned LVL_NUM_Y = 100;
