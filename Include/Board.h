#pragma once

#include "GameObject.h"
#include "Context.h"
#include "Node.h"
#include "EnumsBoard.h"
#include "PlayerInfo.h"
#include "Level.h"

class Board : public GameObject {
public:
	Board(Context* context);
	~Board();

	bool render();
	bool input(sf::Event& e);
	bool update();

	Turn getPlayer();
	void changePlayerState(State state);

	Node* getNodeSelected();
	void setNodeSelected(Node* node);

	void setLevel(Level* level);
	void setNewMill(bool value);

	void setAnimationRunning(bool value);

	PlayerInfo* getCurrentPlayerInfo();
	PlayerInfo* getPrevPlayerInfo();
	PlayerInfo* getPlayerInfo(Turn player);

	std::vector<Node*> getNodesNotInMill();

private:
	void createNodes();

	State determineState();

private:
	Level* m_level;
	sf::Vector2f m_offset;
	std::vector<Node*> m_nodes;

	bool m_newMill;

	Turn m_currentPlayer;
	
	std::map<Turn, PlayerInfo> m_players;
	Node* m_nodeSelected;

	std::vector<Node*> m_notInMill;

	bool m_animationRunning;
};

