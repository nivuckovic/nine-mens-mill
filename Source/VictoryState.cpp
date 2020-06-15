#include "VictoryState.h"
#include "SFML/Graphics.hpp"
#include "GameEngine.h"
#include <iostream>
#include "Button.h"

VictoryState::VictoryState(Context* context) : GameState(context), m_overlayTransparency(50){
	m_overlay.setFillColor(sf::Color(0, 0, 0, m_overlayTransparency));
	m_overlay.setPosition(0, 0);
	m_overlay.setSize((sf::Vector2f)context->gameEngine->getWindow()->getSize());

	m_messageWindow.setSize(sf::Vector2f(480.f, 480.f));
	m_messageWindow.setPosition(sf::Vector2f(80.f, 80.f));
	m_messageWindow.setFillColor(sf::Color::White);

	m_victoryLabel.setString("VICTORY");
	m_victoryLabel.setCharacterSize(96);
	m_victoryLabel.setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	m_victoryLabel.setPosition((context->gameEngine->getWindow()->getSize().x - m_victoryLabel.getGlobalBounds().width) / 2, 160);

	m_playerLabel.setString((bool)Globals::victor ? "Blue won" : "Red won");	
	m_playerLabel.setFillColor(Globals::playerColors[Globals::victor]);
	m_playerLabel.setCharacterSize(64);
	m_playerLabel.setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	m_playerLabel.setPosition((context->gameEngine->getWindow()->getSize().x - m_playerLabel.getGlobalBounds().width) / 2, 240);

	Button* returnMainMenu = new Button(m_context, 195.f, 380.f, 250.f, 80.f, "Main menu");
	returnMainMenu->setOnClick([context]() {context->gameEngine->queueClearStates(); context->gameEngine->queueState(StateNames::MAINMENU); });
	m_objects.push_back(returnMainMenu);
}

bool VictoryState::update() {
	if (m_overlayTransparency < 200.f) {
		m_overlayTransparency += 8.f;
		m_overlay.setFillColor(sf::Color(0, 0, 0, m_overlayTransparency));
	}
	else {
		m_showMessage = true;
		GameState::update();
	}

	return true;
}

bool VictoryState::render() {
	sf::RenderWindow* m_window = m_context->gameEngine->getWindow();

	m_window->draw(m_overlay);

	if (m_showMessage) {
		// m_window->draw(m_messageWindow);
		GameState::render();
		
	}

	m_window->draw(m_playerLabel);
	m_window->draw(m_victoryLabel);

	return false;
}
