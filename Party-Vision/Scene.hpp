#pragma once
#include <list>
#include <memory>
#include "GameObject.hpp"

namespace Scene {
	class Scene
	{
	public:
		Scene();
		/// <summary>
		/// adds a gameObject to the scene
		/// </summary>
		/// <param name="gameObject"></param>
		void addGameObject(std::shared_ptr<GameObject> gameObject);

		/// <summary>
		/// removes component from list.
		/// </summary>
		/// <param name="_gameObject"></param>
		void removeGameObject(GameObject* _gameObject);

		/// <summary>
		/// method to update the scene
		/// </summary>
		void update();

		/// <summary>
		/// method to redraw the scene
		/// </summary>
		void draw();

		/// <summary>
		/// method to pause or unpause the scene
		/// </summary>
		/// <param name="status"></param>
		void setRunning(bool status);

		std::list<std::shared_ptr<GameObject>>* getGameobjects();

	private:
		std::list<std::shared_ptr<GameObject>>* _gameObjects;

		std::list<std::shared_ptr<GameObject>>* _gameObjectsToRemove;

		double _lastFrameTime = 0;
		bool _status = false;
	};

}