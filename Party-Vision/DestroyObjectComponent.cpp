#include "DestroyObjectComponent.hpp"
#include "SchoolNinja.hpp"

namespace Scene {

	void DestroyObjectComponent::update(float deltaTime)
	{
		if (DestroyObjectComponent::_timeToLive <= 0) {

			//remove gameobject from scene
			DestroyObjectComponent::_scene->removeGameObject(_gameObject);
			
			if (DestroyObjectComponent::_game) {
				//remove life
				DestroyObjectComponent::_game->removeLife();
			};
			return;
		}
		
		DestroyObjectComponent::_timeToLive -= deltaTime;
	}

	DestroyObjectComponent::DestroyObjectComponent(Scene* scene, float timeToLive)
		: _scene(scene), _timeToLive(timeToLive)
	{}

	DestroyObjectComponent::DestroyObjectComponent(Scene* scene, SchoolNinja* game)
		:_scene(scene), _game(game)
	{	}

	DestroyObjectComponent::DestroyObjectComponent(Scene* scene, float timeToLive, SchoolNinja* game)
		: _scene(scene), _timeToLive(timeToLive), _game(game)
	{	}
}