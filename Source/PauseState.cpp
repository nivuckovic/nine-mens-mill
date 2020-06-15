#include "PauseState.h"
#include "Button.h"
#include "GameEngine.h"


PauseState::PauseState(Context* context) : GameState(context), m_overlayTransparency(50) {
	m_overlay.setFillColor(sf::Color(0, 0, 0, m_overlayTransparency));
	m_overlay.setPosition(0, 0);
	m_overlay.setSize((sf::Vector2f)context->gameEngine->getWindow()->getSize());

	m_gamePausedLabel.setString("Game paused");
	m_gamePausedLabel.setCharacterSize(64);
	m_gamePausedLabel.setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	m_gamePausedLabel.setPosition((context->gameEngine->getWindow()->getSize().x - m_gamePausedLabel.getGlobalBounds().width) / 2, 240);

	Button* returnToMainMenu = new Button(context, m_gamePausedLabel.getGlobalBounds().left, m_gamePausedLabel.getGlobalBounds().top + m_gamePausedLabel.getGlobalBounds().height + 20.f, 220, 80, "Main Menu");
	returnToMainMenu->setOnClick([context]() { context->gameEngine->queueClearStates(); context->gameEngine->queueState(StateNames::MAINMENU); });

	Button* options = new Button(context, m_gamePausedLabel.getGlobalBounds().left + m_gamePausedLabel.getGlobalBounds().width - 220, returnToMainMenu->getPosition().y, 220, 80, "Options");
	options->setOnClick([context]() { context->gameEngine->queueState(StateNames::OPTIONS, false); });

	Button* restartGame = new Button(context, m_gamePausedLabel.getGlobalBounds().left, m_gamePausedLabel.getGlobalBounds().top + m_gamePausedLabel.getGlobalBounds().height + 120.f, 220, 80, "Restart game");
	restartGame->setOnClick([context]() { context->gameEngine->queueClearStates(); context->gameEngine->queueState(StateNames::GAME); });

	Button* returnToGame = new Button(context, m_gamePausedLabel.getGlobalBounds().left + m_gamePausedLabel.getGlobalBounds().width - 220, restartGame->getPosition().y, 220, 80, "Resume game");
	returnToGame->setOnClick([context]() { context->gameEngine->queueReturn();});

	m_objects.push_back(returnToGame);
	m_objects.push_back(returnToMainMenu);
	m_objects.push_back(restartGame);
	m_objects.push_back(options);
}

bool PauseState::update() {
	if (m_overlayTransparency < 200.f) {
		m_overlayTransparency += 8.f;
		m_overlay.setFillColor(sf::Color(0, 0, 0, m_overlayTransparency));
	}
	else {
		m_showContent = true;
		GameState::update();
	}

	return false;
}

bool PauseState::render() {
	sf::RenderWindow* m_window = m_context->gameEngine->getWindow();

	m_window->draw(m_overlay);

	if (m_showContent) {
		// m_window->draw(m_messageWindow);
		GameState::render();
		
		m_window->draw(m_gamePausedLabel);
	}

	return true;
}
