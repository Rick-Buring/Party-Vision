#pragma once
#include "AbstractComponent.hpp"
#include "IOnDeath.hpp"
#include "glm/glm.hpp"
#include "ObjectLoader.hpp"
#include "Scene.hpp"
//#include <memory>

namespace Scene {
	class GameObject;
	class ReplaceComponent : public IOnDeath, public AbstractComponent {
	public:
		/// <summary>
		/// Will spawn another Object upon death of original Object
		/// </summary>
		/// <param name="obj">The object that will spawn on death</param>
		/// <param name="scene">The scene to spawn the object into</param>
		ReplaceComponent(std::shared_ptr<GameObject> obj, Scene* scene);

		/// <summary>
		/// Implements the OnDeath to method to spawn in the object when it is called. 
		/// </summary>
		void OnDeath() override;

	private:
		Scene* _scene;
		std::shared_ptr<GameObject> _obj;
	};
}