#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
namespace Minigames {

	class SchoolNinja : public AbstractSceneManager
	{
	public:
		int viewport[4];
		bool endScene = false;
		SchoolNinja();
		void sceneUpdate() override;
		~SchoolNinja();
	private:
	};


}