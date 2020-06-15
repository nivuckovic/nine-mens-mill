#include "Globals.h"

std::map<Turn, sf::Color> Globals::playerColors = {
	{Turn::Player1, sf::Color::Red},
	{Turn::Player2, sf::Color::Blue},
	{Turn::Player3, sf::Color::Yellow}
};

std::map<State, std::string> Globals::stateInstructions{
	{State::PLACING, "Set your pieces on the board"},
	{State::MILL, "Remove one of your \nopponent's pieces"},
	{State::MOVING, "Move your pieces to \ncreate a mill"},
	{State::FLYING, "Move your pieces to \ncreate a mill"}
};

float Globals::distance(sf::Vector2f a, sf::Vector2f b) {
	return sqrt((b.x - a.x) * (b.x - a.x) +(b.y - a.y) * (b.y - a.y));
}

Level* Globals::levelSelected = nullptr;
Turn Globals::victor = Turn::NONE;