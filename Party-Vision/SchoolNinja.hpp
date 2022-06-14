#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
namespace Minigames {

	class SchoolNinja : public AbstractSceneManager
	{
	public:
		bool endScene = false;
		SchoolNinja();
		void sceneUpdate() override;
		~SchoolNinja();
	private:
	};


}