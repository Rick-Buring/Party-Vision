#pragma once
#include "AbstractComponent.hpp"
#include "IOnDeath.hpp"
#include "SchoolNinjaComponent.hpp"

//#include <memory>

namespace Scene {
	class IncreaseScoreComponent : public IOnDeath, public AbstractComponent {
	public:
		/// <summary>
		/// Intitializes SchoolNinjaComponent.
		/// </summary>
		/// <param name="">The SchoolNinjaComponent that handels the current games logic</param>
		IncreaseScoreComponent(SchoolNinjaComponent*);

		/// <summary>
		/// Adds 100 points to the current score.
		/// </summary>
		void OnDeath() override;

	private:
		SchoolNinjaComponent* _game = nullptr;
	};
}