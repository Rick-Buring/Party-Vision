#include "SoundComponent.hpp"
#include "bass.h"
#include "fstream"

namespace Scene {

	SoundComponent::SoundComponent(std::string soundFile) {
		SoundComponent::_file = soundFile;
	}
	void SoundComponent::PlayMusic()
	{
		//Code to use the sound
		HSTREAM slice = BASS_StreamCreateFile(FALSE, SoundComponent::_file.c_str(), 0, 0, 0);
		BASS_ChannelPlay(slice, TRUE);
	}

	void SoundComponent::OnDeath()
	{
		PlayMusic();
	}
}