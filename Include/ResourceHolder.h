#pragma once

#include <map>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "EnumResources.h"
#include <string>
#include <algorithm>
#include <utility>

// Klasa koja sadrži sve učitane resurse
template<typename T1, typename T2>
class ResourceHolder {
public:
	~ResourceHolder();
	
	T2& getResource(T1 resourceName);
private:
	std::map<T1, T2*> m_resources;
};

typedef ResourceHolder<Resources, sf::Texture> TextureHolder;
typedef ResourceHolder<Resources, sf::Font> FontHolder;
typedef ResourceHolder<Resources, sf::SoundBuffer> SoundHolder;

template<typename T1, typename T2>
ResourceHolder<T1, T2>::~ResourceHolder() {
	for (auto& p : m_resources) {
		delete p.second;
		p.second = nullptr;
	}
}

// Učitaj resurs čiji put do filea se nalazi u m_resourceLocation pod ključem resourceName
template<typename T1, typename T2>
T2& ResourceHolder<T1, T2>::getResource(T1 resourceName) {
	auto it = std::find_if(m_resources.begin(), m_resources.end(), [resourceName](auto p) { return p.first == resourceName; });

	// Učitaj resurs ako nije učitan već prije 
	if (it == m_resources.end()) {
		m_resources[resourceName] = new T2();

		if (m_resources[resourceName]->loadFromFile(m_resourcesLocation[resourceName])) {
			// ERROR ...
		}

		return *m_resources[resourceName];
	}

	// Inače vrati već učitani resurs
	return *it->second;
}