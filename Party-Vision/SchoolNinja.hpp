#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
namespace Minigames {

	class SchoolNinja : public AbstractSceneManager
	{
	public:
		int viewport[4];
		std::vector<std::shared_ptr<Scene::GameObject>> lifes;
		SchoolNinja();
		void initLifes();
		void removeLife();
	private:


	};


}