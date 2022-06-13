#pragma once
#include "IOnDeath.hpp"
#include "AbstractComponent.hpp"
#include <string>
#include "bass.h"

namespace Scene {
	class GameObject;
	class SoundComponent : public IOnDeath, public AbstractComponent {
	public:
		SoundComponent(std::string soundFile);
		void PlayMusic();

		void OnDeath() override;

	private:
		std::string file;
	};
}