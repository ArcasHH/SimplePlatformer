#pragma once
#include "Constants.h"
#include "view.h"
#include "resources.h"
#include "Player.h"
#include "SpriteManager.h"

using namespace sf;

void die_screen(RenderWindow& window);
void win_screen(RenderWindow& window);
void menu(RenderWindow& window);

void StartGame(RenderWindow& window, sf::String *Map) {
	SpriteManager playerSprite("hero1.png", "Hero");

	MyMusic play("yuka-kitamura-epilogue.ogg", 100, true);
	play.music.play();
	MySound jump("jump.ogg", 100);

	Player p("hero1.png", START_X, START_Y, W, H);
	Clock clock, gameTimeClock; //âğåìÿ èãğû 
	int gameTime = 0;
	float dX = 0, dY = 0;
	bool game = true;
	while (game)
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
			if ((event.type == sf::Event::Closed)){
				play.music.stop();
				game = false;
				return;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { //ÂÛÕÎÄ ÈÇ ÈÃĞÛ ÍÀ Escape
			if (play.music.getStatus() == SoundSource::Status::Playing) {
				play.music.stop();
			}
			return; 
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			play.music.stop();
			game = false;
			menu(window);
		}

		//ÎÒĞÈÑÎÂÊÀ ÊÀĞÒÛ
		for (int i = 0; i < HEIGHT_MAP; i++)
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
			play.music.stop();
			game = false;
			win_screen(window);
			return;
		}
		else if (!p.life) { // ×ÒÎ ÏĞÎÈÑÕÎÄÈÒ ÏĞÈ ÑÌÅĞÒÈ///
			play.music.stop();
			game = false;
			die_screen(window);
			return;
		}
		if (game && p.onGround && p.life) {//ÇÂÓÊÈ ÏĞÛÆÊÀ
			jump.sound.play();
		}
		////////ÂÛÂÎÄ ÂĞÅÌÅÍÈ ÍÀ İÊĞÀÍ
		std::ostringstream gameTimeString;
		gameTimeString << gameTime;
		text.setString("time elapsed :  " + gameTimeString.str());
		text.setPosition(view.getCenter().x - WINDOW_WIDTH / 2 + 50, view.getCenter().y - WINDOW_HEIGHT / 2 + 50);
		window.draw(text);
		window.display();
	}
	if (play.music.getStatus() == SoundSource::Status::Playing) {
		play.music.stop();
	}
}

void die_screen(RenderWindow& window) {
	MyMusic die("die.ogg", 100, false);
	die.music.play();

	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);
	PushButton restart_button("restart.png", view.getCenter().x - 300, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	PushButton menu_button("menu.png", view.getCenter().x - 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184,221,20));
	PushButton exit_button("exit.png", view.getCenter().x + 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	bool isDieScreen = true;
	die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);

	while (isDieScreen)
	{
		window.clear(Color::Black);

		window.draw(die_text);

		restart_button.paint_button(window);
		menu_button.paint_button(window);
		exit_button.paint_button(window);

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)) {
				die.music.stop();
				return;
			}
		}
		//ÄÅÉÑÒÂÈß ÏĞÈ ÍÀÆÀÒÈÈ ÊÍÎÏÎÊ
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (restart_button.is_pos(window)) {
				die.music.stop();
				isDieScreen = false;
				if (lvl == 1) { 
					StartGame(window, Map1); 
					return;
				}
				if (lvl == 2) { 
					StartGame(window, Map2); 
					return;
				}
				if (lvl == 3) { 
					StartGame(window, Map3); 
					return;
				}
			}
			if (menu_button.is_pos(window)) {
				die.music.stop();
				isDieScreen = false;
				menu(window);
				return;
			}
			if (exit_button.is_pos(window)) {
				die.music.stop();
				return;
			}
		}
		window.draw(restart_button.sprite);
		window.draw(menu_button.sprite);
		window.draw(exit_button.sprite);
		window.display();
	}
	if (die.music.getStatus() == SoundSource::Status::Playing) {
		die.music.stop();
	}
}

void win_screen(RenderWindow& window) {
	MyMusic win("dragon_dance.ogg", 10, true);
	win.music.play();

	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);

	PushButton next_button("next.png", view.getCenter().x - 300, view.getCenter().y + 100, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	PushButton menu_button("menu.png", view.getCenter().x - 100, view.getCenter().y + 100, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	PushButton exit_button("exit.png", view.getCenter().x + 100, view.getCenter().y + 100, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	
/////////////////////////////////////////////////////////

	bool isWinScreen = true;
	win_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);

	while (isWinScreen)
	{
		window.clear(Color::Black);

		next_button.paint_button(window);
		menu_button.paint_button(window);
		exit_button.paint_button(window);
		dancing_dragon.draw_anim();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)) {
				win.music.stop();
				return;
			}
		}
		//ÄÅÉÑÒÂÈß ÏĞÈ ÍÀÆÀÒÈÈ ÊÍÎÏÎÊ
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (next_button.is_pos(window)) {
				win.music.stop();
				isWinScreen = false;
				if (lvl == 1) { 
					lvl = 2;
					StartGame(window, Map2); 
					return;
				}
				 if (lvl == 2) { 
					lvl = 3;
					StartGame(window, Map3);
					return;
				}
				 if (lvl == 3) { 
					lvl = 1;
					StartGame(window, Map1); 
					return;
				}
			}
			if (menu_button.is_pos(window)) {
				win.music.stop();
				isWinScreen = false;
				menu(window);
				return;
			}
			if (exit_button.is_pos(window)) {
				win.music.stop();
				return;
			}
		}
		window.draw(dancing_dragon.sprite);
		window.draw(next_button.sprite);
		window.draw(menu_button.sprite);
		window.draw(exit_button.sprite);
		window.draw(win_text);
		window.display();
	}
	if (win.music.getStatus() == SoundSource::Status::Playing) {
		win.music.stop();
	}
}


void menu(RenderWindow& window) {
	MyMusic menu("Akira_Yamaoka_Never_Forgive_Me_Never_Forget_Me.ogg", 10, true);
	menu.music.play();
	//ÊÍÎÏÊÈ Â ÌÅÍŞ
	PushButton Exit_button("exit256.png", MENU_X, EXIT_Y, 256, 256, Color::White, Color(184, 221, 20));
	PushButton NewGame_button("play256.png", MENU_X, NEW_GAME_Y, 256 , 256, Color::White, Color(184, 221, 20));
	PushButton num1("1.png", LVL_NUM_X,                    NEW_GAME_Y + 64, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	PushButton num2("2.png", LVL_NUM_X + LVL_NUM_SIZE,     NEW_GAME_Y + 64, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));
	PushButton num3("3.png", LVL_NUM_X + 2 * LVL_NUM_SIZE, NEW_GAME_Y + 64, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color(184, 221, 20));

	BackgroundImage bg("menu_bg.png", MENU_X + 900, 200);
	
	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);
	

	//ÏĞÎÈÃĞÛÂÀÍÈÅ ÌÓÇÛÊÈ ÌÅÍŞ
	menu.music.play();

	bool isMenu = true;
	//////////////////////////////ÌÅÍŞ///////////////////
	while (isMenu)
	{
		window.clear(Color::Black);

		NewGame_button.paint_button(window);
		Exit_button.paint_button(window);
		num1.paint_button(window);
		num2.paint_button(window);
		num3.paint_button(window);
		

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)) {
				menu.music.stop();
				return;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (num1.is_pos(window)) {
				num1.is_clicked = true;
				num2.is_clicked = false;
				num3.is_clicked = false;
				lvl = 1;
			}
			if (num2.is_pos(window)) {
				num1.is_clicked = false;
				num2.is_clicked = true;
				num3.is_clicked = false;
				lvl = 2;
			}
			if (num3.is_pos(window)) {
				num1.is_clicked = false;
				num2.is_clicked = false;
				num3.is_clicked = true;
				lvl = 3;
			}
			num1.paint_button(window);
			num2.paint_button(window);
			num3.paint_button(window);
			if (NewGame_button.is_pos(window)) {
				menu.music.stop();
				isMenu = false;
			}
			if (Exit_button.is_pos(window)) {
				menu.music.stop();
				return;
			}
		}
		window.draw(bg.sprite);
		window.draw(NewGame_button.sprite);
		window.draw(Exit_button.sprite);
		window.draw(num1.sprite);
		window.draw(num2.sprite);
		window.draw(num3.sprite);

		window.display();
	}
	if (menu.music.getStatus() == SoundSource::Status::Playing) {
		menu.music.stop();
	}

	if (lvl == 1) { StartGame(window, Map1); return; }
	if (lvl == 2) { StartGame(window, Map2); return; }
	if (lvl == 3) { StartGame(window, Map3); return; }
}