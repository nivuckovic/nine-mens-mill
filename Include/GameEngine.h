#pragma once

#include <vector>
#include <vector>
#include <functional>
#include "SFML/Graphics.hpp"
#include "ResourceHolder.h"
#include "Context.h"
#include "AudioManager.h"
#include "Globals.h"

class GameState;

enum class StateNames {
	MAINMENU,
	GAME,
	VICTORY,
	LEVEL,
	PAUSE,
	OPTIONS,
	INSTRUCTIONS,
	LENGTH
};

class GameEngine {
public:
	GameEngine();
	~GameEngine();

	void run();

	void queueState(StateNames stateName, bool quit = true, std::vector<std::function<void()>> exec = { []() {} });
	void queueClearStates();
	void queueReturn();

	void input();
	void update();
	void render();

	bool isRunning();
	void closeWindow();

	sf::RenderWindow* getWindow();
private:
	template <typename T>
	void registerState(StateNames stateName);
	void changeState(GameState* state, bool quit = true, std::vector<std::function<void()>> exec = { []() {} });
	void pendingActions();
	void pendingStates();
	void pendingClearState();
	void pendingReturn();
	void popState();

	void quit();

private:
	int m_width, m_height;
	sf::RenderWindow m_window;
	sf::ContextSettings m_settings;

	std::map<StateNames, std::function<GameState * ()>> m_stateRegister;
	std::vector<GameState*> m_statesStack;
	
	std::vector<std::pair<GameState*, std::pair<bool, std::vector<std::function<void()>>>>> m_pendingStates;
	bool m_pendingClear;
	bool m_pendingReturn;

	Context m_context;

	TextureHolder m_textureHolder;
	FontHolder m_fontHolder;
	AudioManager m_audioManager;

	bool m_exit;
};

template <typename T>
void GameEngine::registerState(StateNames stateName) {
	m_stateRegister[stateName] = [this]() { return new T(&this->m_context); };
}