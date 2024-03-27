#pragma once
// экран
constexpr unsigned WINDOW_HEIGHT = 720;
constexpr unsigned WINDOW_WIDTH = 1280;
constexpr int TILE_SIZE = 32;
constexpr unsigned TEXT_SIZE = 20;
constexpr unsigned BIG_TEXT_SIZE =50;

//скорость отрисовки
constexpr unsigned TIME_SCALE = 300;


//игровые константы
constexpr float PLAYER_SPEED = 0.1f;
constexpr float JUMP = -0.3f;
constexpr float GRAVITATION = 0.0002f;

constexpr unsigned START_X = 100; //начальное положение игрока
constexpr unsigned START_Y = 700;
 
constexpr float W = 96.f;  //ширина и высота спрайта слизн€. Ќеобходимо кратность 2
constexpr float H = 54.f;


// параметры меню
constexpr unsigned MENU_X = 100; //сдвиг текста меню по горизонтали
constexpr unsigned NEW_GAME_Y = 200;//положение кнопки "нова€ игра"
constexpr unsigned EXIT_Y = 300;//положение кнопки "выход"

constexpr unsigned BUTTON_WIDTH = 300;
constexpr unsigned BUTTON_HEIGHT = 50;
