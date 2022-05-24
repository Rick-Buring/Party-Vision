#include "MoveToComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

namespace Scene {

	void MoveToComponent::update(float deltaTime)
	{
		std::shared_ptr<TransformComponent> comp = AbstractComponent::_gameObject->getComponent<TransformComponent>();

		comp->position = targetPosition;
	};
}