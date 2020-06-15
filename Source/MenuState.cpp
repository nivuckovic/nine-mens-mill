#include "MenuState.h"

#include "SFML/Graphics.hpp"
#include "GameEngine.h"
#include "GameObject.h"
#include "Button.h"
#include "Context.h"

MenuState::MenuState(Context* context) : GameState(context) {
	Button* newGame = new Button(m_context, 195.f, 180.f, 250.f, 80.f, "New Game");
	newGame->setOnClick([context]() { context->gameEngine->queueState(StateNames::LEVEL); });

	Button* quitGame = new Button(m_context, 195.f, 380.f, 250.f, 80.f, "Exit");
	quitGame->setOnClick([context]() { context->gameEngine->closeWindow(); });

	Button* options = new Button(m_context, 195.f, 280.f, 250.f, 80.f, "Options");
	options->setOnClick([context]() { context->gameEngine->queueState(StateNames::OPTIONS, false); });

	m_objects.push_back(newGame);
	m_objects.push_back(options);
	m_objects.push_back(quitGame);

	context->audioManager->playBackgroundMusic();
}

MenuState::~MenuState() {
	while (!m_objects.empty()) {
		delete m_objects.back();
		m_objects.pop_back();
	}
}

bool MenuState::render() {
	GameState::render();

	return true;
}

bool MenuState::input(sf::Event& e) {
	GameState::input(e);


	return false;
}

bool MenuState::update() {
	GameState::update();

	return false;
}


