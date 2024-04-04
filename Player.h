#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <sstream>
#include "Constants.h"
#include "map.h"

int lvl = 1;


class Player {
public:
	float w, h, dx, dy, speed;
	float x, y;
	bool life, win, isMove, onGround;
	enum { left, right, up, down, jump, stay } state;
	sf::String File_left, File_right;
	sf::Image image_left, image_right;
	sf::Texture texture_left;
	sf::Texture texture_right;
	sf::Sprite sprite;
	Player(sf::String F_left, sf::String F_right, float X, float Y, float W, float H) {
		state = stay;
		speed = 0, dx = 0, dy = 0;
		life = true, win = false, isMove = false, onGround = false;
		w = W;
		h = H;
		File_left = F_left;
		image_left.loadFromFile("images/" + File_left);
		texture_left.loadFromImage(image_left);
		//sprite.setTexture(texture_left);
		File_right = F_right;
		image_right.loadFromFile("images/" + File_right);
		texture_right.loadFromImage(image_right);
		sprite.setTexture(texture_right);

		x = X;
		y = Y;
		sprite.setTextureRect(sf::IntRect(0, 0, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}
	void restart(float X, float Y, float W, float H) {
		speed = 0, dx = 0, dy = 0;
		state = stay;
		life = true, win = false, isMove = false, onGround = false;
		w = W;
		h = H;
		x = X;
		y = Y;
		sprite.setOrigin(w / 2, h / 2);

	}
	void control() {
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
			state = left;
			speed = PLAYER_SPEED;
			sprite.setTexture(texture_left);

		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
			state = right;
			speed = PLAYER_SPEED;
			sprite.setTexture(texture_right);
		}
#if 0
		if (((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::Space))) && (onGround)) {
			state = jump; dy = JUMP; onGround = false;//прыгает на пробел
		}
#else
		if (onGround) {
			state = jump; dy = JUMP; onGround = false; //постоянно прыгает
		}
#endif
	}
	void update(float time, const sf::String Map[HEIGHT_MAP])
	{
		control();
		switch (state){
			case right: dx = speed; break;
			case left: dx = -speed; break;
			case jump: break;
			case stay: dx = 0; dy = 0; break;
		}

		x += dx * time;
		checkCollisionWithMap(dx, 0, Map);
		y += dy * time;
		checkCollisionWithMap(0, dy, Map);
		if (!isMove) { speed = 0; }
		sprite.setPosition(x + w / 2, y + h / 2);
		dy = dy + GRAVITATION * time;
	}

	float getplayercoordinateX() {
		return x;
	}
	float getplayercoordinateY() {
		return y;
	}

	void checkCollisionWithMap(float Dx, float Dy, const sf::String Map[HEIGHT_MAP])
	{
		int sw = 32; // сужение спрайта при столкновениях по горизонтали
		int sh = 16; // сужение спрайта при столкновениях по вертикали (только сверху)
		for (int i = (y + sh) / TILE_SIZE; i < (y + h ) / TILE_SIZE; i++)
			for (int j = (x + sw) / TILE_SIZE; j < (x + w - sw) / TILE_SIZE; j++)
			{
				if (Map[i][j] == '0')//СТОЛКНОВЕНИЯ С ПЛАТФОРМАМИ
				{
					if (Dy > 0) { y = i * TILE_SIZE - h ;  dy = 0; onGround = true; }
					if (Dy < 0) { y = i * TILE_SIZE + TILE_SIZE - sh ;  dy = 0; }
					if (Dx > 0) { x = j * TILE_SIZE - w + sw; }
					if (Dx < 0) { x = j * TILE_SIZE + TILE_SIZE - sw; }
				}
				if (Map[i][j] == 'X')//СМЕРТЬ
				{
					life = false;
				}
				if (Map[i][j] == 'W')//ПОБЕДА
				{
					win = true;
				}
			}
	}
};