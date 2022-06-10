#pragma once
#include "AbstractComponent.hpp"
#include "GameObject.hpp"


namespace Scene {
	class CollisionComponent : public AbstractComponent {
	public:
		CollisionComponent();

		void update(float deltaTime) override;
		
	private:

	};
}