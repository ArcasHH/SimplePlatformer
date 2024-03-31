
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <sstream>

#include "Constants.h"

#include "view.h"
#include "Player.h"
#include "loops.h"
#include "SpriteManager.h"

#include "resources.h"
#include "map.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
	view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	

	///////////////////МУЗЫКА
	die_music.openFromFile("audio/die.ogg");
	win_music.openFromFile("audio/dragon_dance.ogg");
	music.openFromFile("audio/yuka-kitamura-epilogue.ogg");
	
	///////////////////ЗВУКИ
	jump_buffer.loadFromFile("audio/jump.ogg");// тут загружаем в буфер что то
	jump_sound.setBuffer(jump_buffer);

	
	///////////////////КАРТА
	map_image.loadFromFile("images/map.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);

	//////////////////ТЕКСТЫ
	font.loadFromFile("nyashasans.ttf");
	text.setFont(font);
	die_text.setFont(font);
	win_text.setFont(font);
	//restart_text.setFont(font);

	menu(window);//вызов меню
	//if (lvl == 1) { StartGame(window, Map1); }
	//if (lvl == 2) { StartGame(window, Map2); }
	//if (lvl == 3) { StartGame(window, Map3); }

	music.play();
	
	return 0;
}
