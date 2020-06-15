#pragma once
#include "GameState.h"
#include "Context.h"

class PauseState : public GameState {
public:
	PauseState(Context* context);

	bool update() override;
	bool render() override;

private:
	sf::RectangleShape m_overlay;
	float m_overlayTransparency;
	
	sf::Text m_gamePausedLabel;

	bool m_showContent;
};

