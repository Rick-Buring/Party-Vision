#pragma once
#include "AbstractComponent.hpp"
#include "GameObject.hpp"


namespace Scene {
	class CollisionComponent : public AbstractComponent {
	public:
		CollisionComponent(std::shared_ptr<GameObject> mouse);

		void update(float deltaTime) override;
		
	private:

	};
}