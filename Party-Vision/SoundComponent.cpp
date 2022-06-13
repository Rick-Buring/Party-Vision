#include "SoundComponent.hpp"
#include "bass.h"
#include "fstream"

namespace Scene {
	std::string file;

	SoundComponent::SoundComponent(std::string soundFile) {
		file = soundFile;
	}
	void SoundComponent::PlayMusic()
	{
		HSTREAM slice = BASS_StreamCreateFile(FALSE, file.c_str(), 0, 0, 0);
		BASS_ChannelPlay(slice, TRUE);
	}

	void SoundComponent::OnDeath()
	{
		PlayMusic();
	}
}