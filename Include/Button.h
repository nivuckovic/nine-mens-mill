#pragma once

#include "GameObject.h"

#include "SFML/Graphics.hpp"
#include <string>
#include <functional>

class Button : public GameObject {
public:
	Button(Context* context, float _x, float _y, float _w, float _h, std::string label);

	bool render() override;
	bool input(sf::Event& e) override;
	bool update() override;

	void onFocus() override;
	void whileFocused() override;
	void onFocusExit() override;

	void setOnClick(std::function<void()>);
	void onClick() override;

	void setLabel(std::string label);

	sf::Vector2f getPosition();
private:
	sf::RectangleShape m_button;
	sf::Text m_label;

	std::function<void()> onClickFunc;
	sf::Color backgroundColor;
	sf::Color onFocusBackgroundColor;
};

