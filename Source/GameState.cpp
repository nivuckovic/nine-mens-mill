#include "GameState.h"
#include "GameObject.h"

GameState::GameState(Context* context) : m_context(context) {

}

bool GameState::render() {
	for (auto object : m_objects)
		object->render();

	return false;
}

bool GameState::input(sf::Event& e) {
	for (auto object : m_objects)
		object->input(e);

	return false;
}

bool GameState::update() {
	for (auto object : m_objects)
		object->update();

	return false;
}

