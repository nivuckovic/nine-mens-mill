#pragma once

#include "ResourceHolder.h"

class GameEngine;
class AudioManager;

class Context {
public:
	Context(GameEngine* _gameEngine, TextureHolder* _textureHolder, FontHolder* _fontHolder, AudioManager* _audioManager) {
		gameEngine = _gameEngine;
		textureHolder = _textureHolder;
		fontHolder = _fontHolder;
		audioManager = _audioManager;
	}

	GameEngine* gameEngine;
	TextureHolder* textureHolder;
	FontHolder* fontHolder;
	AudioManager* audioManager;
};