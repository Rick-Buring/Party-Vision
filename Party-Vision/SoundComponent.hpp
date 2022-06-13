#pragma once
#include "IOnDeath.hpp"
#include "AbstractComponent.hpp"
#include <string>
#include "bass.h"

namespace Scene {
	class GameObject;
	class SoundComponent : public IOnDeath, public AbstractComponent {
	public:
		/// <summary>
		/// Initializes the soundComponent
		/// </summary>
		/// <param name="soundFile">
		/// Saves the soundFIle so it can be used next time.
		/// </param>
		SoundComponent(std::string soundFile);
		/// <summary>
		/// Plays music of the current track.
		/// </summary>
		void PlayMusic();

		/// <summary>
		/// Will use PlayMusic on the death of the object.
		/// </summary>
		void OnDeath() override;

	private:
		std::string file;
	};
}