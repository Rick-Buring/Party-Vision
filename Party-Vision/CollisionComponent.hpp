#pragma once
#include "AbstractComponent.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"


namespace Scene {
	class CollisionComponent : public AbstractComponent {
	public:
		/// <summary>
		/// Collision constructor
		/// </summary>
		/// <param name="">The scene where the object checks for collision</param>
		CollisionComponent(Scene*);

		/// <summary>
		/// Checks for collision.
		/// </summary>
		/// <param name="deltaTime"> Time passes since last update</param>
		void update(float deltaTime) override;
		
	private:
		Scene* _scene;
	};
}