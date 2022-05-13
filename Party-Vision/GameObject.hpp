#pragma once
#include <memory>
#include <list>

namespace Scene {
	class AbstractComponent;

	class GameObject
	{
		~GameObject();

		std::list<std::shared_ptr<AbstractComponent>> components;
		

	public:
		void addComponent(std::shared_ptr<AbstractComponent> component);
		std::list<std::shared_ptr<AbstractComponent>> getComponents();
		void update(float elapsedTime);

	};
}