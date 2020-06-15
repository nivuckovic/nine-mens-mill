#pragma once

#include <map>
#include <string>

enum class Resources {
	TEXTURE_STANDARD,
	TEXTURE_MORABARABA,
	FONT_LASERCORPS,
	SOUND_BACKGROUNDMUSIC,
	SOUND_PLACE,
	SOUND_REMOVE,
	SOUND_CLICK,
	SOUND_HOVER,
	SOUND_MILL,
	SOUND_MOVE,
	LENGTH
};

extern std::map<Resources, std::string> m_resourcesLocation;
