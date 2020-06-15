#include "GameEngine.h"
#include "GameState.h"

#include "MenuState.h"
#include "PlayingState.h"
#include "VictoryState.h"
#include "LevelState.h"
#include "PauseState.h"
#include "OptionsState.h"
#include "InstructionsState.h"

#include <iostream>

GameEngine::GameEngine() : m_width(640), m_height(800), m_window(sf::VideoMode(m_width, m_height), "Nine Men's Morris", sf::Style::Titlebar | sf::Style::Close, m_settings), m_exit(false),
					m_context(this, &m_textureHolder, &m_fontHolder, &m_audioManager)
{
	m_settings.antialiasingLevel = 4;

	// Spremi u mapu funkcije koje ce kreirati state i vratiti ga za pohranu u State stack
	registerState<MenuState>(StateNames::MAINMENU);
	registerState<PlayingState>(StateNames::GAME);
	registerState<VictoryState>(StateNames::VICTORY);
	registerState<LevelState>(StateNames::LEVEL);
	registerState<PauseState>(StateNames::PAUSE);
	registerState<OptionsState>(StateNames::OPTIONS);
	registerState<InstructionsState>(StateNames::INSTRUCTIONS);

	// Postavi Main menu kao početni state
	changeState(m_stateRegister[StateNames::MAINMENU]());

	m_window.setFramerateLimit(60);
}

GameEngine::~GameEngine() {
	delete Globals::levelSelected;
	Globals::levelSelected = nullptr;
}

void GameEngine::run() {
	while(isRunning()) {
		pendingActions();

		input();
		update();
		render();
	}

	quit();
}

void GameEngine::quit() {
	while (!m_statesStack.empty()) {
		popState();
	}
}

void GameEngine::render() {
	m_window.clear();

	// Renderaj stateove dok jedan od njih ne vrati false
	for (auto state_it = m_statesStack.begin(); state_it != m_statesStack.end(); ++state_it) {
		if (!(*state_it)->render()) {
			break;
		}
	}

	m_window.display();
}

void GameEngine::update() {
	// Updateaj stateove dok jedan od njih ne vrati false
	for (auto state_it = m_statesStack.rbegin(); state_it != m_statesStack.rend(); ++state_it) {
		if (!(*state_it)->update()) {
			break;
		}
	}
}

void GameEngine::input() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			this->closeWindow();
		
		for (auto state_it = m_statesStack.rbegin(); state_it != m_statesStack.rend(); ++state_it) {
			if (!(*state_it)->input(event)) {
				break;
			}
		}
	}
}

bool GameEngine::isRunning() {
	return !m_exit;
}

void GameEngine::closeWindow() {
	m_exit = true;
}

sf::RenderWindow* GameEngine::getWindow() {
	return &m_window;
}

void GameEngine::changeState(GameState* state, bool quit, std::vector<std::function<void()>> exec) {
	// Ako je postavljena zastavica onda ugasi sve prijašnje kreirane stateove
	if(quit == true && !m_statesStack.empty()) {
		popState();
	}

	m_statesStack.push_back(state);

	for (auto func : exec) {
		func();
	}
}

void GameEngine::pendingActions() {
	pendingClearState();
	pendingStates();
	pendingReturn();
}

void GameEngine::queueState(StateNames stateName, bool quit, std::vector<std::function<void()>> exec) {
	m_pendingStates.insert(m_pendingStates.begin(), { m_stateRegister[stateName](), {quit, exec} });
}

void GameEngine::queueClearStates() {
	m_pendingClear = true;
}

void GameEngine::queueReturn() {
	m_pendingReturn = true;
}

void GameEngine::pendingStates() {
	// Procesiraj zahtjeve za kreiranje novog statea
	while(!m_pendingStates.empty()) {
		changeState(m_pendingStates.back().first, m_pendingStates.back().second.first, m_pendingStates.back().second.second);
		m_pendingStates.pop_back();
	}
}

void GameEngine::pendingClearState() {
	// Ugasi sve stateove
	if (m_pendingClear) {
		quit();
		m_pendingClear = false;
	}
}

void GameEngine::pendingReturn() {
	// Ugasi state na vrhu stacka
	if (m_pendingReturn) {
		popState();
		m_pendingReturn = false;
	}
}

void GameEngine::popState() {
	delete m_statesStack.back();

	m_statesStack.pop_back();
}