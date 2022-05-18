#include "MainMenu.hpp" 

namespace Minigames {
	
	void MainMenu::menuOnClick() {
		
	}

	
	void MainMenu::menuInit() {
		
	}

	
	void MainMenu::menuUpdate() {
		AbstractSceneManager::currentScene->draw();
		AbstractSceneManager::currentScene->update();

	}



}