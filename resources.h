#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <sstream>
#include <string>



sf::Texture dragon;


sf::Font font;
sf::Text text("", font, TEXT_SIZE);
sf::Text die_text("YOU DIED", font, BIG_TEXT_SIZE);
sf::Text win_text("YOU WIN", font, BIG_TEXT_SIZE);


class MyMusic {
public:
	sf::Music music;
	sf::String file;
	int volume;
	bool is_loop;

	MyMusic(sf::String f, int v, bool loop) {
		file = f;
		volume = v;
		is_loop = loop;
		music.openFromFile("audio/" + file);
		music.setVolume(volume);
		music.setLoop(is_loop);	
	}
};

class MySound {
public:
	sf::String file;
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int volume;
	MySound(sf::String f, int v) {
		file = f;
		volume = v;
		buffer.loadFromFile("audio/" + file);
		sound.setBuffer(buffer);
		sound.setVolume(volume);
	}
};

class PushButton {
public:
	sf::String file;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Color base_color, clicked_color;
	int posX, posY, width, height;
	bool is_clicked;

	sf::SoundBuffer click_buffer;
	sf::Sound click_sound;
	bool is_sound;
	
	PushButton(sf::String f, int x, int y, int w, int h, sf::Color b_color, sf::Color c_color) {
		file = f;
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

	bool is_pos(sf::RenderWindow& window) {
		if (sf::IntRect(posX, posY, width, height).contains(sf::Mouse::getPosition(window))) {
			return true;
		}
		return false;
	}
	void paint_button(sf::RenderWindow& window) {
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
	sf::String file;
	sf::Texture texture;
	sf::Sprite sprite;
	int posX, posY;

	BackgroundImage(sf::String f, int x, int y) {
		file = f;
		posX = x, posY = y;
		texture.loadFromFile("images/" + file);
		sprite.setTexture(texture);
		sprite.setPosition(posX, posY);
	}
};

class Animation_frame {
public:
	sf::String file;
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
			else {
				frame = 0;
			}
			sprite.setTexture(textures[frame]);
			anim_clock.restart();
		}
	}
};

Animation_frame dancing_dragon(223, 700, 50);

class SpriteManager {
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	sf::String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(sf::String File, sf::String Name) {
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};