#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include <string>
#include "EnumResources.h"

struct Level {
	std::vector<std::vector<int>> adjacentNodes;
	std::vector < sf::Vector2f> nodesCoordinates;

	int numberOfNodes;
	int nodesToPlace;
	
	std::string name;
	Resources icon;
};
