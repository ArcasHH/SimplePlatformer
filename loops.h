#pragma once
#include "Constants.h"
#include "view.h"
#include "resources.h"
#include "Player.h"
#include "SpriteManager.h"
#include "menu.h"
#include "dieScreen.h"
using namespace sf;
void StartGame(RenderWindow& window, const sf::String Map[HEIGHT_MAP]) {
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

		p.update(time, Map);

		window.setView(view);
		window.clear();

		//ÎÁĞÀÁÎÒÊÀ ÍÀÆÀÒÈÉ ÊÍÎÏÎÊ
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed))
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { break; }//ÂÛÕÎÄ ÈÇ ÈÃĞÛ ÍÀ Escape
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			die_music.stop();
			music.stop();
			menu(window);
			if (lvl == 1) { StartGame(window, Map1); }
			if (lvl == 2) { StartGame(window, Map2); }
			if (lvl == 3) { StartGame(window, Map3); }

		}

		for (int i = 0; i < HEIGHT_MAP; i++)//ÎÒĞÈÑÎÂÊÀ ÊÀĞÒÛ
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (Map[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
				if (Map[i][j] == 'X')  s_map.setTextureRect(IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((Map[i][j] == '0')) s_map.setTextureRect(IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((Map[i][j] == 'W')) s_map.setTextureRect(IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
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
			die_screen(window);
#if 0	
			if (die_music.getStatus() == SoundSource::Status::Stopped) {
				die_music.play();//ÌÓÇÛÊÀ ÏĞÈ ÑÌÅĞÒÈ
				music.pause();
			}
			if (view.getCenter().y < 3.5 * WINDOW_HEIGHT) {
				view.move(0, 1);
			}
			die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
			window.draw(die_text);

			if (view.getCenter().y < 3.5 * WINDOW_HEIGHT) {
				view.move(0, 1);
				die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(die_text);
			}
			else {
				die_music.pause();
				restart_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
				window.draw(restart_text);
			}
#endif
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


