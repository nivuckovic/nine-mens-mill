#pragma once
#include "GameState.h"

class MenuState : public GameState {
public:
	MenuState(Context* context);
	~MenuState();

	bool render() override;
	bool input(sf::Event& e) override;
	bool update() override;

private:

};

