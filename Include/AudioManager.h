#pragma once

#include "ResourceHolder.h"


class AudioManager {
public:
	AudioManager();

	void playSound(Resources sound);
	void playBackgroundMusic();

	void setBackgroundVolume(float value);
	float getBackgroundVolume();

	void toggleBackgroundMusic();
	bool backgroundMusicMuted();

	void toggleSounds();
	bool soundsMuted();
private:
	SoundHolder m_soundHolder;

	std::map<Resources, sf::Sound> m_sounds;
	bool m_backgroundPlaying;

	float m_backgroundVolume;
	float m_soundVolume;
};

