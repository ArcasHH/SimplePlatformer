
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <sstream>

#include "Constants.h"

#include "view.h"
#include "Player.h"
#include "Menu.h"
#include "SpriteManager.h"

#include "resources.h"
#include "map.h"
//#include "level.h"

using namespace sf;

void StartGame(RenderWindow &window) {
	SpriteManager playerSprite("hero1.png", "Hero");
	Player p("hero1.png", START_X, START_Y, W, H);

	Clock clock, gameTimeClock; //âğåìÿ èãğû 
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

		//ÎÁĞÀÁÎÒÊÀ ÍÀÆÀÒÈÉ ÊÍÎÏÎÊ
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed))
				window.close();
		}
		//if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }//ÂÛÕÎÄ ÈÇ ÈÃĞÛ ÍÀ Escape
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			//window.close();
			die_music.stop();
			music.stop();
			menu(window);
			p.x = START_X;
			p.y = START_Y;
			p.speed = 0, p.dx = 0, p.dy = 0;
			p.life = true, p.win = false, p.isMove = false, p.onGround = false;
		}

		for (int i = 0; i < HEIGHT_MAP; i++)//ÎÒĞÈÑÎÂÊÀ ÊÀĞÒÛ
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
				if (TileMap[i][j] == 'X')  s_map.setTextureRect(IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((TileMap[i][j] == 'W')) s_map.setTextureRect(IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				s_map.setPosition(static_cast<float>(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
				window.draw(s_map);
			}

		if (p.life) {//×ÒÎ ÄÅËÀÒÜ ÏÎÊÀ ÆÈÂÛ
			gameTime = static_cast<int>(gameTimeClock.getElapsedTime().asSeconds());
			getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
			window.draw(p.sprite);
		}
		if (p.win) { //×ÒÎ ÏĞÎÈÑÕÎÄÈÒ ÏĞÈ ÏÎÁÅÄÅ
			win_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
			window.draw(win_text);
		}
		else if (!p.life) { // ×ÒÎ ÏĞÎÈÑÕÎÄÈÒ ÏĞÈ ÑÌÅĞÒÈ///

			if (die_music.getStatus() == SoundSource::Status::Stopped) {
				die_music.play();
				music.pause();
			}
			if (view.getCenter().y < 3.5 * WINDOW_HEIGHT) {
				view.move(0, 1);
				die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(die_text);
			}
			else {//ÌÓÇÛÊÀ ÏĞÈ ÑÌÅĞÒÈ
				die_music.pause();
				restart_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(restart_text);
			}
		}
		if (p.onGround && p.life) {//ÇÂÓÊÈ ÏĞÛÆÊÀ
			jump_sound.play();
		}
		////////ÂÛÂÎÄ ÂĞÅÌÅÍÈ ÍÀ İÊĞÀÍ
		std::ostringstream gameTimeString;
		gameTimeString << gameTime;
		text.setString("time elapsed :  " + gameTimeString.str());
		text.setPosition(view.getCenter().x - WINDOW_WIDTH / 2 + 50, view.getCenter().y - WINDOW_HEIGHT / 2 + 50);
		window.draw(text);
		window.display();
	}
}


int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"/*, sf::Style::Fullscreen*/);
	view.reset(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	menu(window);//âûçîâ ìåíş

	///////////////////ÌÓÇÛÊÀ
	die_music.openFromFile("audio/die.ogg");
	music.openFromFile("audio/yuka-kitamura-epilogue.ogg");
	
	///////////////////ÇÂÓÊÈ
	jump_buffer.loadFromFile("audio/jump.ogg");// òóò çàãğóæàåì â áóôåğ ÷òî òî
	jump_sound.setBuffer(jump_buffer);

	
	///////////////////ÊÀĞÒÀ
	map_image.loadFromFile("images/map.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);

	//////////////////ÒÅÊÑÒÛ
	font.loadFromFile("nyashasans.ttf");
	text.setFont(font);
	die_text.setFont(font);
	win_text.setFont(font);
	restart_text.setFont(font);

	StartGame(window);
	

	music.play();
	
	return 0;
}
