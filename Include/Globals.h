#pragma once

#include "EnumsBoard.h"
#include <map>
#include "SFML/Graphics.hpp"
#include "Level.h"

namespace Globals {
	extern std::map<Turn, sf::Color> playerColors;
	extern std::map<State, std::string> stateInstructions;

	float distance(sf::Vector2f a, sf::Vector2f b);

	extern Level* levelSelected;
	extern Turn victor;
}


