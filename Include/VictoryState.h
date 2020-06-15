#pragma once
#include "GameState.h"
#include "Context.h"

class VictoryState : public GameState {
public:
	VictoryState(Context* context);

	bool render() override;
	bool update() override;
private:
	sf::RectangleShape m_messageWindow;
	sf::RectangleShape m_overlay;

	float m_overlayTransparency;
	
	sf::Text m_victoryLabel;
	sf::Text m_playerLabel;

	bool m_showMessage;
};

