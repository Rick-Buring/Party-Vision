#include "DestroyObjectComponent.hpp"

namespace Scene {

	void DestroyObjectComponent::update(float deltaTime)
	{
		if (DestroyObjectComponent::_timeToLive <= 0) {
			//todo remove component
			DestroyObjectComponent::_scene->removeComponent(_gameObject);
			//todo remove live

			return;
		}
		
		DestroyObjectComponent::_timeToLive -= deltaTime;

	}

	DestroyObjectComponent::DestroyObjectComponent(Scene* scene, float timeToLive) : _timeToLive(timeToLive), _scene(scene)
	{	}
}