#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"

namespace Scene {
	class DestroyObjectComponent : public AbstractComponent {
	private:
		float _timeToLive;
		Scene* _scene;

	public:
		DestroyObjectComponent(Scene*,float = 30.0f);
		void update(float) override;

		
	};
}