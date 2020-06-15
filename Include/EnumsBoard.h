#pragma once

enum class Turn {
	Player1,
	Player2,
	NUMPLAYERS,
	Player3,
	NONE
};

enum class State {
	PLACING,
	MOVING,
	FLYING,
	MILL,
	CHANGEPLAYER,
	ENDGAME,
	LENGTH
};