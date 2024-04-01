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

	///////////////////Ã”«€ ¿
	die_music.openFromFile("audio/die.ogg");
	win_music.openFromFile("audio/dragon_dance.ogg");
	music.openFromFile("audio/yuka-kitamura-epilogue.ogg");
	music_menu.openFromFile("audio/Akira_Yamaoka_Never_Forgive_Me_Never_Forget_Me.ogg");
	music_menu.setVolume(10);
	win_music.setVolume(10);
	music.setLoop(true);
	win_music.setLoop(true);
	music_menu.setLoop(true);
	die_music.setLoop(false);
	
	///////////////////«¬” »
	jump_buffer.loadFromFile("audio/jump.ogg");
	jump_sound.setBuffer(jump_buffer);

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

	if (music.getStatus() == SoundSource::Status::Playing) {
		music.stop();
	}
	return 0;
}