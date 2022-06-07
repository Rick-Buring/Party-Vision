#include "GravityComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

namespace Scene {
	void GravityComponent::update(float deltaTime)
	{
		std::shared_ptr<TransformComponent> comp = AbstractComponent::_gameObject->GameObject::Transform;

		comp->velocity.y -= GravityComponent::_gravity * deltaTime;
	}
}