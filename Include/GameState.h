#pragma once

#include <vector>
#include "SFML/Graphics.hpp"

class Context;
class GameObject;

class GameState {
public:
	GameState(Context* context);
	virtual ~GameState() {};

	virtual bool render();
	virtual bool input(sf::Event& e);
	virtual bool update();

protected:
	std::vector<GameObject*> m_objects;
	Context* m_context;


};

