#pragma once

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Context.h"
#include <functional>
#include "EnumsBoard.h"

enum class Directions {
	TOP,
	TOPRIGHT,
	RIGHT,
	DOWNRIGHT,
	DOWN,
	DOWNLEFT,
	LEFT,
	UPLEFT,
	SIZE
};

class Board;

class Node : public GameObject {
public:
	Node(Context* context, Board* board);

	bool input(sf::Event& e) override;
	bool update() override;
	bool render() override;

	void setAdjacentNodes(std::vector<int> adjacentNodes, std::vector<Node*> nodes);
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();;

	void setInMill(bool value);

	bool isInMill();

	bool isOccupied();
	void setOccupied(bool value);

	Turn getPlayer();
	void setPlayer(Turn value);

	void setPrevColor(sf::Color color);
	void setPrevPos(sf::Vector2f pos);
	void setPrevState(State state);
	void setDistanceLeft();

	Board* getBoard();

	bool checkInMill();

	Node* getAdjacentAt(int index);
	bool isAdjacent();
	bool isValidMove();
	bool cannotRemoveFromMill();

	Turn getNodePlayer();
	void setOnClick(State state);

	void drawAnimateGrid(sf::RenderWindow* window);

	bool isSelected();
	bool isSurrounded(Turn player);
private:
	void onClick();

	void drawAnimateAdjacentNodes(sf::RenderWindow* window);
	void drawAnimateSelectedNode(sf::RenderWindow* window);
	void drawAnimateMainNode(sf::RenderWindow* window);
	void drawAnimateRemovableNodes(sf::RenderWindow* window);

	void updateParameter(float& param, float rate, float minParam, float maxParam, bool& inc);
private:
	Board* m_board;

	float radius;
	float maxRadius;
	bool m_mainInc;

	float m_adjacentRadius;

	float m_selectedRadius;
	float m_selectedAngle;
	
	std::vector<float> m_millLinePercentage;
	bool m_millLineInc[9];

	sf::CircleShape m_collisionBox;

	std::vector<Node*> m_adjacentNodes;
	std::vector<bool> m_millDirection;

	bool m_occupied = false;
	bool m_inMill;

	Turn m_player;

	std::function<void()> m_onClick;
	std::map<State, std::function<void()>> m_onClickFunc;

	bool selected = false;

	sf::Color m_prevColor;
	sf::Vector2f m_prevPos;
	float m_distLeft;
	State m_prevState;
};
