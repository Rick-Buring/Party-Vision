#include "replaceComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

namespace Scene {
	ReplaceComponent::ReplaceComponent(std::shared_ptr<GameObject> obj, Scene* scene) :
		_obj(obj), _scene(scene)
	{

	}

	void ReplaceComponent::OnDeath()
	{
		std::shared_ptr<TransformComponent> transform = ReplaceComponent::_obj->getComponent<TransformComponent>();
		std::shared_ptr<TransformComponent> transformGameObject = ReplaceComponent::_gameObject->getComponent<TransformComponent>();

		transform->position += transformGameObject->position;
		transform->rotation += transformGameObject->rotation;
		transform->velocity += transformGameObject->velocity;
		transform->angularMomentum += transformGameObject->angularMomentum;

		ReplaceComponent::_scene->addGameObject(ReplaceComponent::_obj);
	}
}