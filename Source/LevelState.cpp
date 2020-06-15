#include "LevelState.h"
#include "GameEngine.h"
#include "Button.h"
#include "Globals.h"

#include <iostream>

LevelState::LevelState(Context* context) : GameState(context) {
	// Ovdje definiramo levele, za novi level samo treba napraviti novi objekt klase Level i dodati ga u m_levels spremnik
	Level* m_standard = new Level();
	m_standard->numberOfNodes = 24;
	m_standard->nodesToPlace = 9;
	m_standard->adjacentNodes = {
		{-1, -1, 1, -1, 9, -1, -1, -1},
		{-1, -1, 2, -1, 4, -1, 0, -1},
		{-1, -1, -1, -1, 14, -1, 1, -1},
		{-1, -1, 4, -1, 10, -1, -1, -1},
		{1, -1, 5, -1, 7, -1, 3, -1},
		{-1, -1, -1, -1, 13, -1, 4, -1},
		{-1, -1, 7, -1, 11, -1, -1, -1},
		{4, -1, 8, -1, -1, -1, 6, -1},
		{-1, -1, -1, -1, 12, -1, 7, -1},
		{0, -1, 10, -1, 21, -1, -1, -1},
		{3, -1, 11, -1, 18, -1, 9, -1},
		{6, -1, -1, -1, 15, -1, 10, -1},
		{8, -1, 13, -1, 17, -1, -1, -1},
		{5, -1, 14, -1, 20, -1, 12, -1},
		{2, -1, -1, -1, 23, -1, 13, -1},
		{11, -1, 16, -1, -1, -1, -1, -1},
		{-1, -1, 17, -1, 19, -1, 15, -1},
		{12, -1, -1, -1, -1, -1, 16, -1},
		{10, -1, 19, -1, -1, -1, -1, -1},
		{16, -1, 20, -1, 22, -1, 18, -1},
		{13, -1, -1, -1, -1, -1, 19, -1},
		{9, -1, 22, -1, -1, -1, -1, -1},
		{19, -1, 23, -1, -1, -1, 21, -1},
		{14, -1, -1, -1, -1, -1, 22, -1},
	};
	m_standard->nodesCoordinates = {
		{80.f, 80.f},
		{320.f, 80.f},
		{560.f, 80.f},
		{160.f, 160.f},
		{320.f, 160.f},
		{480.f, 160.f},
		{240.f, 240.f},
		{320.f, 240.f},
		{400.f, 240.f},
		{80.f, 320.f},
		{160.f, 320.f},
		{240.f, 320.f},
		{400.f, 320.f},
		{480.f, 320.f},
		{560.f, 320.f},
		{240.f, 400.f},
		{320.f, 400.f},
		{400.f, 400.f},
		{160.f, 480.f},
		{320.f, 480.f},
		{480.f, 480.f},
		{80.f, 560.f},
		{320.f, 560.f},
		{560.f, 560.f},
	};
	m_standard->icon = Resources::TEXTURE_STANDARD;
	m_standard->name = "Standard";

	m_levels.push_back(m_standard);
	
	Level* m_morabaraba = new Level();
	m_morabaraba->numberOfNodes = 24;
	m_morabaraba->nodesToPlace = 9;
	m_morabaraba->adjacentNodes = {
		{-1, -1, 1, 3, 9, -1, -1, -1},
		{-1, -1, 2, -1, 4, -1, 0, -1},
		{-1, -1, -1, -1, 14, 5, 1, -1},
		{-1, -1, 4, 6, 10, -1, -1, 0},
		{1, -1, 5, -1, 7, -1, 3, -1},
		{-1, 2, -1, -1, 13, 8, 4, -1},
		{-1, -1, 7, -1, 11, -1, -1, 3},
		{4, -1, 8, -1, -1, -1, 6, -1},
		{-1, 5, -1, -1, 12, -1, 7, -1},
		{0, -1, 10, -1, 21, -1, -1, -1},
		{3, -1, 11, -1, 18, -1, 9, -1},
		{6, -1, -1, -1, 15, -1, 10, -1},
		{8, -1, 13, -1, 17, -1, -1, -1},
		{5, -1, 14, -1, 20, -1, 12, -1},
		{2, -1, -1, -1, 23, -1, 13, -1},
		{11, -1, 16, -1, -1, 18, -1, -1},
		{-1, -1, 17, -1, 19, -1, 15, -1},
		{12, -1, -1, 20, -1, -1, 16, -1},
		{10, 15, 19, -1, -1, 21, -1, -1},
		{16, -1, 20, -1, 22, -1, 18, -1},
		{13, -1, -1, 23, -1, -1, 19, 17},
		{9, 18, 22, -1, -1, -1, -1, -1},
		{19, -1, 23, -1, -1, -1, 21, -1},
		{14, -1, -1, -1, -1, -1, 22, 20},
	};
	m_morabaraba->nodesCoordinates = {
		{80.f, 80.f},
		{320.f, 80.f},
		{560.f, 80.f},
		{160.f, 160.f},
		{320.f, 160.f},
		{480.f, 160.f},
		{240.f, 240.f},
		{320.f, 240.f},
		{400.f, 240.f},
		{80.f, 320.f},
		{160.f, 320.f},
		{240.f, 320.f},
		{400.f, 320.f},
		{480.f, 320.f},
		{560.f, 320.f},
		{240.f, 400.f},
		{320.f, 400.f},
		{400.f, 400.f},
		{160.f, 480.f},
		{320.f, 480.f},
		{480.f, 480.f},
		{80.f, 560.f},
		{320.f, 560.f},
		{560.f, 560.f},
	};
	m_morabaraba->icon = Resources::TEXTURE_MORABARABA;
	m_morabaraba->name = "Morabaraba";

	m_levels.push_back(m_morabaraba);

	// Za novi level također treba dodati preview thumbnail za level
	float offset = 120.f;
	for (int i = 0; i < m_levels.size(); ++i) {
		Button* levelButton = new Button(context, 180.f, offset, 200, 80, m_levels[i]->name);
		levelButton->setOnClick([context, i, this]() { Globals::levelSelected = m_levels[i]; context->gameEngine->queueState(StateNames::GAME); context->gameEngine->queueState(StateNames::INSTRUCTIONS, false); });

		sf::Sprite* levelIcon = new sf::Sprite();
		levelIcon->setTexture(context->textureHolder->getResource(m_levels[i]->icon));
		levelIcon->setPosition(400.f, offset);

		m_objects.push_back(levelButton);
		m_levelIcon.push_back(levelIcon);
		
		offset = offset + 80.f + 20.f;
	}

	Button* mainMenuButton = new Button(context, 180.f, offset, 320, 80, "Main menu");
	mainMenuButton->setOnClick([context]() { context->gameEngine->queueState(StateNames::MAINMENU); });

	m_objects.push_back(mainMenuButton);
}

LevelState::~LevelState() {
	for (int i = 0; i < m_levels.size(); ++i) {
		if (m_levels[i] != Globals::levelSelected) {
			delete m_levels[i];
			m_levels[i] = nullptr;
		}

		delete m_levelIcon[i];
	}
}

bool LevelState::render() {
	GameState::render();

	for (int i = 0; i < m_levelIcon.size(); ++i)
		m_context->gameEngine->getWindow()->draw(*m_levelIcon[i]);

	return false;
}
