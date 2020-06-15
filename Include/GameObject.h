#pragma once
#include "SFML/Graphics.hpp"

class Context;


class GameObject {
public:
	GameObject(Context* context);

	virtual bool render() = 0;
	virtual bool input(sf::Event& e) = 0;
	virtual bool update();

	virtual void onFocus() {};
	virtual void whileFocused() {};
	virtual void onFocusExit() {}
	virtual void onClick() {};

protected:
	Context* m_context;

	bool m_isFocused;
	bool m_focusEntered;
	bool m_isClicked;
};

inline GameObject::GameObject(Context* context) : m_context(context), m_isFocused(false), m_focusEntered(false), m_isClicked(false) {}

inline bool GameObject::update()
{
	if (m_isFocused && m_focusEntered) {
		whileFocused();
	}

	if (!m_isFocused && m_focusEntered) {
		m_isFocused = true;
		onFocus();
	}

	if (m_isFocused && !m_focusEntered) {
		m_isFocused = false;
		onFocusExit();
	}

	if (m_isClicked) {
		m_isClicked = false;
		onClick();
	}

	return false;
}

