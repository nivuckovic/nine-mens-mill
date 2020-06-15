#pragma once
#include "GameState.h"

class Button;

class OptionsState : public GameState {
public:
	OptionsState(Context* context);

	bool update() override;
	bool render() override;
private:
	sf::RectangleShape m_background;

	Button* toggleBackground;
	Button* toggleSounds;

	sf::Text m_backgroundLabel;
	sf::Text m_soundsLabel;
};

