#pragma once
#include "AbstractSceneManager.hpp"
namespace Minigames {

	class SchoolNinja : public AbstractSceneManager
	{
	public:
		int viewport[4];
		SchoolNinja();
		void sceneUpdate() override;
	private:
	};


}