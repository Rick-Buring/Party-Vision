#pragma once
#include <list>

namespace Scene {
	class GameObject;
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		std::list<GameObject*> _gameObjects;
	};

}