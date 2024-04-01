#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <sstream>
#include <string>

sf::Image map_image;
sf::Texture map;
sf::Texture dragon;
sf::Sprite s_map;
sf::Texture menuTexture1, menuTexture2, menuBackground, num1, num2, num3;  //ТЕКСТУРКИ ДЛЯ МЕНЮ



class AllMusic {
public:
	sf::Music die;
	sf::Music win;
	sf::Music game;
	sf::Music menu;
	sf::SoundBuffer jump_buffer;
	sf::Sound jump_sound;
	
	int volume;
	bool is_loop;
	AllMusic() {
		is_loop = true;
		///////////////////МУЗЫКА
		die.openFromFile("audio/die.ogg");
		win.openFromFile("audio/dragon_dance.ogg");
		game.openFromFile("audio/yuka-kitamura-epilogue.ogg");
		menu.openFromFile("audio/Akira_Yamaoka_Never_Forgive_Me_Never_Forget_Me.ogg");
		//Громкость
		menu.setVolume(10);
		win.setVolume(10);
		//Зацикливание
		game.setLoop(is_loop);
		win.setLoop(is_loop);
		menu.setLoop(is_loop);
		

		///////////////////ЗВУКИ
		jump_buffer.loadFromFile("audio/jump.ogg");
		jump_sound.setBuffer(jump_buffer);
		
	}
	void not_loop() {
		game.setLoop(false);
		win.setLoop(false);
		menu.setLoop(false);
	}
};

sf::Font font;

sf::Text text("", font, TEXT_SIZE);
sf::Text die_text("YOU DIED", font, BIG_TEXT_SIZE);
sf::Text win_text("YOU WIN", font, BIG_TEXT_SIZE);

class PushButton {
public:
	String file;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Color base_color, clicked_color;
	int posX, posY, width, height;
	bool is_clicked;

	sf::SoundBuffer click_buffer;
	sf::Sound click_sound;
	bool is_sound;

	int shift_x, shift_y; //такого не должно быть. где-то ошибка, но спрайт не совпадает с текстуркой по X и без этого наведение идет со сдвигом// надо shift = 0
	
	PushButton(String f, int x, int y, int w, int h, sf::Color b_color, sf::Color c_color) {
		file = f;
		shift_x = 100, shift_y = -10;
		posX = x, posY = y;
		width = w, height = h;
		base_color = b_color, clicked_color = c_color;
		is_clicked = false;
		texture.loadFromFile("images/" + file);
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
		sprite.setColor(base_color);

		click_buffer.loadFromFile("audio/click.ogg");
		click_sound.setBuffer(click_buffer);
		click_sound.setVolume(10);
		is_sound = false;
	}

	bool is_pos(RenderWindow& window) {
		if (IntRect(posX+shift_x, posY+shift_y, width, height).contains(Mouse::getPosition(window))) {
			return true;
		}
		return false;
	}
	void paint_button(RenderWindow& window) {
		if (is_pos(window)){
			sprite.setColor(clicked_color);
			if (!is_sound) {
				click_sound.play();
				is_sound = true;
			}
		}
		else  {
			is_sound = false;
		}
		if (is_clicked) {
			sprite.setColor(clicked_color);
		}
		else if ((!is_clicked) && (!is_pos(window))) {
			sprite.setColor(base_color);
		}
			
	}

};
class BackgroundImage {
public:
	String file;
	sf::Texture texture;
	sf::Sprite sprite;
	int posX, posY;

	BackgroundImage(String f, int x, int y) {
		file = f;
		posX = x, posY = y;
		texture.loadFromFile("images/" + file);
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}
};
class Animation_frame {
public:
	String file;
	sf::Texture texture;
	sf::Sprite sprite;
	int posX, posY;
	sf::Clock anim_clock;
	int frame;
	std::vector<sf::Texture> textures;
	int num_frames;

	Animation_frame( int num, int x, int y) {
		num_frames = num;
		frame = 0;
		std::string s;
		for (int i = 0; i < num_frames+1; ++i) {
			s = std::to_string(i);
			file = s + "_sprite_dragon.png";
			texture.loadFromFile("images/background/sprite_dragon/" + file);
			textures.push_back(texture);
		}
		posX = x, posY = y;
		sprite.setTexture(textures[0]);
		sprite.setPosition(posX, posY);
		anim_clock.restart();
	}
	void draw_anim() {
		if (anim_clock.getElapsedTime().asSeconds() > SPEED_ANIM) {
			if (frame < num_frames) {
				++frame;
			}
			else { // заново
				frame = 0;
			}
			sprite.setTexture(textures[frame]);
			anim_clock.restart();
		}
	}
};
Animation_frame dancing_dragon(223, 600, 50);