#pragma once
#include "GameState.h"
#include "Level.h"
#include "EnumsBoard.h"

class Context;
class Board;

class PlayingState : public GameState {
public:
	PlayingState(Context* context);
	~PlayingState();

	bool render() override;
	bool update() override;

	void setBoardLevel(Level* level);
	void setTransparency(float value);

private:
	Board* m_board;
	sf::Text m_playerLabel;
	sf::Text m_currentPlayerLabel;
	sf::Text m_phaseLabel;
	sf::Text m_currentStateInstructionLabel;

	sf::RectangleShape m_overlay;
	float m_overlayTransparency;

	std::map<Turn, std::string> m_playerNames;
	std::map<State, std::string> m_phaseNames;
};

