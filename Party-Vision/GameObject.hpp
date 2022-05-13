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

		template<class T>
		std::shared_ptr<T> getComponent()
		{
			for (auto c : components)
			{
				std::shared_ptr<T> t = dynamic_pointer_cast<T>(c);
				if (t)
					return t;
			}
			return nullptr;
		}

		template<class T>
		void removeComponent()
		{
			components.remove_if([](Component* c)
				{
					T* t = dynamic_cast<T*>(c);
					return t != nullptr;
				});
		}
	};
}