#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
namespace Minigames {

	class SchoolNinja : public AbstractSceneManager
	{
	public:
		bool endScene = false;
		SchoolNinja();
		~SchoolNinja();

		/// <summary>
		/// updates the scene inherided from Absract SceneManager
		/// </summary>
		void sceneUpdate() override;
	private:
	};


}