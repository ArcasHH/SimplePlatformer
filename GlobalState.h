#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>


class BaseWindow;
class GlobalState;

GlobalState& getGlobalState();

namespace sf {
	class Music;
};

using Musics = std::vector<sf::Music*>;
class GlobalState
{
	std::unordered_map<std::string, BaseWindow*> AllWindows{ std::make_pair<std::string, BaseWindow*>("exit", nullptr) };

	BaseWindow* CurrWindow = nullptr;

	Musics MusicVector;

public:
	template <typename WinTy>
	void addWindow(std::string Name) {
		AllWindows.emplace(std::move(Name), new WinTy{});
	}

	void setCurrWindow(std::string Name) {
		CurrWindow = getWindow(std::move(Name));
	}
	
	void recordMusic(sf::Music* Music);
	const Musics& getMusics() const;
	
	BaseWindow* getCurrWindow() const {
		return CurrWindow;
	}

	BaseWindow* getWindow(std::string Name) {
		auto FindIt = AllWindows.find(Name);
		if (FindIt == AllWindows.end())
			throw std::runtime_error{ Name + " <- has not been added" };
		return FindIt->second;
	}
};

