#include "OutofBoundsComponent.hpp"
#include "GameObject.hpp"
#include "TransformComponent.hpp"

namespace Scene {

	OutOfBoundsComponent::OutOfBoundsComponent(Scene* scene) : _scene(scene)
	{
	}

	OutOfBoundsComponent::OutOfBoundsComponent(Scene* scene, glm::vec3 min, glm::vec3 max) : _scene(scene)
	{
		if (min.x < max.x && min.y < max.y && min.z < max.z) {
			_min = min;
			_max = max;
		}
		else
		{
			throw "Invalid parameters min must be smaller than max";
		}
	}

	void OutOfBoundsComponent::update(float)
	{
		if (_gameObject->Transform->position.x < OutOfBoundsComponent::_min.x ||
			_gameObject->Transform->position.x > OutOfBoundsComponent::_max.x ||
			_gameObject->Transform->position.y < OutOfBoundsComponent::_min.y ||
			_gameObject->Transform->position.y > OutOfBoundsComponent::_max.y ||
			_gameObject->Transform->position.z < OutOfBoundsComponent::_min.z ||
			_gameObject->Transform->position.z > OutOfBoundsComponent::_max.z) {
		
			_scene->removeGameObject(_gameObject);
		
		}
	}
}