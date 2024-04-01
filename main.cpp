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

	/////////////////// ¿–“¿
	map_image.loadFromFile("images/map.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);

	//////////////////“≈ —“€
	font.loadFromFile("nyashasans.ttf");
	text.setFont(font);
	die_text.setFont(font);
	win_text.setFont(font);

	dragon.loadFromFile("images/sprite_dragon.png");

	menu(window);//‚˚ÁÓ‚ ÏÂÌ˛

	return 0;
}