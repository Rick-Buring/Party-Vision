#pragma once
#include <memory>
#include <list>
#include <glm/glm.hpp>
#include "AbstractDrawComponent.hpp"
#include <vector>

namespace Scene {

	/// <summary>
	/// defining classes instead of including the headerfiles because build time they dont exist yet.
	/// in cpp file they are included so we can call the functions.
	/// </summary>
	class AbstractComponent;
	class AbstractDrawComponent;
	class TransformComponent;

	class GameObject
	{
	private:
		std::shared_ptr<AbstractDrawComponent>_drawComponent;
		std::list<std::shared_ptr<AbstractComponent>> components;
		std::shared_ptr<TransformComponent> _transformComponent;


	public:
		~GameObject();

		/// <summary>
		/// adds component to GameObject
		/// </summary>
		/// <param name="component">Component refrence to be added to the gamecomponent</param>
		void addComponent(std::shared_ptr<AbstractComponent> component);
		std::list<std::shared_ptr<AbstractComponent>> getComponents();

		/// <summary>
		/// update function called once per frame
		/// </summary>
		/// <param name="elapsedTime">time passed since last frame</param>
		void update(float elapsedTime);

		/// <summary>
		/// draw method returns if ether there is no drawComponent or transformComponent
		/// </summary>
		/// <param name=""></param>
		void draw(const glm::mat4 & = glm::mat4(1.0f));

		GameObject* getGameObject();

		/// <summary>
		/// get a specific component
		/// </summary>
		/// <typeparam name="T">the type of the component</typeparam>
		/// <returns></returns>
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

		/// <summary>
		/// get a specific component
		/// </summary>
		/// <typeparam name="T">the type of the component</typeparam>
		/// <returns></returns>
		template<class T>
		std::vector<std::shared_ptr<T>> getComponents()
		{
			std::vector<std::shared_ptr<T>> foundComponents;
			for (auto c : components)
			{
				std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
				if (t)
					foundComponents.push_back(t);
			}
			return foundComponents;
		}

		/// <summary>
		/// removes a specific component
		/// </summary>
		/// <typeparam name="T">type of a specific component</typeparam>
		template<class T>
		void removeComponent()
		{
			components.remove_if([](AbstractComponent* c)
				{
					T* t = dynamic_cast<T*>(c);
					return t != nullptr;
				});
		}

	};
}