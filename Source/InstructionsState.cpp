#include "InstructionsState.h"
#include "Button.h"
#include "GameEngine.h"

InstructionsState::InstructionsState(Context* context) : GameState(context) {
	m_background.setSize(sf::Vector2f(480.f, 640.f));
	m_background.setPosition(sf::Vector2f(80.f, 80.f));
	m_background.setFillColor(sf::Color(0, 0, 128, 240));

	m_howToPlayLabel.setString("HOW TO PLAY");
	m_howToPlayLabel.setCharacterSize(48);
	m_howToPlayLabel.setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	m_howToPlayLabel.setPosition(sf::Vector2f(80.f + (480.f - m_howToPlayLabel.getGlobalBounds().width) / 2, 100.f));

	sf::Text* instructionLabel1 = new sf::Text();
	instructionLabel1->setString("Place all your pieces on board\nand move them to form a line\nof 3 pieces (a mill).");
	instructionLabel1->setCharacterSize(24);
	instructionLabel1->setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	instructionLabel1->setPosition(sf::Vector2f(100.f, 180.f));

	sf::Text* instructionLabel2 = new sf::Text();
	instructionLabel2->setString("Once you form a mill, you can\nremove one of your\nopponent's pieces.");
	instructionLabel2->setCharacterSize(24);
	instructionLabel2->setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	instructionLabel2->setPosition(sf::Vector2f(100.f, 280.f));

	sf::Text* instructionLabel3 = new sf::Text();
	instructionLabel3->setString("Pieces from a formed mill\ncan't be removed unless no\nother pieces are available.");
	instructionLabel3->setCharacterSize(24);
	instructionLabel3->setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	instructionLabel3->setPosition(sf::Vector2f(100.f, 380.f));

	sf::Text* instructionLabel4 = new sf::Text();
	instructionLabel4->setString("Your goal is to leave your\nopponent with either 2 pieces\nor 0 moves!");
	instructionLabel4->setCharacterSize(24);
	instructionLabel4->setFont(context->fontHolder->getResource(Resources::FONT_LASERCORPS));
	instructionLabel4->setPosition(sf::Vector2f(100.f, 480.f));

	m_instructionsLabels.push_back(instructionLabel1);
	m_instructionsLabels.push_back(instructionLabel2);
	m_instructionsLabels.push_back(instructionLabel3);
	m_instructionsLabels.push_back(instructionLabel4);

	Button* play = new Button(context, 80 + 140, 620, 200, 80, "Play");
	play->setOnClick([context]() { context->gameEngine->queueReturn(); });

	m_objects.push_back(play);
}

InstructionsState::~InstructionsState() {
	while (!m_instructionsLabels.empty()) {
		delete m_instructionsLabels.back();
		
		m_instructionsLabels.pop_back();
	}
}

bool InstructionsState::render() {
	sf::RenderWindow* window = m_context->gameEngine->getWindow();

	window->draw(m_background);

	GameState::render();

	window->draw(m_howToPlayLabel);
	
	for (auto instruction : m_instructionsLabels)
		window->draw(*instruction);

	return false;
}
