#pragma once
#include "AbstractComponent.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"


namespace Scene {
	class CollisionComponent : public AbstractComponent {
	public:
		CollisionComponent(Scene*);

		/// <summary>
		/// Checks every update if there is any collision detected.
		/// </summary>
		/// <param name="deltaTime">
		/// Time
		/// </param>
		void update(float deltaTime) override;
		
	private:
		Scene* _scene;
	};
}