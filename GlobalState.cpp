#include "GlobalState.h"
GlobalState& getGlobalState() {
	static GlobalState G;
	return G;
}

void GlobalState::recordMusic(sf::Music *Music) {
	MusicVector.push_back(Music);
}

const Musics& GlobalState::getMusics() const {
	return MusicVector;
}