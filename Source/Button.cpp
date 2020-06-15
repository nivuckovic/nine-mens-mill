#include "Button.h"
#include "Context.h"
#include "GameEngine.h"
#include "ResourceHolder.h"
#include "Context.h"
#include <iostream>

Button::Button(Context* context, float _x, float _y, float _w, float _h, std::string label) : GameObject(context), m_button(sf::Vector2f(_w, _h)), onClickFunc([]() {}) {
	
	backgroundColor = sf::Color(0, 0, 255, 200);
	onFocusBackgroundColor = sf::Color(0, 0, 255, 255);

	m_button.setPosition(sf::Vector2f(_x, _y));
	m_button.setFillColor(backgroundColor);

	m_label.setString(label);
	m_label.setCharacterSize(24);
	m_label.setFillColor(sf::Color::White);
	m_label.setFont(m_context->fontHolder->getResource(Resources::FONT_LASERCORPS));

	float labelX = _x + (_w - m_label.getGlobalBounds().width) / 2;
	float labelY = _y + (_h - m_label.getGlobalBounds().height) / 2;

	m_label.setPosition(sf::Vector2f(labelX, labelY));
	m_label.setOrigin(2.f, 6.f);

	m_isClicked = false;
}

bool Button::render() {
	sf::RenderWindow* m_window = m_context->gameEngine->getWindow();

	m_window->draw(m_button);
	m_window->draw(m_label);

	return true;
}

bool Button::input(sf::Event& e) {
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_context->gameEngine->getWindow());

	m_focusEntered = m_button.getGlobalBounds().contains(mousePosition) ? true : false;

	if (e.type == sf::Event::MouseButtonPressed) {
		if (e.mouseButton.button == sf::Mouse::Left) {
			m_isClicked = m_focusEntered ? true : false;
		}
	}
	
	return true;
}

bool Button::update() {
	GameObject::update();

	return false;
}

void Button::onFocus() {
	m_context->audioManager->playSound(Resources::SOUND_HOVER);

	m_button.setFillColor(onFocusBackgroundColor);
	m_label.setFillColor(sf::Color::Red);
}

void Button::whileFocused() {

}

void Button::onFocusExit() {
	m_button.setFillColor(backgroundColor);
	m_label.setFillColor(sf::Color::White);
}

void Button::setOnClick(std::function<void()> func) {
	onClickFunc = func;
}

void Button::onClick() {
	m_context->audioManager->playSound(Resources::SOUND_CLICK);
	onClickFunc();
}

void Button::setLabel(std::string label) {
	m_label.setString(label);

	float labelX = m_button.getGlobalBounds().left + (m_button.getGlobalBounds().width - m_label.getGlobalBounds().width) / 2;
	float labelY = m_button.getGlobalBounds().top + (m_button.getGlobalBounds().height - m_label.getGlobalBounds().height) / 2;

	m_label.setPosition(sf::Vector2f(labelX, labelY));
}

sf::Vector2f Button::getPosition() {
	return m_button.getPosition();
}
