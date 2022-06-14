#pragma once
#include "AbstractComponent.hpp"
#include "IOnDeath.hpp"
#include "SchoolNinjaComponent.hpp"

//#include <memory>

namespace Scene {
	class IncreaseScoreComponent : public IOnDeath, public AbstractComponent {
	public:
		IncreaseScoreComponent(SchoolNinjaComponent*);

		void OnDeath() override;

	private:
		SchoolNinjaComponent* _game = nullptr;
	};
}