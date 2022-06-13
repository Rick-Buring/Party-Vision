#pragma once
#include "AbstractSceneManager.hpp"
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