#include "GameObject.hpp"

namespace Scene {
	void GameObject::addComponent(AbstractComponent* component)
	{
		component->setGameObject(this);
		components.push_back(component);
	}

	std::list<AbstractComponent*> GameObject::getComponents()
	{
		return components;
	}

	void GameObject::update(float elapsedTime)
	{
		for (auto &c : components)
			c->update(elapsedTime);
	}
}