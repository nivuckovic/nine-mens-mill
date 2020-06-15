#include "AudioManager.h"

#include <algorithm>

AudioManager::AudioManager() : m_soundVolume(25.f), m_backgroundVolume(25.f) {
}

void AudioManager::playSound(Resources sound) {
	// Učitaj zadani resurs ako nije učitan već prije
	if (std::find_if(m_sounds.begin(), m_sounds.end(), [sound](auto& pair) { return pair.first == sound; }) == m_sounds.end()) {
		sf::Sound newSound(m_soundHolder.getResource(sound));

		newSound.setVolume(m_soundVolume);

		m_sounds[sound] = newSound;
	}

	m_sounds[sound].play();
}

void AudioManager::playBackgroundMusic() {
	if (m_backgroundPlaying)
		return;

	playSound(Resources::SOUND_BACKGROUNDMUSIC);

	m_sounds[Resources::SOUND_BACKGROUNDMUSIC].setLoop(true);
	m_backgroundPlaying = true;
}

void AudioManager::setBackgroundVolume(float value) {
	m_backgroundVolume = value;
}

float AudioManager::getBackgroundVolume() {
	return m_backgroundVolume;
}

void AudioManager::toggleBackgroundMusic() {
	if (m_backgroundVolume == 0.f) 
		m_backgroundVolume = 25.f;
	else 
		m_backgroundVolume = 0.f;

	m_sounds[Resources::SOUND_BACKGROUNDMUSIC].setVolume(m_backgroundVolume);
}

bool AudioManager::backgroundMusicMuted() {
	if (m_backgroundVolume == 0.f)
		return true;
	
	return false;
}

void AudioManager::toggleSounds() {
	if (m_soundVolume == 0.f)
		m_soundVolume = 25.f;
	else
		m_soundVolume = 0.f;

	for (auto& sound : m_sounds)
		if(sound.first != Resources::SOUND_BACKGROUNDMUSIC)
			sound.second.setVolume(m_soundVolume);
}

bool AudioManager::soundsMuted() {
	if (m_soundVolume == 0.f)
		return true;

	return false;
}
