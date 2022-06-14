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
		DestroyObjectComponent(Scene*, float);
		DestroyObjectComponent(Scene*, SchoolNinjaComponent*);
		DestroyObjectComponent(Scene*, float, SchoolNinjaComponent*);
		void update(float) override;

		
	};
}