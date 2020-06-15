#pragma once

#include "Node.h"

#include <iostream>
#include "GameEngine.h"
#include "Board.h"

Node::Node(Context* context, Board* board) : GameObject(context), maxRadius(20.f), radius(0.f), m_collisionBox(radius), m_millDirection(((int)Directions::SIZE / 2)), m_board(board), m_millLinePercentage((int)Directions::SIZE) {
	m_collisionBox.setOrigin(radius, radius);
	m_collisionBox.setFillColor(sf::Color::White);

	m_player = Turn::NONE;

	m_adjacentRadius = maxRadius / 2.f;

	m_selectedRadius = maxRadius / 4.f;
	m_selectedAngle = 0.f;

	m_mainInc = true;

	m_distLeft = 0.f;

	// Predefiniramo funkcije za zadane faze playera
	m_onClick = []() {};
	// Ako polje nije okupirano postavi zastavicu da je okupiran i umanji brojač playeru koliko mu je komada ostala za postaviti
	m_onClickFunc[State::PLACING] = [this]() {
		if (isOccupied()) {
			return;
		}

		this->m_context->audioManager->playSound(Resources::SOUND_PLACE);

		// Označi da je node zauzet
		setPlayer(getBoard()->getPlayer());
		setPrevColor(Globals::playerColors[getPlayer()]);
		setPrevState(State::PLACING);

		// Daj signal da se promjeni Turn
		getBoard()->changePlayerState(State::CHANGEPLAYER);

		// Promjeni playerInfo
		--getBoard()->getPlayerInfo(getPlayer())->m_leftToPlace;
		++getBoard()->getPlayerInfo(getPlayer())->m_leftOnBoard;

		setOccupied(true);

		if (checkInMill())
			m_board->setNewMill(true);

		return;
	};

	// Player je u millu, provjeri je li kliknuti zauzet od strane protivnickog igraca i moguce ga je ukloniti te ga ukloni
	m_onClickFunc[State::MILL] = [this]() {
		if (isOccupied() && getNodePlayer() != m_board->getPlayer()) {

			// Ako postoji node van mlina
			if (cannotRemoveFromMill())
				return;

			this->m_context->audioManager->playSound(Resources::SOUND_REMOVE);

			setOccupied(false);

			setPrevColor(Globals::playerColors[getPlayer()]);
			setPrevState(State::MILL);

			// Promjeni playerInfo
			--getBoard()->getPlayerInfo(this->getPlayer())->m_leftOnBoard;

			setPlayer(Turn::NONE);
			getBoard()->changePlayerState(State::CHANGEPLAYER);

			return;
		}
	};

	m_onClickFunc[State::MOVING] = [this]() {
		// Ako je već selektiran node s kojeg želimo pomaknuti i moguće ga je pomaknuti na kliknuti node
		if (isValidMove()) {
			getBoard()->getNodeSelected()->setPlayer(Turn::NONE);
			getBoard()->getNodeSelected()->setOccupied(false);

			setPrevColor(Globals::playerColors[getBoard()->getPlayer()]);
			setPrevPos(getBoard()->getNodeSelected()->getPosition());
			getBoard()->getNodeSelected()->setPrevState(State::MOVING);
			setPrevState(State::MOVING);
			setDistanceLeft();

			this->setPlayer(getBoard()->getPlayer());
			this->setOccupied(true);

			getBoard()->changePlayerState(State::CHANGEPLAYER);
			getBoard()->setNodeSelected(nullptr);

			this->m_context->audioManager->playSound(Resources::SOUND_MOVE);

			if (checkInMill())
				m_board->setNewMill(true);

		}
		else {
			// Ako nije selektiran node i kliknuti node pripada playeru koji je na potezu
			if (getNodePlayer() == m_board->getPlayer()) {
				this->m_context->audioManager->playSound(Resources::SOUND_PLACE);
				getBoard()->setNodeSelected(this);
			}
		}
	};

	m_onClickFunc[State::FLYING] = [this]() {
		if (isValidMove()) {
			getBoard()->getNodeSelected()->setPlayer(Turn::NONE);
			getBoard()->getNodeSelected()->setOccupied(false);

			setPrevColor(Globals::playerColors[getBoard()->getPlayer()]);
			setPrevPos(getBoard()->getNodeSelected()->getPosition());
			setPrevState(State::FLYING);

			this->setPlayer(getBoard()->getPlayer());
			this->setOccupied(true);

			getBoard()->changePlayerState(State::CHANGEPLAYER);
			getBoard()->setNodeSelected(nullptr);

			this->m_context->audioManager->playSound(Resources::SOUND_MOVE);

			if (checkInMill())
				m_board->setNewMill(true);
		}
		else {
			if (getNodePlayer() == m_board->getPlayer()) {
				this->m_context->audioManager->playSound(Resources::SOUND_PLACE);
				getBoard()->setNodeSelected(this);
			}
		}
	};
}

bool Node::input(sf::Event& e) {
	sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(*m_context->gameEngine->getWindow());

	float distance = (m_collisionBox.getPosition().x - mousePosition.x) * (m_collisionBox.getPosition().x - mousePosition.x) +
		(m_collisionBox.getPosition().y - mousePosition.y) * (m_collisionBox.getPosition().y - mousePosition.y);

	bool m_focusEntered = distance < maxRadius * maxRadius ? true : false;

	if (e.type == sf::Event::MouseButtonPressed) {
		if (e.mouseButton.button == sf::Mouse::Left) {
			m_isClicked = m_focusEntered ? true : false;
		}
	}

	return false;
}

bool Node::update() {
	GameObject::update();
	
	return false;
}

bool Node::render() {
	sf::RenderWindow* m_window = m_context->gameEngine->getWindow();

	drawAnimateAdjacentNodes(m_window);
	drawAnimateMainNode(m_window);
	drawAnimateSelectedNode(m_window);
	drawAnimateRemovableNodes(m_window);

	return false;
}

void Node::setAdjacentNodes(std::vector<int> adjacentNodes, std::vector<Node*> nodes) {
	for (int i = 0; i < (int)Directions::SIZE; ++i) {
		if (adjacentNodes[i] != -1)
			m_adjacentNodes.push_back(nodes[adjacentNodes[i]]);
		else
			m_adjacentNodes.push_back(nullptr);
	}
}

void Node::setPosition(sf::Vector2f position) {
	m_collisionBox.setPosition(position);
}

sf::Vector2f Node::getPosition() {
	return m_collisionBox.getPosition();
}

void Node::setInMill(bool value) {
	m_inMill = value;
}

bool Node::isInMill() {
	return m_inMill;
}

bool Node::isOccupied() {
	return m_occupied;
}

void Node::setOccupied(bool value) {
	m_occupied = value;
}

Turn Node::getPlayer() {
	return m_player;
}

void Node::setPlayer(Turn value) {
	m_player = value;
}

void Node::setPrevColor(sf::Color color) {
	m_prevColor = color;
}

void Node::setPrevPos(sf::Vector2f pos) {
	m_prevPos = pos;
}

void Node::setPrevState(State state) {
	m_prevState = state;
}

void Node::setDistanceLeft() {
	m_distLeft = 1.f;
}

Board* Node::getBoard() {
	return m_board;
}

Node* Node::getAdjacentAt(int index) {
	return m_adjacentNodes[index];
}

bool Node::isAdjacent() {
	Node* selectedNode = getBoard()->getNodeSelected();

	if (selectedNode == nullptr)
		return false;

	for (int i = 0; i < (int)Directions::SIZE; ++i)
		if (m_adjacentNodes[i] == selectedNode)
			return true;

	return false;
}

bool Node::isValidMove() {
	if (getBoard()->getCurrentPlayerInfo()->m_playerState == State::FLYING)
		return getBoard()->getNodeSelected() != nullptr && getPlayer() == Turn::NONE;

	if (getBoard()->getCurrentPlayerInfo()->m_playerState == State::MOVING)
		return isAdjacent() && getPlayer() == Turn::NONE;

	if (getBoard()->getCurrentPlayerInfo()->m_playerState == State::PLACING)
		return !isOccupied();

	return false;
}

bool Node::cannotRemoveFromMill() {
	std::vector<Node*> notInMill = getBoard()->getNodesNotInMill();

	return !notInMill.empty() && std::find(notInMill.begin(), notInMill.end(), this) == notInMill.end();
}

Turn Node::getNodePlayer() {
	return m_player;
}

void Node::setOnClick(State state) {
	m_onClick = m_onClickFunc[state];
}

void Node::onClick() {
	m_onClick();
}

void Node::drawAnimateGrid(sf::RenderWindow* window) {
	sf::CircleShape m_backgroundCircle = m_collisionBox;
	m_backgroundCircle.setRadius(maxRadius);
	m_backgroundCircle.setOrigin(sf::Vector2f(maxRadius, maxRadius));
	m_backgroundCircle.setFillColor(sf::Color::White);

	window->draw(m_backgroundCircle);

	sf::RectangleShape line;
	sf::RectangleShape millLine;

	for (int i = (int)Directions::RIGHT; i < (int)Directions::LEFT; ++i) {
		if (m_adjacentNodes[i] != nullptr) {
			float width = Globals::distance(m_adjacentNodes[i]->getPosition(), getPosition());
			float height = 12.5f;

			sf::RectangleShape line;
			line.setSize(sf::Vector2f(width, height));
			line.setPosition(getPosition());
			line.setOrigin(0, height / 2);
			line.rotate(-90.f + 45.f * i);
			line.setFillColor(sf::Color::White);
			window->draw(line);
		}
	}

	for (int i = 0; i < (int)Directions::SIZE; ++i) {
		if (m_adjacentNodes[i] != nullptr) {
			float width = Globals::distance(getPosition(), m_adjacentNodes[i]->getPosition());
			float height = 12.5f;

			if ((isInMill() && m_millDirection[i % ((int)Directions::SIZE / 2)]) || m_millLinePercentage[i] > 0) {

				updateParameter(m_millLinePercentage[i], 0.05f, 0, 1, m_millLineInc[i]);

				sf::RectangleShape millLine;
				millLine.setSize(sf::Vector2f(width * m_millLinePercentage[i] / 2, height  / 3));
				millLine.setPosition(getPosition());
				millLine.rotate(-90.f + 45.f * i);
				millLine.setOrigin(0, height / 6);
				millLine.setFillColor(isOccupied() ? Globals::playerColors[getPlayer()] : m_prevColor);

				window->draw(millLine);
			}
		}
	}
}

bool Node::isSelected() {
	return selected;
}

bool Node::isSurrounded(Turn player) {
	for (int i = 0; i < (int)Directions::SIZE; ++i) {
		if (getPlayer() == m_board->getPlayer() && m_adjacentNodes[i] != nullptr && !m_adjacentNodes[i]->isOccupied())
			return false;
	}
	
	return true;
}

void Node::drawAnimateAdjacentNodes(sf::RenderWindow* window) {
	if (isValidMove()) {
		sf::CircleShape circle;

		circle.setRadius(m_adjacentRadius);
		circle.setOrigin(m_adjacentRadius, m_adjacentRadius);
		circle.setPosition(getPosition());
		circle.setFillColor(sf::Color::Green);

		window->draw(circle);
	}
}

void Node::drawAnimateSelectedNode(sf::RenderWindow* window) {
	if (getBoard()->getNodeSelected() == this) {
		sf::CircleShape circle;

		float posX, posY;
		float r = maxRadius * 0.75f;

		posX = getPosition().x + r * cos(m_selectedAngle);
		posY = getPosition().y + r * sin(m_selectedAngle);

		m_selectedAngle = fmod(m_selectedAngle + 0.05f, 2 * 3.14);

		circle.setRadius(m_selectedRadius);
		circle.setOrigin(m_selectedRadius, m_selectedRadius);
		circle.setPosition(sf::Vector2f(posX, posY));
		circle.setFillColor(Globals::playerColors[getPlayer()]);

		window->draw(circle);
	}
}

void Node::drawAnimateMainNode(sf::RenderWindow* window) {
	sf::CircleShape circle;

	if (isOccupied()) {
		if (m_prevState == State::MOVING)
			radius = maxRadius * 0.5f;
		else if (getBoard()->getCurrentPlayerInfo()->m_playerState == State::MILL) {
			if (m_prevState == State::MOVING) {
				radius = maxRadius * 0.5f;
			}
			else {
				if (radius < maxRadius * 0.5f)
					radius += 0.75;
			}
		}
		else {
			if (radius < maxRadius * 0.5f)
				radius += 0.75;
		}

		if (m_distLeft > 0) {
			sf::Vector2f direction = getPosition() - m_prevPos;

			circle.setPosition(getPosition() - m_distLeft * direction);

			m_distLeft -= 0.05f;
		}
		else {
			circle.setPosition(getPosition());
		}

		circle.setFillColor(Globals::playerColors[getPlayer()]);
		circle.setRadius(radius);
		circle.setOrigin(radius, radius);
	}

	if (!isOccupied()) {
		if (m_prevState == State::MOVING)
			radius = 0;
		else if (radius > 0)
			radius -= 0.75;

		m_selectedAngle = 0.f;

		circle.setPosition(getPosition());
		circle.setFillColor(m_prevColor);
		circle.setRadius(radius);
		circle.setOrigin(radius, radius);
	}

	window->draw(circle);
}

void Node::drawAnimateRemovableNodes(sf::RenderWindow* window) {
	if (getBoard()->getCurrentPlayerInfo()->m_playerState == State::MILL && !cannotRemoveFromMill() && isOccupied()) {
		sf::CircleShape circle(maxRadius / 4.f);

		float posX, posY;
		float r = maxRadius * 0.75f;

		posX = getPosition().x + r * cos(m_selectedAngle);
		posY = getPosition().y + r * sin(m_selectedAngle);

		m_selectedAngle = fmod(m_selectedAngle + 0.05f, 2 * 3.14);

		circle.setOrigin(maxRadius / 4.f, maxRadius / 4.f);
		circle.setPosition(sf::Vector2f(posX, posY));
		circle.setFillColor(Globals::playerColors[getPlayer()]);

		window->draw(circle);
	}
}

void Node::updateParameter(float& param, float rate, float minParam, float maxParam, bool& inc) {
	if (param < maxParam && inc) {
		param += rate;
	}

	if (param > minParam && !inc) {
		param -= rate;
	}
}

bool Node::checkInMill() {
	if (!isOccupied()) {
		m_inMill = false;
		
		for (int i = 0; i < (int)Directions::SIZE; ++i)
			m_millLineInc[i] = false;
		
		return false;
	}

	// Za sve smjerove provjeri sljedeće
	bool foundMill = false;
	for (int i = 0; i < (int)Directions::SIZE / 2; ++i) {
		// Ako je trenutni i jednak smjeru desno onda provjeri lijevo i desno je li zauzeti node pripada playeru
		if (m_adjacentNodes[i] != nullptr && m_adjacentNodes[i + 4] != nullptr) {
			if (m_adjacentNodes[i]->isOccupied() && m_adjacentNodes[i + 4]->isOccupied()) {
				if ((m_adjacentNodes[i]->getNodePlayer() == m_adjacentNodes[i + 4]->getNodePlayer()) && (m_adjacentNodes[i + 4]->getNodePlayer() == getNodePlayer())) {
					foundMill = true;

					m_inMill = true;
					m_millDirection[i % ((int)Directions::SIZE / 2)] = true;
					m_millLineInc[i] = true;
					m_millLineInc[i + (int)Directions::SIZE / 2] = true;
					continue;
				}
			}
		}
		// Provjeri je li node desno i desno od desnog noda pripada playeru
		else if (m_adjacentNodes[i] != nullptr && m_adjacentNodes[i]->getAdjacentAt(i) != nullptr) {
			if (m_adjacentNodes[i]->isOccupied() && m_adjacentNodes[i]->getAdjacentAt(i)->isOccupied()) {
				if ((m_adjacentNodes[i]->getNodePlayer() == m_adjacentNodes[i]->getAdjacentAt(i)->getNodePlayer()) && (m_adjacentNodes[i]->getNodePlayer() == getNodePlayer())) {
					foundMill = true;

					m_inMill = true;
					m_millDirection[i % ((int)Directions::SIZE / 2)] = true;
					m_millLineInc[i] = true;
					m_millLineInc[i + (int)Directions::SIZE / 2] = true;
					continue;
				}
			}
		}
		// Provjeri za suprotan smjer
		else if (m_adjacentNodes[i + 4] != nullptr && m_adjacentNodes[i + 4]->getAdjacentAt(i + 4) != nullptr) {
			if (m_adjacentNodes[i + 4]->isOccupied() && m_adjacentNodes[i + 4]->getAdjacentAt(i + 4)->isOccupied()) {
				if ((m_adjacentNodes[i + 4]->getNodePlayer() == m_adjacentNodes[i + 4]->getAdjacentAt(i + 4)->getNodePlayer()) && (m_adjacentNodes[i + 4]->getNodePlayer() == getNodePlayer())) {
					foundMill = true;

					m_inMill = true;
					m_millDirection[i % ((int)Directions::SIZE / 2)] = true;
					m_millLineInc[i] = true;
					m_millLineInc[i + (int)Directions::SIZE / 2] = true;
					continue;
				}
			}
		}

		m_millDirection[i % ((int)Directions::SIZE / 2)] = false;
		m_millLineInc[i] = false;
		m_millLineInc[i + (int)Directions::SIZE / 2] = false;
	}

	if (!foundMill) {
		m_inMill = false;
	}

	return foundMill;
}
