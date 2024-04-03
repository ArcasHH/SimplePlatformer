#pragma once

#include <SFML\Graphics.hpp>
#include "Constants.h"
#include <iostream>
#include <fstream>
#include <string> 


class Map {
public:
	std::string file;
	sf::String map[HEIGHT_MAP];

	sf::Image map_image;
	sf::Texture map_texture;
	sf::Sprite s_map;

	Map(std::string f) {
		file = "map/" + f;
		std::ifstream in(file);
		if (in.is_open()){
			std::string line;
			for (int i = 0; i < HEIGHT_MAP; ++i) {
				std::getline(in, line);
				map[i] = line;
			}
		}
		in.close();

		map_image.loadFromFile("images/map.png");
		map_texture.loadFromImage(map_image);
		s_map.setTexture(map_texture);
	}
	void renderMap(sf::RenderWindow& window) {
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (map[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
				if (map[i][j] == 'X')  s_map.setTextureRect(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((map[i][j] == '0')) s_map.setTextureRect(sf::IntRect(2 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				if ((map[i][j] == 'W')) s_map.setTextureRect(sf::IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
				s_map.setPosition(static_cast<float>(j * TILE_SIZE), static_cast<float>(i * TILE_SIZE));
				window.draw(s_map);
			}
	}
};

