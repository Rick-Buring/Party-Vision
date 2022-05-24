#include "replaceComponent.hpp"
#include "GameObject.hpp"

namespace Scene {
	onReplace::onReplace(std::shared_ptr<GameObject> obj, void (*addGameObject)(std::shared_ptr<GameObject> gameObject)) : 
		_obj(obj), _addGameObject(addGameObject)
	{

	}

	void onReplace::OnDeath()
	{
		onReplace::_addGameObject(onReplace::_obj);
	}
}