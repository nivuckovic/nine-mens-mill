#include "Board.h"
#include "GameEngine.h"
#include <iostream>
#include <algorithm>

Board::Board(Context* context) : GameObject(context) {
	m_offset.y = 80.f;
	createNodes();

	for (int i = 0; i < (int)Turn::NUMPLAYERS; ++i) {
		Turn player = (Turn)i;
		m_players[player] = PlayerInfo(player);
		m_players[player].m_leftToPlace = Globals::levelSelected->nodesToPlace;
	}
}

Board::~Board() {
	while (!m_nodes.empty()) {
		delete m_nodes.back();

		m_nodes.pop_back();
	}
}

bool Board::render() {
	sf::RenderWindow* m_window = m_context->gameEngine->getWindow();

	for (auto node : m_nodes) {
		node->drawAnimateGrid(m_window);
	}

	for (auto node : m_nodes) {
		node->render();
	}

	return false;
}

bool Board::input(sf::Event& e) {
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_context->gameEngine->getWindow());

	for (auto node : m_nodes) {
		node->input(e);
	}

	return false;
}

bool Board::update() {
	setNewMill(false);

	// Provjeri jel player okružen tj. nema više poteza za odigrati
	for (int i = 0; i < (int)Turn::NUMPLAYERS; ++i) {
		if (getPlayerInfo((Turn)i)->m_playerState == State::MOVING) {
			// Ako ne nađeš niti jedan node na koji se može pomaknuti onda je okružen
			auto it = std::find_if_not(m_nodes.begin(), m_nodes.end(), [i](Node* node) { return node->isSurrounded((Turn)i); });

			if (it == m_nodes.end()) {
				Globals::victor = (Turn)(((int)m_currentPlayer + 1) % (int)(Turn::NUMPLAYERS));
				m_players[m_currentPlayer].m_playerState = State::ENDGAME;
				m_context->gameEngine->queueState(StateNames::VICTORY, false);
				return false;
			}
		}
	}
	
	// Updateaj nodeove i ovisno o fazi playera namjesti sto ce se dogoditi kad se klikne na node
	for (auto node : m_nodes) {
		node->setOnClick(m_players[m_currentPlayer].m_playerState);
		node->update();
	}

	// Provjeri je li nodeovi formiraju mlin
	for (auto node : m_nodes) {
		node->checkInMill();
	}

	// Ako postoji novi mlin
	if (m_newMill == true) {
		m_context->audioManager->playSound(Resources::SOUND_MILL);

		m_players[m_currentPlayer].m_playerState = State::MILL;
		
		m_notInMill.clear();
		for (auto node : m_nodes) {
			if (node->isInMill() == false && node->getPlayer() != this->getPlayer() && node->isOccupied())
				m_notInMill.push_back(node);
		}
	}

	// Promjeni playera i odredi mu fazu u kojoj se nalazi
	if (m_players[m_currentPlayer].m_playerState == State::CHANGEPLAYER) {
		m_currentPlayer = (Turn)(((int)m_currentPlayer + 1) % (int)(Turn::NUMPLAYERS));
		m_players[m_currentPlayer].m_playerState = determineState();
	}

	return false;
}

Turn Board::getPlayer() {
	return m_currentPlayer;
}

void Board::changePlayerState(State state) {
	m_players[m_currentPlayer].m_playerState = state;
}

Node* Board::getNodeSelected() {
	return m_nodeSelected;
}

void Board::setNodeSelected(Node* node) {
	m_nodeSelected = node;
}

void Board::setLevel(Level* level) {
	m_level = level;
}

void Board::setNewMill(bool value) {
	m_newMill = value;
}

void Board::setAnimationRunning(bool value) {
	m_animationRunning = value;
}

PlayerInfo* Board::getCurrentPlayerInfo() {
	return &m_players[m_currentPlayer];
}

PlayerInfo* Board::getPrevPlayerInfo() {
	return &m_players[(Turn)(((int)getPlayer() - 1) % ((int)Turn::NUMPLAYERS))];
}

PlayerInfo* Board::getPlayerInfo(Turn player) {
	return &m_players[player];
}

std::vector<Node*> Board::getNodesNotInMill() {
	return m_notInMill;
}

void Board::createNodes() {
	m_level = Globals::levelSelected;

	for (int i = 0; i < m_level->numberOfNodes; ++i) {
		m_nodes.push_back(new Node(m_context, this));
	}

	for (int i = 0; i < m_level->numberOfNodes; ++i) {
		m_nodes[i]->setAdjacentNodes(m_level->adjacentNodes[i], m_nodes);
		m_nodes[i]->setPosition(m_offset + m_level->nodesCoordinates[i]);
	}
}

State Board::determineState() {
	if(getCurrentPlayerInfo()->m_leftToPlace > 0)
		return State::PLACING;
	
	if (getCurrentPlayerInfo()->m_leftOnBoard > 3)
		return State::MOVING;

	if (getCurrentPlayerInfo()->m_leftOnBoard == 3)
		return State::FLYING;

	if (getCurrentPlayerInfo()->m_leftOnBoard == 2) {
		Globals::victor = (Turn)(((int)m_currentPlayer + 1) % (int)(Turn::NUMPLAYERS));
		m_context->gameEngine->queueState(StateNames::VICTORY, false);
		return State::ENDGAME;
	}
}
