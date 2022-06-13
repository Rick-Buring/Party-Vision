#pragma once
#include "Scene.hpp"
#include "AbstractComponent.hpp"
#include "SchoolNinjaComponent.hpp"

namespace Scene {
	class DestroyObjectComponent : public AbstractComponent {
	private:
		float _timeToLive = 30.0f;
		SchoolNinja* _game = nullptr;
		Scene* _scene;

	public:
		DestroyObjectComponent(Scene*, float);
		DestroyObjectComponent(Scene*, SchoolNinja*);
		DestroyObjectComponent(Scene*, float, SchoolNinja*);

		//inherited function from abstract component
		void update(float) override;

		
	};
}