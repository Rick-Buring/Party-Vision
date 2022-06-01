#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"

namespace Scene {
	class SchoolNinja;
	class DestroyObjectComponent : public AbstractComponent {
	private:
		float _timeToLive = 30.0f;
		SchoolNinja* _game = nullptr;
		Scene* _scene;

	public:
		DestroyObjectComponent(Scene*, float);
		DestroyObjectComponent(Scene*, SchoolNinja*);
		DestroyObjectComponent(Scene*, float, SchoolNinja*);
		void update(float) override;

		
	};
}