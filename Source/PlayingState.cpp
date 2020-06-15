#include "PlayingState.h"
#include "Context.h"
#include "EnumResources.h"
#include "GameEngine.h"
#include "Button.h"
#include "Board.h"
#include <iostream>

PlayingState::PlayingState(Context* context) : GameState(context), m_overlayTransparency(200.f) {
	m_board = new Board(context);
	m_objects.push_back(m_board);

	m_overlay.setFillColor(sf::Color(0, 0, 0, m_overlayTransparency));
	m_overlay.setPosition(0, 0);
	m_overlay.setSize((sf::Vector2f)context->gameEngine->getWindow()->getSize());

	Button* pauseButton = new Button(context, 470, 10, 160, 80, "Pause");
	pauseButton->setOnClick([context, this]() { context->gameEngine->queueState(StateNames::PAUSE, false); });

	m_objects.push_back(pauseButton);

	m_phaseNames = {
		{ State::MOVING, "Moving"},
		{ State::FLYING, "Flying"},
		{ State::MILL, "Mill"},
		{ State::PLACING, "Placing"},
	};

	m_playerNames = {
		{Turn::Player1, "Red"},
		{Turn::Player2, "Blue"}
	};

	m_playerLabel.setString("Turn: ");
	m_playerLabel.setCharacterSize(36);
	m_playerLabel.setFillColor(sf::Color::White);
	m_playerLabel.setPosition(10, -2);
	m_playerLabel.setFont(m_context->fontHolder->getResource(Resources::FONT_LASERCORPS));

	m_currentPlayerLabel.setCharacterSize(36);
	m_currentPlayerLabel.setPosition(m_playerLabel.getGlobalBounds().width + 20, -2);
	m_currentPlayerLabel.setFont(m_context->fontHolder->getResource(Resources::FONT_LASERCORPS));

	m_phaseLabel.setCharacterSize(36);
	m_phaseLabel.setFillColor(sf::Color::Yellow);
	m_phaseLabel.setPosition(pauseButton->getPosition().x - 250, -2);
	m_phaseLabel.setFont(m_context->fontHolder->getResource(Resources::FONT_LASERCORPS));

	m_currentStateInstructionLabel.setCharacterSize(24);
	m_currentStateInstructionLabel.setFillColor(sf::Color::White);
	m_currentStateInstructionLabel.setFont(m_context->fontHolder->getResource(Resources::FONT_LASERCORPS));

}

PlayingState::~PlayingState() {
}

bool PlayingState::render() {
	GameState::render();
	sf::RenderWindow* m_window = m_context->gameEngine->getWindow();

	m_window->draw(m_playerLabel);
	m_window->draw(m_phaseLabel);
	m_window->draw(m_currentPlayerLabel);
	m_window->draw(m_currentStateInstructionLabel);

	for (int j = 0; j < m_board->getPlayerInfo(Turn::Player1)->m_leftToPlace; ++j) {
		sf::CircleShape circle(15.f);
		circle.setOrigin(15.f, 15.f);
		circle.setPosition(sf::Vector2f(25.f + 35.f * j, m_window->getSize().y - 60 ));
		circle.setFillColor(Globals::playerColors[Turn::Player1]);

		m_window->draw(circle);
	}

	for (int j = m_board->getPlayerInfo(Turn::Player2)->m_leftToPlace; j > 0; --j) {
		sf::CircleShape circle(15.f);
		circle.setOrigin(15.f, 15.f);
		circle.setPosition(sf::Vector2f(m_window->getSize().x + 15.f - 35.f * j, m_window->getSize().y - 60 ));
		circle.setFillColor(Globals::playerColors[Turn::Player2]);

		m_window->draw(circle);
	}

	m_window->draw(m_overlay);

	return true;
}

bool PlayingState::update() {
	GameState::update();

	if (m_overlayTransparency > 0) {
		m_overlayTransparency -= 8.f;

		if (m_overlayTransparency < 0)
			m_overlayTransparency = 0;
		
		m_overlay.setFillColor(sf::Color(0, 0, 0, m_overlayTransparency));
	}

	m_currentPlayerLabel.setFillColor(Globals::playerColors[m_board->getPlayer()]);
	m_currentPlayerLabel.setString(m_playerNames[m_board->getPlayer()]);

	m_phaseLabel.setString(m_phaseNames[m_board->getCurrentPlayerInfo()->m_playerState]);
	m_phaseLabel.setPosition(m_currentPlayerLabel.getPosition().x + m_currentPlayerLabel.getGlobalBounds().width + 20.f, -2);

	m_currentStateInstructionLabel.setString(Globals::stateInstructions[m_board->getCurrentPlayerInfo()->m_playerState]);
	m_currentStateInstructionLabel.setPosition(m_playerLabel.getPosition().x, 54);

	return false;
}

void PlayingState::setBoardLevel(Level* level) {
	m_board->setLevel(level);
}

void PlayingState::setTransparency(float value) {
	m_overlayTransparency = value;
}
