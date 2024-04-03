#pragma once
#include "Constants.h"
#include "view.h"
#include "resources.h"
#include "Player.h"
#include "map.h"


sf::Clock gameClock; //‚ÂÏˇ Ë„˚
bool isMenu = false, isGame = false, isDie = false, isWin = false, isExit = false;

void StartGame(sf::RenderWindow& window, Map play_map, Player& p) {
	window.setView(view);
	play_map.renderMap(window);//Œ“–»—Œ¬ ¿  ¿–“€
	
	float time = static_cast<float>(gameClock.getElapsedTime().asMicroseconds());
	gameClock.restart();
	time = time / TIME_SCALE;
	
	p.update(time, play_map.map);

	if (p.life) {//◊“Œ ƒ≈À¿“‹ œŒ ¿ ∆»¬€
		getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
		window.draw(p.sprite);
	}
	if (p.win) { //◊“Œ œ–Œ»—’Œƒ»“ œ–» œŒ¡≈ƒ≈
		isGame = false;
		isWin = true;
		return;
	}
	else if (!p.life) { // ◊“Œ œ–Œ»—’Œƒ»“ œ–» —Ã≈–“»///
		isGame = false; 
		isDie = true;
		return;
	}
}

void dieScreen(sf::RenderWindow& window, PushButton& restart_button, PushButton& menu_button, PushButton& exit_button) {
		
	restart_button.paint_button(window);
	menu_button.paint_button(window);
	exit_button.paint_button(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (restart_button.is_pos(window)) {
			isDie = false;
			isGame = true;
			return;
		}
		if (menu_button.is_pos(window)) {
			isDie = false;
			isMenu = true;	
			return;
		}
		if (exit_button.is_pos(window)) {
			isExit = true;
		}
	}
	window.draw(die_text);
	window.draw(restart_button.sprite);
	window.draw(menu_button.sprite);
	window.draw(exit_button.sprite);
}

void winScreen(sf::RenderWindow& window, PushButton& next_button, PushButton& menu_button, PushButton& exit_button) {

	next_button.paint_button(window);
	menu_button.paint_button(window);
	exit_button.paint_button(window);
	dancing_dragon.draw_anim();
	window.draw(win_text);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (next_button.is_pos(window)) {
			if (lvl == 1) {
				lvl = 2;
				isWin = false;
				isGame = true;
				return;
			}
			else if (lvl == 2) {
				lvl = 3;
				isWin = false;
				isGame = true;
				return;
			}
			else if (lvl == 3) {
				lvl = 1;
				isWin = false;
				isGame = true;
				return;
			}
		}
		if (menu_button.is_pos(window)) {
			isWin = false;
			isMenu = true;
			return;
		}
		if (exit_button.is_pos(window)) {
			isExit = true;
			return;
		}
	}
	window.draw(dancing_dragon.sprite);
	window.draw(next_button.sprite);
	window.draw(menu_button.sprite);
	window.draw(exit_button.sprite);
	
}


void menuScreen(sf::RenderWindow& window, BackgroundImage& bg, PushButton& NewGame_button, PushButton& Exit_button, PushButton& num1, PushButton& num2, PushButton& num3) {

		NewGame_button.paint_button(window);
		Exit_button.paint_button(window);
		num1.paint_button(window);
		num2.paint_button(window);
		num3.paint_button(window);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
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

		if (NewGame_button.is_pos(window)) {
			num1.is_clicked = false;
			num2.is_clicked = false;
			num3.is_clicked = false;
			isMenu = false;
			isGame = true;
			return;
		}
		if (Exit_button.is_pos(window)) {
			isExit = true;
			return;
		}
	}
	window.draw(bg.sprite);
	window.draw(NewGame_button.sprite);
	window.draw(Exit_button.sprite);
	window.draw(num1.sprite);
	window.draw(num2.sprite);
	window.draw(num3.sprite);
}