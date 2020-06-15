#include "OptionsState.h"
#include "Button.h"
#include "Context.h"
#include "GameEngine.h"

OptionsState::OptionsState(Context* context) : GameState(context) {
	m_background.setPosition(sf::Vector2f(160.f, 140.f));
	m_background.setSize(sf::Vector2f(320.f, 360.f));
	m_background.setFillColor(sf::Color(0, 0, 128, 240));

	m_backgroundLabel.setString("Background");
	m_backgroundLabel.setCharacterSize(36);
	m_backgroundLabel.setPosition(200, 200);

	Button* returnButton = new Button(context, 195.f, 380.f, 250.f, 80.f, "Return");
	returnButton->setOnClick([context]() { context->gameEngine->queueReturn(); });

	toggleBackground = new Button(context, 195.f, 180.f, 250.f, 80.f, "Background: ON");
	toggleBackground->setOnClick([context]() { context->audioManager->toggleBackgroundMusic(); });

	toggleSounds = new Button(context, 195.f, 280.f, 250.f, 80.f, "Sounds: ON");
	toggleSounds->setOnClick([context]() { context->audioManager->toggleSounds(); });

	m_objects.push_back(returnButton);
	m_objects.push_back(toggleBackground);
	m_objects.push_back(toggleSounds);
}

bool OptionsState::update() {
	GameState::update();

	toggleBackground->setLabel(m_context->audioManager->backgroundMusicMuted() ? "Background: OFF" : "Background: ON");
	toggleSounds->setLabel(m_context->audioManager->soundsMuted() ? "Sounds: OFF" : "Sounds: ON");

	return false;
}

bool OptionsState::render() {
	sf::RenderWindow* window = m_context->gameEngine->getWindow();
	
	window->draw(m_background);

	GameState::render();

	return true;
}
