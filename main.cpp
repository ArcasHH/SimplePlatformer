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

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
	view.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

	/////////////////// ¿–“¿
	map_image.loadFromFile("images/map.png");
	map.loadFromImage(map_image);
	s_map.setTexture(map);

	//////////////////“≈ —“€
	font.loadFromFile("nyashasans.ttf");
	text.setFont(font);
	die_text.setFont(font);
	die_text.setPosition(view.getCenter().x - 250, view.getCenter().y - 100);
	win_text.setFont(font);
	win_text.setPosition(view.getCenter().x - 250, view.getCenter().y - 100);
	//////////////////“≈ —“”–€
	dragon.loadFromFile("images/sprite_dragon.png");
	BackgroundImage bg("menu_bg.png", MENU_X + 900, 200);

	//////////////////////////////////////////////////////////////////////////////////////////
	SpriteManager playerSprite("hero1.png", "Hero");
	Player p("left.png", "right.png", START_X, START_Y-200, 128, 128);

	///////////////////Ã”«€ ¿ » «¬” »
	MyMusic play("yuka-kitamura-epilogue.ogg", 100, true);
	MyMusic die("die.ogg", 100, false);
	MyMusic win("dragon_dance.ogg", 10, true);
	MyMusic menu("Akira_Yamaoka_Never_Forgive_Me_Never_Forget_Me.ogg", 10, true);
	MySound jump("jump.ogg", 100);

	////////////////// ÕŒœ »
	PushButton restart_button("restart.png", view.getCenter().x - 400, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));
	PushButton next_button("next.png", view.getCenter().x - 400, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));
	PushButton menu_button("menu.png", view.getCenter().x - 200, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));
	PushButton exit_button("exit.png", view.getCenter().x , view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));
	// ÕŒœ » ¬ Ã≈Õﬁ
	PushButton Exit_button("exit256.png", MENU_X, EXIT_Y, 256, 256, sf::Color::White, sf::Color(184, 221, 20));
	PushButton NewGame_button("play256.png", MENU_X, NEW_GAME_Y, 256, 256, sf::Color::White, sf::Color(184, 221, 20));
	PushButton num1("1.png", LVL_NUM_X, NEW_GAME_Y + 64, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));
	PushButton num2("2.png", LVL_NUM_X + LVL_NUM_SIZE, NEW_GAME_Y + 64, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));
	PushButton num3("3.png", LVL_NUM_X + 2 * LVL_NUM_SIZE, NEW_GAME_Y + 64, LVL_NUM_SIZE, LVL_NUM_SIZE, sf::Color::White, sf::Color(184, 221, 20));

	int gameTime = 0;
	isMenu = true;// ¬ Õ¿◊¿À≈ «¿œ”— ¿≈Ã Ã≈Õﬁ
	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!isGame && (play.music.getStatus() == sf::SoundSource::Status::Playing)) {
			play.music.stop();
		}
		if (!isDie && (die.music.getStatus() == sf::SoundSource::Status::Playing)) {
			die.music.stop();
		}
		if (!isMenu && (menu.music.getStatus() == sf::SoundSource::Status::Playing)) {
			menu.music.stop();
		}
		if (!isWin && (win.music.getStatus() == sf::SoundSource::Status::Playing)) {
				win.music.stop();
		}

		
		if (isMenu && !isExit) {
			if (menu.music.getStatus() != sf::SoundSource::Status::Playing) {
				menu.music.play();
				view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
				window.setView(view);
			}
			menuScreen(window, bg, NewGame_button, Exit_button, num1, num2, num3);
			window.display();
			continue;
		}

		else if (isGame && !isExit) {
			if (play.music.getStatus() != sf::SoundSource::Status::Playing) {
				play.music.play();
				p.restart(START_X, START_Y - 200, 128, 128);
				gameTime = 0;
			}
			if (lvl == 1) { 
				StartGame(window, Map1, p, gameTime); 
				if (p.onGround && p.life) {
					jump.sound.play();
				}
				window.display();
				continue;
			}
			if (lvl == 2) { 
				StartGame(window, Map2,  p, gameTime);  
				if ( p.onGround && p.life) {
					jump.sound.play();
				}
				window.display();
				continue;
			}
			if (lvl == 3) { 
				StartGame(window, Map3, p, gameTime);  
				if ( p.onGround && p.life) {
					jump.sound.play();
				}
				window.display();
				continue;
			}

		}
		else if (isDie && !isExit) {
			if (die.music.getStatus() != sf::SoundSource::Status::Playing) {
				die.music.play();
				view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
				window.setView(view);
			}
			dieScreen(window, restart_button, menu_button, exit_button);
			window.display();
			continue;
		}
		else if (isWin && !isExit) {
			if (win.music.getStatus() != sf::SoundSource::Status::Playing) {
				win.music.play();
				view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
				window.setView(view);
			}
			winScreen(window, next_button, menu_button, exit_button);
			window.display();
			continue;
		}

		if (isExit)	return 0;
	}
	return 0;
}