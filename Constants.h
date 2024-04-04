#pragma once
// параметры экрана
 unsigned WINDOW_WIDTH = 1920; // по умолчанию
 unsigned WINDOW_HEIGHT = 1080;
 int fps = 60;

constexpr int HEIGHT_MAP = 128;//размер карты высота
constexpr int WIDTH_MAP = 64;//размер карты ширина 

constexpr int TILE_SIZE = 32;
constexpr int LVL_NUM_SIZE = 128;

constexpr unsigned TEXT_SIZE = 20;
constexpr unsigned BIG_TEXT_SIZE =50;

//скорость отрисовки
constexpr unsigned TIME_SCALE = 300;
constexpr float SPEED_ANIM = 0.04f; //чем меньше, тем быстрее
//игровые константы
constexpr float PLAYER_SPEED = 0.15f;
constexpr float JUMP = -0.3f;
constexpr float GRAVITATION = 0.0002f;

constexpr int START_X = 100; //начальное положение игрока
constexpr int START_Y = 3872;
 
constexpr float W = 128.f;  //ширина и высота спрайта 
constexpr float H = 128.f;


// параметры меню
constexpr unsigned MENU_X = 200; //сдвиг текста меню по горизонтали
constexpr unsigned NEW_GAME_Y = 100;//положение кнопки "новая игра"
constexpr unsigned SETTINGS_Y = 400;//положение кнопки "настройки"
constexpr unsigned EXIT_Y = 700;//положение кнопки "выход"

constexpr unsigned LVL_NUM_X = 500;
constexpr unsigned LVL_NUM_Y = 100;



