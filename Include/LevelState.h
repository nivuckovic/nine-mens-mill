#pragma once
#include "GameState.h"
#include "Level.h"
#include "Context.h"

class LevelState : public GameState {
public:
	LevelState(Context* context);
	~LevelState();

	bool render() override;
private:
	std::vector<Level*> m_levels;
	std::vector<sf::Sprite*> m_levelIcon;
};

