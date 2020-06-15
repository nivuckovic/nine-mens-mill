#include "EnumResources.h"

std::map<Resources, std::string> m_resourcesLocation{
	{ Resources::TEXTURE_STANDARD, "Textures/standard.png"},
	{ Resources::TEXTURE_MORABARABA, "Textures/morabaraba.png"},

	{ Resources::FONT_LASERCORPS, "Fonts/lasercorps.ttf" }, 

	{ Resources::SOUND_BACKGROUNDMUSIC, "Sounds/background-looped.ogg" },
	{ Resources::SOUND_PLACE, "Sounds/phaserUp3.ogg" },
	{ Resources::SOUND_REMOVE, "Sounds/phaserDown3.ogg" },
	{ Resources::SOUND_MILL, "Sounds/phaseJump2.ogg" },
	{ Resources::SOUND_CLICK, "Sounds/tone1.ogg" },
	{ Resources::SOUND_HOVER, "Sounds/switch1.ogg" },
	{ Resources::SOUND_MOVE, "Sounds/phaserUp6.ogg" }
};
