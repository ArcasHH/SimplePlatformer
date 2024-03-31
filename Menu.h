#pragma once
#include "Constants.h"
#include "view.h"
#include "resources.h"
#include "Player.h"
using namespace sf;

void menu(RenderWindow& window) {

	menuTexture1.loadFromFile("images/111.png");//кнопка новой игры
	menuTexture2.loadFromFile("images/222.png");//кнопка выхода

	PushButton num1("1.png", LVL_NUM_X, LVL_NUM_Y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton num2("2.png", LVL_NUM_X, LVL_NUM_Y + LVL_NUM_SIZE, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Green);
	PushButton num3("3.png", LVL_NUM_X, LVL_NUM_Y + 2 * LVL_NUM_SIZE, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Blue);
	menuBackground.loadFromFile("images/screen.jpg");// задний фон

	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;

	menu1.setPosition(MENU_X, NEW_GAME_Y);
	menu2.setPosition(MENU_X, EXIT_Y);
	menuBg.setPosition(MENU_X + 500, 0);

	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);
	//ПРОИГРЫВАНИЕ МУЗЫКИ МЕНЮ
	music_menu.openFromFile("audio/yuka-kitamura-epilogue.ogg");
	if (music_menu.getStatus() == SoundSource::Status::Stopped) {
		music_menu.play();
	}

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);

		menuNum = 0;
		window.clear(Color::Black);

		if (IntRect(MENU_X, NEW_GAME_Y, BUTTON_WIDTH, BUTTON_HEIGHT).contains(Mouse::getPosition(window))) {
			menu1.setColor(Color(200, 90, 90));
			menuNum = 1;
		}
		if (IntRect(MENU_X, EXIT_Y, BUTTON_WIDTH, BUTTON_HEIGHT).contains(Mouse::getPosition(window))) {
			menu2.setColor(Color(200, 90, 90));
			menuNum = 2;
		}
		num1.paint_button(window);
		num2.paint_button(window);
		num3.paint_button(window);

		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)) {
				window.close();
				music_menu.stop();
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

			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.draw(num1.sprite);
		window.draw(num2.sprite);
		window.draw(num3.sprite);

		window.display();
	}
	music_menu.stop();
}
