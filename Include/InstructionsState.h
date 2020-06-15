#pragma once
#include "GameState.h"
#include "Context.h"

class InstructionsState : public GameState {
public:
	InstructionsState(Context* context);
	~InstructionsState();

	bool render() override;

private:
	sf::RectangleShape m_background;

	sf::Text m_howToPlayLabel;
	std::vector<sf::Text*> m_instructionsLabels;
};

