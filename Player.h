#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> 
#include <sstream>
#include "Constants.h"
#include "map.h"

using namespace sf;

int lvl = 1;
class Player {
public:
	float w, h, dx, dy, speed;
	float x, y;
	bool life, win, isMove, onGround;
	enum { left, right, up, down, jump, stay } state;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H) {

		speed = 0, dx = 0, dy = 0;
		life = true, win = false, isMove = false, onGround = false;
		File = F;
		w = W;
		h = H;
		image.loadFromFile("images/" + File);
		//image.createMaskFromColor();
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		x = X;
		y = Y;
		sprite.setTextureRect(IntRect(0, 134, w, h));
		sprite.setOrigin(w / 2, h / 2);
	}
	void control() {
		if ((Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A))) {
			state = left;
			speed = PLAYER_SPEED;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D))) {
			state = right;
			speed = PLAYER_SPEED;
		}
#if 0
		if (((Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::Space))) && (onGround)) {
			state = jump; dy = JUMP; onGround = false;//ïðûãàåò íà ïðîáåë
		}
#else
		if (onGround) {
			state = jump; dy = JUMP; onGround = false; //ïîñòîÿííî ïðûãàåò
		}
#endif
	}
	void update(float time, const sf::String Map[HEIGHT_MAP])
	{
		control();
		switch (state)
		{
			case right: dx = speed; break;
			case left: dx = -speed; break;
			case jump: break;
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
		for (int i = y / TILE_SIZE; i < (y + h) / TILE_SIZE; i++)
			for (int j = x / TILE_SIZE; j < (x + w) / TILE_SIZE; j++)
			{
				if (Map[i][j] == '0')//ÑÒÎËÊÍÎÂÅÍÈß Ñ ÏËÀÒÔÎÐÌÀÌÈ
				{
					if (Dy > 0) { y = i * TILE_SIZE - h;  dy = 0; onGround = true; }
					if (Dy < 0) { y = i * TILE_SIZE + TILE_SIZE;  dy = 0; }
					if (Dx > 0) { x = j * TILE_SIZE - w; }
					if (Dx < 0) { x = j * TILE_SIZE + TILE_SIZE; }
				}
				if (Map[i][j] == 'X')//ÑÌÅÐÒÜ
				{
					life = false;
				}
				if (Map[i][j] == 'W')//ÏÎÁÅÄÀ
				{
					win = true;
				}
			}
	}
};