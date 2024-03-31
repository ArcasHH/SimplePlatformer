#pragma once
#include "Constants.h"
#include "view.h"
#include "resources.h"
#include "Player.h"
#include "menu.h"
//#include "loops.h"
using namespace sf;


void die_screen(RenderWindow& window) {

	view.setCenter(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2);
	window.setView(view);

	PushButton restart_button("restart.png", view.getCenter().x-300, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton menu_button("menu.png", view.getCenter().x - 100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	PushButton exit_button("exit.png", view.getCenter().x +100, view.getCenter().y, LVL_NUM_SIZE, LVL_NUM_SIZE, Color::White, Color::Red);
	bool isDieScreen = true;

	while (isDieScreen)
	{
		window.clear(Color::Black);

		if (die_music.getStatus() == SoundSource::Status::Stopped) {
			die_music.play();//Ã”«€ ¿ œ–» —Ã≈–“»
			music.pause();
		}

		die_text.setPosition(view.getCenter().x - 150, view.getCenter().y - 100);
		window.draw(die_text);

		restart_button.paint_button(window);
		menu_button.paint_button(window);
		exit_button.paint_button(window);

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
			if (restart_button.is_pos(window)) {
				//restart.is_clicked = true;
				isDieScreen = false;
				//if (lvl == 1) { StartGame(window, Map1); }
				//if (lvl == 2) { StartGame(window, Map2); }
				//if (lvl == 3) { StartGame(window, Map3); }
			}

			if (menu_button.is_pos(window)) {
				die_music.stop();
				music.stop();
				menu(window);
			}
			if (exit_button.is_pos(window)) {
				window.close();
				music_menu.stop();
				return;
			}

		}
		window.draw(restart_button.sprite);
		window.draw(menu_button.sprite);
		window.draw(exit_button.sprite);
		window.display();
	}
	music_menu.stop();
}