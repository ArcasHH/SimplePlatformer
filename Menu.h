#pragma once
#include "Constants.h"
#include "view.h"
#include "resources.h"


void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");

	menuBackground.loadFromFile("images/screen.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = true;
	int menuNum = 0;
	menu1.setPosition(MENU_X, NEW_GAME_Y);
	menu2.setPosition(MENU_X, EXIT_Y);

	menuBg.setPosition(350, 0);
	view.setCenter(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/2);
	window.setView(view);
	//œ–Œ»√–€¬¿Õ»≈ Ã”«€ » Ã≈Õﬁ
	music_menu.openFromFile("audio/yuka-kitamura-epilogue.ogg");
	if (music_menu.getStatus() == SoundSource::Status::Stopped) {
		music_menu.play();
	}

	//////////////////////////////Ã≈Õﬁ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		
		menuNum = 0;
		window.clear(Color::Black);

		if (IntRect(MENU_X, NEW_GAME_Y, BUTTON_WIDTH, BUTTON_HEIGHT).contains(Mouse::getPosition(window))) { menu1.setColor(Color(200,90,90)); menuNum = 1; }
		if (IntRect(MENU_X, EXIT_Y, BUTTON_WIDTH, BUTTON_HEIGHT).contains(Mouse::getPosition(window))) { menu2.setColor(Color(200, 90, 90)); menuNum = 2; }
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
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.close(); isMenu = false; }

		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
	music_menu.stop();
}

