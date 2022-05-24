#pragma once
#include "AbstractComponent.hpp"
#include "IOnDeath.hpp"
#include "glm/glm.hpp"
#include "ObjectLoader.hpp"
//#include <memory>

namespace Scene {
	class GameObject;
	class onReplace : public IOnDeath, public AbstractComponent {
	public:
		onReplace(std::shared_ptr<GameObject> obj, void (*addGameObject)(std::shared_ptr<GameObject> gameObject));

		void OnDeath() override;

	private:
		void (*_addGameObject)(std::shared_ptr<GameObject> gameObject);
		std::shared_ptr<GameObject> _obj;
	};
}