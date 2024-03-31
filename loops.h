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
	music.play();
	SpriteManager playerSprite("hero1.png", "Hero");
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
			if ((event.type == sf::Event::Closed))
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { //ÂÛÕÎÄ ÈÇ ÈÃĞÛ ÍÀ Escape
			if (music.getStatus() == SoundSource::Status::Playing) {
				music.stop();
			}
			return; 
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			music.stop();
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
			music.stop();
			game = false;
			win_screen(window);
		}
		else if (!p.life) { // ×ÒÎ ÏĞÎÈÑÕÎÄÈÒ ÏĞÈ ÑÌÅĞÒÈ///
			music.stop();
			game = false;
			die_screen(window);
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
	if (music.getStatus() == SoundSource::Status::Playing) {
		music.stop();
	}
}

void die_screen(RenderWindow& window) {

	die_music.play();
	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);
	PushButton restart_button("restart.png", view.getCenter().x - 300, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton menu_button("menu.png", view.getCenter().x - 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton exit_button("exit.png", view.getCenter().x + 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
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
				window.close();
				return;
			}
		}
		//ÄÅÉÑÒÂÈß ÏĞÈ ÍÀÆÀÒÈÈ ÊÍÎÏÎÊ
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (restart_button.is_pos(window)) {
				die_music.stop();
				isDieScreen = false;
				if (lvl == 1) { StartGame(window, Map1); }
				if (lvl == 2) { StartGame(window, Map2); }
				if (lvl == 3) { StartGame(window, Map3); }
			}
			if (menu_button.is_pos(window)) {
				die_music.stop();
				isDieScreen = false;
				menu(window);
			}
			if (exit_button.is_pos(window)) {
				die_music.stop();
				return;
			}
		}
		window.draw(restart_button.sprite);
		window.draw(menu_button.sprite);
		window.draw(exit_button.sprite);
		window.display();
	}
	if (die_music.getStatus() == SoundSource::Status::Playing) {
		die_music.stop();
	}
}

void win_screen(RenderWindow& window) {

	
	

	
	

	//sf::IntRect rectSourceSprite(0, 0, 498,391);
	//sf::Sprite win_sprite(dragon, rectSourceSprite);
	//win_sprite.setPosition(100, 100);
	//sf::Clock win_clock;

	win_music.play();
	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);

	PushButton next_button("next.png", view.getCenter().x - 300, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton menu_button("menu.png", view.getCenter().x - 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton exit_button("exit.png", view.getCenter().x + 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	//BackgroundImage dance("sprite_dragon.png", 500, 500);
	Animation dance("sprite_dragon.png", 100, 100, 498, 391);
	
/////////////////////////////////////////////////////////

	bool isWinScreen = true;
	win_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);

	while (isWinScreen)
	{
		window.clear(Color::Black);
		//window.draw(dance.sprite);


		next_button.paint_button(window);
		menu_button.paint_button(window);
		exit_button.paint_button(window);
		dance.draw_anim();

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)) {
				window.close();
				return;
			}
		}
		//ÄÅÉÑÒÂÈß ÏĞÈ ÍÀÆÀÒÈÈ ÊÍÎÏÎÊ
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (next_button.is_pos(window)) {
				win_music.stop();
				isWinScreen = false;
				if (lvl == 1) { 
					lvl = 2;
					StartGame(window, Map2); 
				}
				if (lvl == 2) { 
					lvl = 3;
					StartGame(window, Map3);
				}
				if (lvl == 3) { 
					lvl = 1;
					StartGame(window, Map1); 
				}
			}
			if (menu_button.is_pos(window)) {
				win_music.stop();
				isWinScreen = false;
				menu(window);
			}
			if (exit_button.is_pos(window)) {
				win_music.stop();
				//window.close(); // íàäî íàïèñàòü ôóíêöèş, çàêğûâàşùóş âñå îêíà è âûêëş÷àşùóş âñş ìóçûêó
				return;
			}
		}
		//window.draw(dance.sprite);
		window.draw(next_button.sprite);
		window.draw(menu_button.sprite);
		window.draw(exit_button.sprite);
		window.draw(win_text);
		window.display();
	}
	if (win_music.getStatus() == SoundSource::Status::Playing) {
		win_music.stop();
	}
}


void menu(RenderWindow& window) {

	//ÊÍÎÏÊÈ Â ÌÅÍŞ
	PushButton Exit_button("222.png", MENU_X, EXIT_Y, BUTTON_WIDTH-100, BUTTON_HEIGHT, Color::White, Color::Red);
	PushButton NewGame_button("111.png", MENU_X, NEW_GAME_Y, BUTTON_WIDTH-100, BUTTON_HEIGHT, Color::White, Color::Red);
	PushButton num1("1.png", LVL_NUM_X, LVL_NUM_Y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton num2("2.png", LVL_NUM_X, LVL_NUM_Y + LVL_NUM_SIZE, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton num3("3.png", LVL_NUM_X, LVL_NUM_Y + 2 * LVL_NUM_SIZE, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);

	BackgroundImage bg("screen.jpg", MENU_X + 500, 0);
	
	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);

	//ÏĞÎÈÃĞÛÂÀÍÈÅ ÌÓÇÛÊÈ ÌÅÍŞ
	music_menu.play();

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
				window.close();
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
				music_menu.stop();
				isMenu = false;
			}
			if (Exit_button.is_pos(window)) {
				music_menu.stop();
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
	if (music_menu.getStatus() == SoundSource::Status::Playing) {
		music_menu.stop();
	}

	if (lvl == 1) { StartGame(window, Map1); }
	if (lvl == 2) { StartGame(window, Map2); }
	if (lvl == 3) { StartGame(window, Map3); }
}