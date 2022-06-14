#pragma once
#include "AbstractComponent.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"


namespace Scene {
	class CollisionComponent : public AbstractComponent {
	public:
		CollisionComponent(Scene*);

		void update(float deltaTime) override;
		
	private:
		Scene* _scene;
	};
}