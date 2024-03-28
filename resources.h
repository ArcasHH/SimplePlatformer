#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::Image map_image;
sf::Texture map;
sf::Sprite s_map;


sf::Music die_music;
sf::Music music;
sf::Music music_menu;
sf::SoundBuffer jump_buffer;
sf::Sound jump_sound;


sf::Font font;
void getFont(sf::Font &font) {
	font.loadFromFile("nyashasans.ttf");
}
sf::Text text("", font, TEXT_SIZE);
sf::Text die_text("YOU DIED", font, BIG_TEXT_SIZE);
sf::Text win_text("YOU WIN", font, BIG_TEXT_SIZE);
sf::Text restart_text("press R to exit menu", font, BIG_TEXT_SIZE);