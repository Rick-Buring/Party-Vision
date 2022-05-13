#include "GameObject.hpp"
#include "AbstractComponent.hpp"

namespace Scene {
	GameObject::~GameObject()
	{
		components.clear();
	}
	void GameObject::addComponent(std::shared_ptr<AbstractComponent> component)
	{
		component->setGameObject(this);
		components.push_back(component);
	}

	std::list<std::shared_ptr<AbstractComponent>> GameObject::getComponents()
	{
		return components;
	}

	void GameObject::update(float elapsedTime)
	{
		for (auto &c : components)
			c->update(elapsedTime);
	}
}