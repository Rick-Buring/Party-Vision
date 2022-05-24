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
		ReplaceComponent(std::shared_ptr<GameObject> obj, Scene* scene);

		void OnDeath() override;

	private:
		Scene* _scene;
		std::shared_ptr<GameObject> _obj;
	};
}