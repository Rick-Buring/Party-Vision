#pragma once
#include <memory>
#include <list>
#include <glm/glm.hpp>
#include "AbstractDrawComponent.hpp"

namespace Scene {
	class AbstractComponent;
	class AbstractDrawComponent;
	class TransformComponent;

	class GameObject
	{
		~GameObject();

		std::list<std::shared_ptr<AbstractComponent>> components;
	protected:
		std::shared_ptr<AbstractDrawComponent>_drawComponent;
		std::shared_ptr<TransformComponent> _transformComponent;
		

	public:
		void addComponent(std::shared_ptr<AbstractComponent> component);
		std::list<std::shared_ptr<AbstractComponent>> getComponents();
		void update(float elapsedTime);
		void draw(const glm::mat4 & = glm::mat4(1.0f));

		template<class T>
		std::shared_ptr<T> getComponent()
		{
			for (auto c : components)
			{
				std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
				if (t)
					return t;
			}
			return nullptr;
		}

	/*	template<class T>
		void removeComponent()
		{
			components.remove_if([](Component* c)
				{
					T* t = dynamic_cast<T*>(c);
					return t != nullptr;
				});
		}*/
	};
}