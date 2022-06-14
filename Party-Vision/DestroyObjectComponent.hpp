#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"

namespace Scene {
	class SchoolNinjaComponent;
	class DestroyObjectComponent : public AbstractComponent {
	private:
		float _timeToLive = 30.0f;
		SchoolNinjaComponent* _game = nullptr;
		Scene* _scene;

	public:
		/// <summary>
		/// Constructor for destroy object component.
		/// </summary>
		/// <param name="Scene">The scene to remove this object from</param>
		/// <param name="float">The time to live</param>
		DestroyObjectComponent(Scene*, float);

		/// <summary>
		/// Constructor for destroy object component.
		/// </summary>
		/// <param name="Scene">The scene to remove this object from</param>
		/// <param name="SchoolNinjaComponent">Will update score and other statisticst for the game upon destruction</param>
		DestroyObjectComponent(Scene*, SchoolNinjaComponent*);

		/// <summary>
		/// Constructor for destroy object component.
		/// </summary>
		/// <param name="Scene">The scene to remove this object from</param>
		/// <param name="float">The time to live</param>
		/// <param name="SchoolNinjaComponent">Will update score and other statisticst for the game upon destruction</param>
		DestroyObjectComponent(Scene*, float, SchoolNinjaComponent*);
		void update(float) override;

		
	};
}