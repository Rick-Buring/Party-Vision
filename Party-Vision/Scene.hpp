#pragma once
#include <vector>
#include "GameObject.hpp"

namespace Scene {
	class Scene
	{
	public:
		Scene();
		~Scene();

	private:
		std::vector<GameObject> _gameObjects;


	};

}