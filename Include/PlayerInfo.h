#pragma once
#pragma once

#include "EnumsBoard.h"
#include "SFML/Graphics.hpp"
#include <map>
#include "Globals.h"

struct PlayerInfo {
	PlayerInfo() {};

	PlayerInfo(Turn player) {
		m_playerState = State::PLACING;
		m_isInMill = false;
		m_leftToPlace = 4;
		m_leftOnBoard = 0;
	}

	State m_playerState;
	
	int m_leftToPlace;
	int m_leftOnBoard;

	bool m_isInMill;
};


