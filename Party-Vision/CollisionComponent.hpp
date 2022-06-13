#pragma once
#include "AbstractComponent.hpp"
#include "GameObject.hpp"

namespace Scene {
	/// <summary>
	/// simpel component to detect collision between a gameObject and itself
	/// </summary>
	class CollisionComponent : public AbstractComponent {
	public:
		CollisionComponent(std::shared_ptr<GameObject> mouse);

		//inherited function from abstract component
		void update(float deltaTime) override;
		
	private:

	};
}