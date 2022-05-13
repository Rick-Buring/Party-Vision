#pragma once
#include <memory>
#include <list>

namespace Scene {
	class AbstractComponent;

	class GameObject
	{
	public:
		void addComponent(AbstractComponent* component);
		std::list<AbstractComponent*> getComponents();
		void update(float elapsedTime);

	private:
		std::list<AbstractComponent*> components;
	};
}