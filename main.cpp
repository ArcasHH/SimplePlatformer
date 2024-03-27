
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <sstream>
#include "Constants.h"
#include "map.h"
#include "view.h"
#include "Player.h"
#include "Menu.h"
#include "SpriteManager.h"
//#include "level.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"/*, sf::Style::Fullscreen*/);
	view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	///////////////////МУЗЫКА
	Music die_music;
	die_music.openFromFile("audio/die.ogg");
	Music music;
	music.openFromFile("audio/yuka-kitamura-epilogue.ogg");
	music.play();
	///////////////////ЗВУКИ
	sf::SoundBuffer jump_buffer;
	jump_buffer.loadFromFile("audio/jump.ogg");// тут загружаем в буфер что то
	sf::Sound jump_sound;
	jump_sound.setBuffer(jump_buffer);

	

	menu(window);//вызов меню
	 
	///////////////////КАРТА
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	//Level lvl;//создали экземпляр класса уровень
	//lvl.LoadFromFile("map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.

	//////////////////ТЕКСТЫ
	Font font;
	font.loadFromFile("nyashasans.ttf");
	Text text("", font, TEXT_SIZE);
	Text die_text("YOU DIED", font, BIG_TEXT_SIZE);
	Text win_text("YOU WIN", font, BIG_TEXT_SIZE);
	Text restart_text("press R", font, BIG_TEXT_SIZE);


	SpriteManager playerSprite("hero1.png", "Hero");
	Player p("hero1.png", START_X, START_Y, W, H);

	float currentFrame = 0;
	Clock clock, gameTimeClock; //время игры 
	int gameTime = 0;
	float dX = 0, dY = 0;
	while (window.isOpen())
	{
		float time = static_cast<float>(clock.getElapsedTime().asMicroseconds());
		clock.restart();
		time = time / TIME_SCALE;

		p.update(time);

		window.setView(view);
		window.clear();

		//ОБРАБОТКА НАЖАТИЙ КНОПОК
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed))
				window.close();
		}
		//if (Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }// рестарт.
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//ВЫХОД ИЗ ИГРЫ НА Escape
		if (Keyboard::isKeyPressed(Keyboard::R)) { window.close(); }


		for (int i = 0; i < HEIGHT_MAP; i++)//ОТРИСОВКА КАРТЫ
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
				if (TileMap[i][j] == 'X')  s_map.setTextureRect(IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((TileMap[i][j] == 'W')) s_map.setTextureRect(IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				s_map.setPosition(static_cast<float>(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
				window.draw(s_map);
			}

		if (p.life) {//ЧТО ДЕЛАТЬ ПОКА ЖИВЫ
			gameTime = static_cast<int>(gameTimeClock.getElapsedTime().asSeconds());
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			window.draw(p.sprite);
		}
		if (p.win) { //ЧТО ПРОИСХОДИТ ПРИ ПОБЕДЕ
			win_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
			window.draw(win_text);
		}
		else if (!p.life){ // ЧТО ПРОИСХОДИТ ПРИ СМЕРТИ///
#if 0
			sf::Clock clock;
			float time = 0;
			while (time < 3.5)
			{
				time = clock.getElapsedTime().asSeconds();
				view.move(0, 1.5);
				die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(die_text);
				if (time >= 3) {
					//menu(window);//вызов меню
					break;
				}
			}
#else
			if (die_music.getStatus() == SoundSource::Status::Stopped) {
				die_music.play();
				music.pause();
			}
			if(view.getCenter().y < 3.5 * WINDOW_HEIGHT)
				view.move(0, 1);
			if (die_music.getStatus() != SoundSource::Status::Paused) {
				die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(die_text);
			}
			if (die_music.getStatus() == SoundSource::Status::Paused) {
				restart_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(restart_text);
			}
			
#endif
		}
		if (view.getCenter().y > 3.4 * WINDOW_HEIGHT) {//МУЗЫКА ПРИ СМЕРТИ
			die_music.pause();
			//window.close();
			//menu(window);//вызов меню
			//break;
		}
		if (p.onGround&&p.life) {//ЗВУКИ ПРЫЖКА
			jump_sound.play();
		}
		
		std::ostringstream gameTimeString; 
		gameTimeString << gameTime;		
		text.setString("time elapsed :  " + gameTimeString.str()); 
		text.setPosition(view.getCenter().x - WINDOW_WIDTH/2 +50, view.getCenter().y - WINDOW_HEIGHT/2 +50);

		
		window.draw(text);
		window.display();
	}
	music.stop();
	return 0;
}
